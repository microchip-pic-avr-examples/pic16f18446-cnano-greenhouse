/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
   software and any derivatives exclusively with Microchip products.

   THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
   EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
   WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
   PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
   WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

   IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
   INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
   WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
   BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
   FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
   ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
   THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

   MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
   TERMS.
*/

#include "HTS221.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c2_master_example.h"

#define CONCATENATE_2BYTES(X, Y)    ((((uint16_t)(X)) << 8 ) | ((uint16_t)(Y)))

#define HUM_UPPER                   100.0f
#define HUM_LOWER                   0.0f
#define T0_MSB_MASK                 0b00000011
#define T1_MSB_MASK                 0b00001100
#define ACTIVE                      0x80
#define REBOOT_MEMORY               0x80
#define DATA_RATE_1HZ               0x01

int16_t HTS221_H0rH;
int16_t HTS221_H1rH;

int16_t HTS221_T0degC;
int16_t HTS221_T1degC;

int16_t HTS221_H0T0OUT;
int16_t HTS221_H1T0OUT;

int16_t HTS221_T0OUT;
int16_t HTS221_T1OUT;

inline static void HTS221_readH0rH(void);
inline static void HTS221_readH1rH(void);
inline static void HTS221_readT0degC(void);
inline static void HTS221_readT1degC(void);
inline static void HTS221_readH0T0OUT(void);
inline static void HTS221_readH1T0OUT(void);
inline static void HTS221_readT0OUT(void);
inline static void HTS221_readT1OUT(void);
static void HTS221_readCalibrationSettings(void);

inline static void HTS221_readH0rH(void)
{
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_H0_RH_X2, (uint8_t *) &HTS221_H0rH, 1);
    HTS221_H0rH = HTS221_H0rH >> 1;
}

inline static void HTS221_readH1rH(void)
{
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_H1_RH_X2, (uint8_t *) &HTS221_H1rH, 1);
    HTS221_H1rH = HTS221_H1rH >> 1;
}

inline static void HTS221_readT0degC(void)
{
    uint8_t T0_degC_x8 = 0;
    uint8_t T1T0_msb = 0;
    
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_T0_DEGC_X8, (uint8_t *) &T0_degC_x8, 1);
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_T1_T0_MSB, (uint8_t *) &T1T0_msb, 1);
    
    HTS221_T0degC = CONCATENATE_2BYTES(T1T0_msb & T0_MSB_MASK, T0_degC_x8);
    HTS221_T0degC = HTS221_T0degC >> 3;
}

inline static void HTS221_readT1degC(void)
{
    uint8_t T1_degC_x8 = 0;
    uint8_t T1T0_msb = 0;
    
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_T1_DEGC_X8, (uint8_t *) &T1_degC_x8, 1);
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_T1_T0_MSB, (uint8_t *) &T1T0_msb, 1);
    
    HTS221_T1degC = CONCATENATE_2BYTES((T1T0_msb & T1_MSB_MASK) >> 2, T1_degC_x8);
    HTS221_T1degC = HTS221_T1degC >> 3;
}

inline static void HTS221_readH0T0OUT(void)
{
    uint8_t H0T0OUT_H = 0;
    uint8_t H0T0OUT_L = 0;

    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_H0_T0_OUT_H, (uint8_t *) &H0T0OUT_H, 1);
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_H0_T0_OUT_L, (uint8_t *) &H0T0OUT_L, 1);
    HTS221_H0T0OUT = CONCATENATE_2BYTES(H0T0OUT_H, H0T0OUT_L);
}

inline static void HTS221_readH1T0OUT(void)
{
    uint8_t H1T0OUT_H = 0;
    uint8_t H1T0OUT_L = 0;
    
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_H1_T0_OUT_H, (uint8_t *) &H1T0OUT_H, 1);
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_H1_T0_OUT_L, (uint8_t *) &H1T0OUT_L, 1);
    HTS221_H1T0OUT = CONCATENATE_2BYTES(H1T0OUT_H, H1T0OUT_L);
}

inline static void HTS221_readT0OUT(void)
{
    uint8_t T0OUT_H = 0;
    uint8_t T0OUT_L = 0;
    
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_T0_OUT_H, (uint8_t *) &T0OUT_H, 1);
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_T0_OUT_L, (uint8_t *) &T0OUT_L, 1);
    HTS221_T0OUT = CONCATENATE_2BYTES(T0OUT_H, T0OUT_L);
}

inline static void HTS221_readT1OUT(void)
{
    uint8_t T1OUT_H = 0;
    uint8_t T1OUT_L = 0;
    
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_T1_OUT_H, (uint8_t *) &T1OUT_H, 1);
    I2C2_ReadDataBlock(HTS221_ADDRESS, CALIB_T1_OUT_L, (uint8_t *) &T1OUT_L, 1);
    HTS221_T1OUT = CONCATENATE_2BYTES(T1OUT_H, T1OUT_L);
}

static void HTS221_readCalibrationSettings(void)
{
    HTS221_readH0rH();
    HTS221_readH1rH();
    HTS221_readT0degC();
    HTS221_readT1degC();
    HTS221_readH0T0OUT();
    HTS221_readH1T0OUT();
    HTS221_readT0OUT();
    HTS221_readT1OUT();
}

void HTS221_init(void)
{
    I2C2_Write1ByteRegister(HTS221_ADDRESS, CTRL_REG2, REBOOT_MEMORY);
    I2C2_Write1ByteRegister(HTS221_ADDRESS, CTRL_REG1, ACTIVE | DATA_RATE_1HZ);

    HTS221_readCalibrationSettings();
}

float HTS221_readTemperature(void)
{
    int16_t T_out = 0;
    uint8_t TEMP_H = 0;
    uint8_t TEMP_L = 0;
    
    I2C2_ReadDataBlock(HTS221_ADDRESS, TEMP_H_REG, (uint8_t *) &TEMP_H, 1);
    I2C2_ReadDataBlock(HTS221_ADDRESS, TEMP_L_REG, (uint8_t *) &TEMP_L, 1);
    T_out = CONCATENATE_2BYTES(TEMP_H, TEMP_L);
    
    return (float)(T_out - HTS221_T0OUT) *
           (float)(HTS221_T1degC - HTS221_T0degC) /
           (float)(HTS221_T1OUT - HTS221_T0OUT)  +  HTS221_T0degC;
}

float HTS221_readHumidity(void)
{    
    int16_t H_T_out = 0;
    uint8_t HUMIDITY_H = 0;
    uint8_t HUMIDITY_L = 0;
    float hum_f;
    
    I2C2_ReadDataBlock(HTS221_ADDRESS, HUMIDITY_H_REG, (uint8_t *) &HUMIDITY_H, 1);
    I2C2_ReadDataBlock(HTS221_ADDRESS, HUMIDITY_L_REG, (uint8_t *) &HUMIDITY_L, 1);
    H_T_out = CONCATENATE_2BYTES(HUMIDITY_H, HUMIDITY_L);
    
    hum_f = (float)(H_T_out - HTS221_H0T0OUT) *
            (float)(HTS221_H1rH - HTS221_H0rH) /
            (float)(HTS221_H1T0OUT - HTS221_H0T0OUT)  +  HTS221_H0rH;

    if(hum_f > HUM_UPPER)
    {
        return HUM_UPPER;
    }
    
    if(hum_f < HUM_LOWER)
    {
        return HUM_LOWER;
    }
   
    return hum_f;
}
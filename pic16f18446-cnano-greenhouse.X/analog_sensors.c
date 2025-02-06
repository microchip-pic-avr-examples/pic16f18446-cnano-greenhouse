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

#include "analog_sensors.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/adcc.h"

#define SAMPLES_NUM         1000
#define WATER_X0            0
#define WATER_X1            1000000
#define SOIL_X0             130400
#define SOIL_X1             1026000
#define Y0                  0
#define Y1                  100

#define CONVERSION_DELAY    3200 /* delay : 100us */


uint8_t ANALOG_readSoilMoisture(void)
{
    uint32_t soil = 0;
    static bool conversion_state = true;
    
    for (int count = 0; count  < SAMPLES_NUM; ++count)
    {
        if(conversion_state)
        {
            channel_ANB4_SetPullup();
            channel_ANB4_SetDigitalInput();
            channel_ANB6_ResetPullup();
            channel_ANB6_SetDigitalOutput();
            soil += ADCC_GetSingleConversion(channel_ANB4);
        } 
        else
        {
            channel_ANB6_SetPullup();
            channel_ANB6_SetDigitalInput();
            channel_ANB4_ResetPullup();
            channel_ANB4_SetDigitalOutput();
            soil += ADCC_GetSingleConversion(channel_ANB6);
        }
        
        conversion_state = !conversion_state;
    }
    
    channel_ANB4_ResetPullup();
    channel_ANB6_ResetPullup();
    channel_ANB4_SetDigitalInput();
    channel_ANB6_SetDigitalInput();
    
    if(soil > SOIL_X1)
    {
        return Y0;
    }
    
    if(soil < SOIL_X0)
    {
        return Y1;
    }
    
    soil = Y0 * (SOIL_X1 - soil) + Y1 * (soil - SOIL_X0);
    return Y1 - soil / (SOIL_X1 - SOIL_X0);
}

uint8_t ANALOG_readWaterLevel(void)
{
    uint32_t level = 0;

    for(int count = 0; count < SAMPLES_NUM / 2; ++count)
    {
        level += ADCC_GetSingleConversion(channel_ANC2);
    }
    
    if(level > WATER_X1)
    {
        return Y1;
    }
    
    if(level < WATER_X0)
    {
        return Y0;
    }
    
    level = Y0 * (WATER_X1 - level) + Y1 * (level - WATER_X0);
    return level / (WATER_X1 - WATER_X0);
}
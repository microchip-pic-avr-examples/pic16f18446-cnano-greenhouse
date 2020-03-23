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

#include "greenhouse_display.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/oledC_colors.h"
#include "mcc_generated_files/oledC_shapeHandler.h"
#include "mcc_generated_files/oledC_shapes.h"

#define BUFF_SIZE       10
#define CMD             0x62

#define FONT_SIZE_X     1
#define FONT_SIZE_Y     1
#define UPPER           96
#define LOWER           0

#define TEMP_TEXT_X     1
#define TEMP_TEXT_Y     80
#define HUM_TEXT_X      1
#define HUM_TEXT_Y      60
#define SOIL_TEXT_X     1
#define SOIL_TEXT_Y     40
#define WATER_TEXT_X    1
#define WATER_TEXT_Y    20
#define REFILL_TEXT_X   30
#define REFILL_TEXT_Y   0

#define BOX_SIZE_X      50
#define BOX_SIZE_Y      9

#define TEMP_VALUE_X    1
#define TEMP_VALUE_Y    70
#define HUM_VALUE_X     1
#define HUM_VALUE_Y     50
#define SOIL_VALUE_X    1
#define SOIL_VALUE_Y    30
#define WATER_VALUE_X   1
#define WATER_VALUE_Y   10

#define TEMPERATURE     "TEMPERATURE"
#define HUMIDITY        "HUMIDITY"
#define SOIL_MOISTURE   "SOIL MOISTURE"
#define WATER_LEVEL     "WATER LEVEL"
#define REFILL          "REFILL"

bool exampleInitialized;
uint16_t background_color;

static void GREEN_HOUSE_DISPLAY_clearScreen(void)
{    
    oledC_setColumnAddressBounds(LOWER,UPPER);
    oledC_setRowAddressBounds(LOWER,UPPER);
    for(uint8_t x = LOWER; x < UPPER; x++){
        for(uint8_t y = LOWER; y < UPPER; y++){
            oledC_sendColorInt(background_color);
        }
    }
}

static void GREEN_HOUSE_DISPLAY_setBackground(uint16_t color)
{
    background_color = color;
    GREEN_HOUSE_DISPLAY_clearScreen();
}

void GREEN_HOUSE_DISPLAY_init(void)
{
    uint8_t payload = CMD;
    //oledC_sendCommand(OLEDC_CMD_SET_REMAP_DUAL_COM_LINE_MODE, &payload, 1);
    
    GREEN_HOUSE_DISPLAY_setBackground(OLEDC_COLOR_BLACK);
    
    oledC_DrawString(
            TEMP_TEXT_X,
            TEMP_TEXT_Y,
            FONT_SIZE_X,
            FONT_SIZE_Y,
            (uint8_t *) TEMPERATURE,
            OLEDC_COLOR_WHITE);
    oledC_DrawString(
            HUM_TEXT_X,
            HUM_TEXT_Y,
            FONT_SIZE_X,
            FONT_SIZE_Y,
            (uint8_t *) HUMIDITY,
            OLEDC_COLOR_WHITE);
    oledC_DrawString(
            SOIL_TEXT_X,
            SOIL_TEXT_Y,
            FONT_SIZE_X,
            FONT_SIZE_Y,
            (uint8_t *) SOIL_MOISTURE,
            OLEDC_COLOR_WHITE);
    oledC_DrawString(
            WATER_TEXT_X,
            WATER_TEXT_Y,
            FONT_SIZE_X,
            FONT_SIZE_Y,
            (uint8_t *) WATER_LEVEL,
            OLEDC_COLOR_WHITE);
}

void GREEN_HOUSE_DISPLAY_temperature(float temp)
{
    char tempString[BUFF_SIZE];
    
    sprintf(tempString, "%.0f C\0", temp);
    
    oledC_DrawRectangle(
            TEMP_VALUE_X,
            TEMP_VALUE_Y,
            TEMP_VALUE_X + BOX_SIZE_X,
            TEMP_VALUE_Y + BOX_SIZE_Y,
            OLEDC_COLOR_BLACK);
    oledC_DrawString(
            TEMP_VALUE_X,
            TEMP_VALUE_Y,
            FONT_SIZE_X,
            FONT_SIZE_Y,
            (uint8_t *) tempString,
            OLEDC_COLOR_WHITE);
}

void GREEN_HOUSE_DISPLAY_humidity(float hum)
{
    char humString[BUFF_SIZE];
    
    sprintf(humString, "%.0f %%\0", hum);
    
    oledC_DrawRectangle(
            HUM_VALUE_X,
            HUM_VALUE_Y,
            HUM_VALUE_X + BOX_SIZE_X,
            HUM_VALUE_Y + BOX_SIZE_Y,
            OLEDC_COLOR_BLACK);
    oledC_DrawString(HUM_VALUE_X,
            HUM_VALUE_Y,
            FONT_SIZE_X,
            FONT_SIZE_Y,
            (uint8_t *) humString,
            OLEDC_COLOR_WHITE);
}

void GREEN_HOUSE_DISPLAY_soilMoisture(uint8_t soil)
{
    char soilString[BUFF_SIZE];
    
    sprintf(soilString, "%i %%\0 ", soil);
    
    oledC_DrawRectangle(
            SOIL_VALUE_X,
            SOIL_VALUE_Y,
            SOIL_VALUE_X + BOX_SIZE_X,
            SOIL_VALUE_Y + BOX_SIZE_Y,
            OLEDC_COLOR_BLACK);
    oledC_DrawString(
            SOIL_VALUE_X,
            SOIL_VALUE_Y,
            FONT_SIZE_X,
            FONT_SIZE_Y,
            (uint8_t *) soilString,
            OLEDC_COLOR_WHITE);
}

void GREEN_HOUSE_DISPLAY_waterLevel(uint8_t water)
{
    char waterString[BUFF_SIZE];
    
    sprintf(waterString, "%i %% \0", water);
    
    oledC_DrawRectangle(
            WATER_VALUE_X,
            WATER_VALUE_Y,
            WATER_VALUE_X + BOX_SIZE_X,
            WATER_VALUE_Y + BOX_SIZE_Y,
            OLEDC_COLOR_BLACK);
    oledC_DrawString(
            WATER_VALUE_X,
            WATER_VALUE_Y,
            FONT_SIZE_X,
            FONT_SIZE_Y,
            (uint8_t *) waterString,
            OLEDC_COLOR_WHITE);
}

void GREEN_HOUSE_DISPLAY_refillMessage(bool refill)
{
    if(refill)
    {
        oledC_DrawRectangle(
            LOWER,
            LOWER,
            UPPER,
            BOX_SIZE_Y,
            OLEDC_COLOR_RED);
        oledC_DrawString(
            REFILL_TEXT_X,
            REFILL_TEXT_Y,
            FONT_SIZE_X,
            FONT_SIZE_Y,
            (uint8_t *) REFILL,
            OLEDC_COLOR_WHITE);
    }
    else
    {
        oledC_DrawRectangle(
            LOWER,
            LOWER,
            UPPER,
            BOX_SIZE_Y,
            OLEDC_COLOR_BLACK);
    }
}

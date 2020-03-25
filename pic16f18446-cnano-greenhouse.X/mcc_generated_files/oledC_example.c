 /*
     (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
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

#include <stdint.h>
#include <stdbool.h>
#include "oledC.h"
#include "oledC_colors.h"
#include "oledC_shapeHandler.h"
#include "oledC_shapes.h"

static bool exampleInitialized;
static uint16_t background_color;

static const uint32_t logo[] = 
{ 
    0b11111111111000000000011111111111,
    0b11111111100000000000001111111111,
    0b11111111000000000000000111111111,
    0b11111110000000000000000111111111,
    0b11111100000000000000000011111111,
    0b11111000000010000000100011111111,
    0b11111000000110000001100001111111,
    0b11110000001111000011110000111111,
    0b11110000001111100011111000111111,
    0b11110000000111100001111000011111,
    0b11110000000111110001111100001111,
    0b11110001000011110000111110001111,
    0b11110001100011111000111110001111,
    0b11110011110001111100011111001111,
    0b11110111110000111100001111001111,
    0b11111111100000111100001111111111,
    0b11111111100000011100000111111111,
    0b11111111000000011000000011111111,
    0b11111110000000000000000011111111,
    0b11111110000000000000000001111111,
    0b11111110000000000000000001111111,
    0b11111111100000000000000111111111,
    0b11111111111000000000011111111111
};

static void oledC_clearScreen(void) 
{    
    uint8_t x;
    uint8_t y;
    oledC_setColumnAddressBounds(0,96);
    oledC_setRowAddressBounds(0,96);
    for(x = 0; x < 96; x++)
    {
        for(y = 0; y < 96; y++)
        {
            oledC_sendColorInt(background_color);
        }
    }
}

static void oledC_setBackground(uint16_t color)
{
    background_color = color;
    oledC_clearScreen();
}

static void oledC_example_setup(void)
{
    oledC_setBackground(OLEDC_COLOR_WHITE);
    shape_params_t params;
    
    params.bitmap.color = OLEDC_COLOR_RED;
    params.bitmap.x = 14;
    params.bitmap.y = 25;
    params.bitmap.sx = 2;
    params.bitmap.sy = 2;
    params.bitmap.bit_array = (uint32_t *)&logo[0];
    params.bitmap.array_length = 23;
    oledC_addShape(0,OLED_SHAPE_BITMAP, &params);
    
    params.circle.radius = 10;
    params.circle.xc = 10;
    params.circle.yc = 10;
    oledC_addShape(1,OLED_SHAPE_CIRCLE, &params);
    
    params.circle.color = OLEDC_COLOR_BLUE;
    params.circle.yc = 85;
    oledC_addShape(2,OLED_SHAPE_CIRCLE, &params);
    
    params.circle.color = OLEDC_COLOR_YELLOW;
    params.circle.xc = 85;
    oledC_addShape(3,OLED_SHAPE_CIRCLE, &params);
    
    params.circle.color = OLEDC_COLOR_GREEN;
    params.circle.yc = 10;
    oledC_addShape(4,OLED_SHAPE_CIRCLE, &params);
    
    
    oledC_redrawAll();
    exampleInitialized = true;
}

void oledC_example(void)
{
    static int8_t shift = -24;
    const uint8_t shift_from = 15;
    if(!exampleInitialized)
    {
        oledC_example_setup();
    }
    shape_t *moveIt = oledC_getShape(0);
    
    oledC_eraseShape(0, background_color);
    moveIt->params.bitmap.x = shift_from + shift;
    shift += 4;
    if(shift > 24)
    {
        shift = -24;
    }
    oledC_redrawIndex(0);
}


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

#include <stdbool.h>
#include <stdint.h>
#include "oledC_shapes.h"
#include "oledC.h"

static const uint8_t OLED_DIM_WIDTH = 0x5F;
static const uint8_t OLED_DIM_HEIGHT = 0x5F;
static const uint8_t OLED_FONT_WIDTH = 0x5;
static const uint8_t OLED_FONT_HEIGHT = 0x8;

static void drawPoint(shape_t *shape);
static void drawCircle(shape_t *shape);
static void drawRing(shape_t *shape);
static void drawRectangle(shape_t *shape);
static void drawLine(shape_t *shape);
static void drawCharacter(shape_t *shape);
static void drawString(shape_t *shape);
static void drawString(shape_t *shape);
static void drawBitmap(shape_t *shape);


void oledC_createShape(enum OLEDC_SHAPE shape_type, shape_params_t *params, shape_t *newShape)
{
    newShape->_type = shape_type;
    newShape->active = true;
    
    newShape->params.point = params->point;
    switch(shape_type)
    {
        case OLED_SHAPE_CIRCLE:
            newShape->params.circle = params->circle;
            newShape->draw = drawCircle;
            break;
        case OLED_SHAPE_RING:
            newShape->params.ring = params->ring;
            newShape->draw = drawRing;
            break;
        case OLED_SHAPE_RECTANGLE:
            newShape->params.rectangle = params->rectangle;
            newShape->draw = drawRectangle;
            break;
        case OLED_SHAPE_LINE:
            newShape->params.line = params->line;
            newShape->draw = drawLine;
            break;
        case OLED_SHAPE_CHARACTER:
            newShape->params.character = params->character;
            newShape->draw = drawCharacter;
            break;
        case OLED_SHAPE_STRING:
            newShape->params.string = params->string;
            newShape->draw = drawString;
            break;
        case OLED_SHAPE_BITMAP:
            newShape->params.bitmap = params->bitmap;
            newShape->draw = drawBitmap;
            break;
        default: 
            newShape->draw = drawPoint;
            break;
    }
}

static const uint8_t font[] = 
    { // compact 5x8 font
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFA,0x00,0x00,0x00,0xE0,0x00,0xE0,0x00, //	'sp,!,"
    0x28,0xFE,0x28,0xFE,0x28, // #
    0x24,0x54,0xFE,0x54,0x48,0xC4,0xC8,0x10,0x26,0x46,0x6C,0x92,0x6A,0x04,0x0A, //	'$,%,&
    0x00,0x10,0xE0,0xC0,0x00,0x00,0x38,0x44,0x82,0x00,0x00,0x82,0x44,0x38,0x00, //	'',(,)
    0x54,0x38,0xFE,0x38,0x54,0x10,0x10,0x7C,0x10,0x10,0x00,0x00,0x0E,0x0C,0x00, //	'*,+,,
    0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x06,0x06,0x00,0x04,0x08,0x10,0x20,0x40, //	'-,.,/
    0x7C,0x8A,0x92,0xA2,0x7C,0x00,0x42,0xFE,0x02,0x00,0x4E,0x92,0x92,0x92,0x62, //	'0,1,2
    0x84,0x82,0x92,0xB2,0xCC,0x18,0x28,0x48,0xFE,0x08,0xE4,0xA2,0xA2,0xA2,0x9C, //	'3,4,5
    0x3C,0x52,0x92,0x92,0x8C,0x82,0x84,0x88,0x90,0xE0,0x6C,0x92,0x92,0x92,0x6C, //	'6,7,8
    0x62,0x92,0x92,0x94,0x78,0x00,0x00,0x28,0x00,0x00,0x00,0x02,0x2C,0x00,0x00, //	'9,:,;
    0x00,0x10,0x28,0x44,0x82,0x28,0x28,0x28,0x28,0x28,0x00,0x82,0x44,0x28,0x10, //	'<,=,>
    0x40,0x80,0x9A,0x90,0x60,0x7C,0x82,0xBA,0x9A,0x72,                          //  '?,@
    0x3E,0x48,0x88,0x48,0x3E,                                                   //	'A
    0xFE,0x92,0x92,0x92,0x6C,0x7C,0x82,0x82,0x82,0x44,0xFE,0x82,0x82,0x82,0x7C, //	'B,C,D
    0xFE,0x92,0x92,0x92,0x82,0xFE,0x90,0x90,0x90,0x80,0x7C,0x82,0x82,0x8A,0xCE, //	'E,F,G
    0xFE,0x10,0x10,0x10,0xFE,0x00,0x82,0xFE,0x82,0x00,0x04,0x02,0x82,0xFC,0x80, //	'H,I,J
    0xFE,0x10,0x28,0x44,0x82,0xFE,0x02,0x02,0x02,0x02,0xFE,0x40,0x38,0x40,0xFE, //	'K,L,M
    0xFE,0x20,0x10,0x08,0xFE,0x7C,0x82,0x82,0x82,0x7C,0xFE,0x90,0x90,0x90,0x60, //	'N,O,P
    0x7C,0x82,0x8A,0x84,0x7A,0xFE,0x90,0x98,0x94,0x62,0x64,0x92,0x92,0x92,0x4C, //	'Q,R,S
    0xC0,0x80,0xFE,0x80,0xC0,0xFC,0x02,0x02,0x02,0xFC,0xF8,0x04,0x02,0x04,0xF8, //	'T,U,V
    0xFC,0x02,0x1C,0x02,0xFC,0xC6,0x28,0x10,0x28,0xC6,0xC0,0x20,0x1E,0x20,0xC0, //	'W,X,Y
    0x86,0x9A,0x92,0xB2,0xC2,                                                   //  'Z
    0x00,0xFE,0x82,0x82,0x82,0x40,0x20,0x10,0x08,0x04,                          //	'[,'\' 
    0x00,0x82,0x82,0x82,0xFE,0x20,0x40,0x80,0x40,0x20,0x02,0x02,0x02,0x02,0x02, //	'],^,_
    0x00,0xC0,0xE0,0x10,0x00,0x04,0x2A,0x2A,0x1C,0x02,0xFE,0x14,0x22,0x22,0x1C, //	'`,a,b
    0x1C,0x22,0x22,0x22,0x14,0x1C,0x22,0x22,0x14,0xFE,0x1C,0x2A,0x2A,0x2A,0x18, //	'c,d,e
    0x00,0x10,0x7E,0x90,0x40,0x30,0x4A,0x4A,0x52,0x3C,0xFE,0x10,0x20,0x20,0x1E, //	'f,g,h
    0x00,0x22,0xBE,0x02,0x00,0x04,0x02,0x02,0xBC,0x00,0xFE,0x08,0x14,0x22,0x00, //	'i,j,k
    0x00,0x82,0xFE,0x02,0x00,0x3E,0x20,0x1E,0x20,0x1E,0x3E,0x10,0x20,0x20,0x1E, //	'l,m,n
    0x1C,0x22,0x22,0x22,0x1C,0x3E,0x18,0x24,0x24,0x18,0x18,0x24,0x24,0x18,0x3E, //	'o,p,q
    0x3E,0x10,0x20,0x20,0x10,0x12,0x2A,0x2A,0x2A,0x24,0x20,0x20,0xFC,0x22,0x24, //	'r,s,t
    0x3C,0x02,0x02,0x04,0x3E,0x38,0x04,0x02,0x04,0x38,0x3C,0x02,0x0C,0x02,0x3C, //	'u,v,w
    0x22,0x14,0x08,0x14,0x22,0x32,0x0A,0x0A,0x0A,0x3C,0x22,0x26,0x2A,0x32,0x22, //	'x,y,z
    0x00,0x10,0x6C,0x82,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x82,0x6C,0x10,0x00, //	'{,|,}
    0x40,0x80,0x40,0x20,0x40                                                    //  '~
    };

static uint8_t coerceAddressAdditionWithinRange(uint8_t base_address, int8_t adder)
{
    int16_t additionResult = base_address+adder;
    if(additionResult > (int16_t)OLED_DIM_WIDTH)
    {
        return OLED_DIM_WIDTH;
    } 
    if(additionResult < (int16_t) 0x00) 
    {
        return 0x00;
    }
    return (uint8_t) (base_address+adder);
}

void oledC_DrawPoint(uint8_t x, uint8_t y, uint16_t color)
{
    if(x > OLED_DIM_WIDTH || y > OLED_DIM_HEIGHT)
    {
        return;
    }
    oledC_setColumnAddressBounds(x,95);
    oledC_setRowAddressBounds(y,95);
    oledC_sendColorInt(color);
}

void oledC_DrawThickPoint(uint8_t center_x, uint8_t center_y, uint8_t width, uint16_t color)
{
    uint8_t max_x,min_x,max_y, min_y;
    uint8_t x, y, dx, dy;
    if((center_x-width) > OLED_DIM_WIDTH || (center_y-width) > OLED_DIM_HEIGHT)
    {
        return;
    }
    width = (width <= 1) ? 1 : width;
    max_x = coerceAddressAdditionWithinRange(center_x, width);
    min_x = coerceAddressAdditionWithinRange(center_x, -(width));
    max_y = coerceAddressAdditionWithinRange(center_y, width);
    min_y = coerceAddressAdditionWithinRange(center_y, -(width));
    
    for(x = min_x; x < max_x; x++)
    {
        dx = (center_x >= x) ? (center_x-x) : (x - center_x);
        for(y = min_y; y < max_y; y++)
        {
            dy = (center_y >= y) ? (center_y-y) : (y - center_y);
            if(((dy+dx) <= width)|| (dy*dy+dx*dx) <= (width*width))
            {
                oledC_DrawPoint(x, y, color);
            }
        }
    }
}

void oledC_DrawCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t color)
{
    int8_t xCurr, yMax = 0, y = 0, x=0;
    int16_t d = 0;
   
    radius = radius <= 1 ? 1 : radius;
    xCurr = radius+1;
    yMax = 0;
    y = 0;
    d = 0;

    while (xCurr >= yMax)
    {
        d += (2*yMax+1);
        yMax++;
        if(d >= 0)
        {
            for(y = y; y < yMax; y++)
            {
                for(x = y; x < xCurr; x++)
                {
                    oledC_DrawPoint(x0 + x,y0 + y, color);
                    oledC_DrawPoint(x0 + x,y0 - y, color);
                    oledC_DrawPoint(x0 - x,y0 + y, color);
                    oledC_DrawPoint(x0 - x,y0 - y, color);    
                    oledC_DrawPoint(x0 + y,y0 + x, color);
                    oledC_DrawPoint(x0 + y,y0 - x, color);
                    oledC_DrawPoint(x0 - y,y0 + x, color);
                    oledC_DrawPoint(x0 - y,y0 - x, color);
                }
            }
            d += -2*xCurr + 1;
            xCurr--;
        }
    }
}

void oledC_DrawRing(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t width, uint16_t color)
{
    int8_t x, y;
    int16_t d;
    radius += width >> 1;
    while(width-- > 0)
    {
        x = radius;
        y = 0;
        d = 0;

        while (x >= y)
        {
            oledC_DrawPoint(x0 + x,y0 + y, color);
            oledC_DrawPoint(x0 + x,y0 - y, color);
            oledC_DrawPoint(x0 - x,y0 + y, color);
            oledC_DrawPoint(x0 - x,y0 - y, color);    
            oledC_DrawPoint(x0 + y,y0 + x, color);
            oledC_DrawPoint(x0 + y,y0 - x, color);
            oledC_DrawPoint(x0 - y,y0 + x, color);
            oledC_DrawPoint(x0 - y,y0 - x, color);
            
            d += (2*y+1);
            y++;
            if(d >= 0)
            {
                d += -2*x + 1;
                x--;
            }
        }
        radius--;
    }
}

void oledC_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t width, uint16_t color)
{
    int8_t x, y;
    int8_t dx, dy, D;
    width = width <= 1 ? 1 : width;
    
    dx = x1 - x0;
    dy = y1 - y0;
    D = dy - dx;
    y = y0;
    
    for(x = x0; x < x1; x++)
    {
        if(x <= OLED_DIM_WIDTH && y <= OLED_DIM_HEIGHT)
        {
            if(width <= 1)
            {
                oledC_DrawPoint(x,y, color);
            } 
            else 
            {
                oledC_DrawCircle(x, y, width/2, color);
            }
        }
        if(D >= 0)
        {
            y = y+1;
            D = D - dx;
        }
        D = D + dy;
    }
}

void oledC_DrawRectangle(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, uint16_t color)
{
    uint8_t x;
    uint8_t y;
    oledC_setColumnAddressBounds(start_x,end_x);
    oledC_setRowAddressBounds(start_y,end_y);
    for(x = start_x; x < end_x+1; x++)
    {
        for(y = start_y; y < end_y+1; y++)
        {
            oledC_sendColorInt(color);
        }
    }
}

void oledC_DrawCharacter(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, uint8_t ch, uint16_t color)
{   
    const uint8_t *f = &font[(ch-' ')*OLED_FONT_WIDTH]; // find the char in our font...
    uint16_t i_x;
    uint16_t i_y;
    
    for(i_x = 0; i_x < OLED_FONT_WIDTH * sx; i_x += sx) // For each line of our text...
    { 
        uint8_t curr_char_byte = *f++;
        for(i_y = OLED_FONT_HEIGHT*sy; i_y > 0; i_y -= sy)
        {
            if(curr_char_byte & 0x01)
            {
                oledC_DrawRectangle(x+i_x, y+i_y, x+i_x+sx-1, y+i_y+sy-1, color);
            }
            curr_char_byte >>= 1;
        }
    }
}

void oledC_DrawString(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, uint8_t *string, uint16_t color)
{
    while(*string)
    {
        oledC_DrawCharacter(x, y, sx, sy, *string++, color);
        x += OLED_FONT_WIDTH * sx + 1;
    }
}

void oledC_DrawBitmap(uint8_t x, uint8_t y, uint16_t color, uint8_t sx, uint8_t sy, uint32_t *bitmap, uint8_t bitmap_length)
{
    const uint8_t bitmap_width = 32;
    uint8_t rowNum;
    uint8_t bitNum;
    sx = sx == 0 ? 1 : sx;
    sy = sy == 0 ? 1 : sy;
    for(rowNum = 0; rowNum < bitmap_length; rowNum++)
    {
        uint32_t rowBits = *bitmap++;
        uint8_t curr_y = y + rowNum*sy;
        for(bitNum = 0; bitNum < bitmap_width; bitNum++)
        {
            if(!(rowBits & 0x01))
            {
                uint8_t curr_x = x + (bitmap_width - bitNum)*sx;
                oledC_DrawRectangle(curr_x, curr_y, curr_x+sx-1, curr_y+sy-1, color);
            }
            rowBits >>= 0x000001;
        }
    }
}

/* Standardized Shape Drawing */
static void drawPoint(shape_t *shape)
{
    oledC_DrawPoint(
        shape->params.point.x, 
        shape->params.point.y,
        shape->params.point.color
    );
}

static void drawCircle(shape_t *shape)
{
    oledC_DrawCircle(
        shape->params.circle.xc, 
        shape->params.circle.yc, 
        shape->params.circle.radius, 
        shape->params.circle.color
    );
}

static void drawRing(shape_t *shape)
{
    oledC_DrawRing(
        shape->params.ring.x0, 
        shape->params.ring.y0, 
        shape->params.ring.radius, 
        shape->params.ring.width, 
        shape->params.ring.color
    );
}

static void drawRectangle(shape_t *shape)
{
    oledC_DrawRectangle(
        shape->params.rectangle.xs, 
        shape->params.rectangle.ys,
        shape->params.rectangle.xe, 
        shape->params.rectangle.ye, 
        shape->params.rectangle.color
    );
}

static void drawLine(shape_t *shape)
{
    oledC_DrawLine(
        shape->params.line.xs, 
        shape->params.line.ys,
        shape->params.line.xe, 
        shape->params.line.ye, 
        shape->params.line.width, 
        shape->params.line.color
    );
}

static void drawCharacter(shape_t *shape)
{
    oledC_DrawCharacter(
        shape->params.character.x, 
        shape->params.character.y,
        shape->params.character.scale_x, 
        shape->params.character.scale_y, 
        shape->params.character.character, 
        shape->params.character.color
    );
}

static void drawString(shape_t *shape)
{
    oledC_DrawString(
        shape->params.string.x, 
        shape->params.string.y,
        shape->params.string.scale_x, 
        shape->params.string.scale_y, 
        shape->params.string.string, 
        shape->params.string.color
    );
}

static void drawBitmap(shape_t *shape)
{
    oledC_DrawBitmap(
        shape->params.bitmap.x, 
        shape->params.bitmap.y,
        shape->params.bitmap.color,
        shape->params.bitmap.sx,
        shape->params.bitmap.sy,
        shape->params.bitmap.bit_array,
        shape->params.bitmap.array_length
    );
}

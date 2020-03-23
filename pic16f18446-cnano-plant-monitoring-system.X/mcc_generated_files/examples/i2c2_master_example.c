/**
  I2C2 Generated Example Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c2.c

  @Summary
    This is the generated driver examples implementation file for the I2C2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides implementations for driver APIs for I2C2.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.79.0
        Device            :  PIC16F18446
        Driver Version    :  1.0.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above or later
        MPLAB             :  MPLAB X 5.30
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "i2c2_master_example.h"


typedef struct
{
    size_t len;
    uint8_t *data;
}i2c2_buffer_t;

static i2c2_operations_t rd1RegCompleteHandler(void *ptr);
static i2c2_operations_t rd2RegCompleteHandler(void *ptr);
static i2c2_operations_t wr1RegCompleteHandler(void *ptr);
static i2c2_operations_t wr2RegCompleteHandler(void *ptr);
static i2c2_operations_t rdBlkRegCompleteHandler(void *ptr);


uint8_t I2C2_Read1ByteRegister(i2c2_address_t address, uint8_t reg)
{
    uint8_t returnValue = 0x00;
    
    while(!I2C2_Open(address)); // sit here until we get the bus..
    I2C2_SetDataCompleteCallback(rd1RegCompleteHandler,&returnValue);
    I2C2_SetBuffer(&reg,1);
    I2C2_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C2_MasterWrite();
    while(I2C2_BUSY == I2C2_Close()); // sit here until finished.
    
    return returnValue;
}

uint16_t I2C2_Read2ByteRegister(i2c2_address_t address, uint8_t reg)
{
    uint16_t returnValue =0x00; // returnValue is little endian

    while(!I2C2_Open(address)); // sit here until we get the bus..
    I2C2_SetDataCompleteCallback(rd2RegCompleteHandler,&returnValue);
    I2C2_SetBuffer(&reg,1);
    I2C2_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C2_MasterWrite();
    while(I2C2_BUSY == I2C2_Close()); // sit here until finished.
  
    return (returnValue << 8 | returnValue >> 8);
}

void I2C2_Write1ByteRegister(i2c2_address_t address, uint8_t reg, uint8_t data)
{
    while(!I2C2_Open(address)); // sit here until we get the bus..
    I2C2_SetDataCompleteCallback(wr1RegCompleteHandler,&data);
    I2C2_SetBuffer(&reg,1);
    I2C2_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C2_MasterWrite();
    while(I2C2_BUSY == I2C2_Close()); // sit here until finished.
}

void I2C2_Write2ByteRegister(i2c2_address_t address, uint8_t reg, uint16_t data)
{
    while(!I2C2_Open(address)); // sit here until we get the bus..
    I2C2_SetDataCompleteCallback(wr2RegCompleteHandler,&data);
    I2C2_SetBuffer(&reg,1);
    I2C2_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C2_MasterWrite();
    while(I2C2_BUSY == I2C2_Close()); // sit here until finished.
}

void I2C2_WriteNBytes(i2c2_address_t address, uint8_t* data, size_t len)
{
    while(!I2C2_Open(address)); // sit here until we get the bus..
    I2C2_SetBuffer(data,len);
    I2C2_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C2_MasterWrite();
    while(I2C2_BUSY == I2C2_Close()); // sit here until finished.
}

void I2C2_ReadNBytes(i2c2_address_t address, uint8_t *data, size_t len)
{
    while(!I2C2_Open(address)); // sit here until we get the bus..
    I2C2_SetBuffer(data,len);
    I2C2_MasterRead();
    while(I2C2_BUSY == I2C2_Close()); // sit here until finished.
}

void I2C2_ReadDataBlock(i2c2_address_t address, uint8_t reg, uint8_t *data, size_t len)
{
    i2c2_buffer_t bufferBlock; // result is little endian
    bufferBlock.data = data;
    bufferBlock.len = len;

    while(!I2C2_Open(address)); // sit here until we get the bus..
    I2C2_SetDataCompleteCallback(rdBlkRegCompleteHandler,&bufferBlock);
    I2C2_SetBuffer(&reg,1);
    I2C2_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C2_MasterWrite();
    while(I2C2_BUSY == I2C2_Close()); // sit here until finished.
}

static i2c2_operations_t rd1RegCompleteHandler(void *ptr)
{
    I2C2_SetBuffer(ptr,1);
    I2C2_SetDataCompleteCallback(NULL,NULL);
    return I2C2_RESTART_READ;
}

static i2c2_operations_t rd2RegCompleteHandler(void *ptr)
{
    I2C2_SetBuffer(ptr,2);
    I2C2_SetDataCompleteCallback(NULL,NULL);
    return I2C2_RESTART_READ;
}

static i2c2_operations_t wr1RegCompleteHandler(void *ptr)
{
    I2C2_SetBuffer(ptr,1);
    I2C2_SetDataCompleteCallback(NULL,NULL);
    return I2C2_CONTINUE;
}

static i2c2_operations_t wr2RegCompleteHandler(void *ptr)
{
    I2C2_SetBuffer(ptr,2);
    I2C2_SetDataCompleteCallback(NULL,NULL);
    return I2C2_CONTINUE;
}

static i2c2_operations_t rdBlkRegCompleteHandler(void *ptr)
{
    I2C2_SetBuffer(((i2c2_buffer_t *)ptr)->data,((i2c2_buffer_t*)ptr)->len);
    I2C2_SetDataCompleteCallback(NULL,NULL);
    return I2C2_RESTART_READ;
}
/**
  I2C2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c2.c

  @Summary
    This is the generated driver implementation file for the I2C2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

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

#include "i2c2_master.h"
#include <xc.h>

// I2C2 STATES
typedef enum {
    I2C2_IDLE = 0,
    I2C2_SEND_ADR_READ,
    I2C2_SEND_ADR_WRITE,
    I2C2_TX,
    I2C2_RX,
    I2C2_RCEN,
    I2C2_TX_EMPTY,      
    I2C2_SEND_RESTART_READ,
    I2C2_SEND_RESTART_WRITE,
    I2C2_SEND_RESTART,
    I2C2_SEND_STOP,
    I2C2_RX_ACK,
    I2C2_RX_NACK_STOP,
    I2C2_RX_NACK_RESTART,
    I2C2_RESET,
    I2C2_ADDRESS_NACK,

} i2c2_fsm_states_t;

// I2C2 Event callBack List
typedef enum {
    I2C2_DATA_COMPLETE = 0,
    I2C2_WRITE_COLLISION,
    I2C2_ADDR_NACK,
    I2C2_DATA_NACK,
    I2C2_TIMEOUT,
    I2C2_NULL
} i2c2_callbackIndex_t;

// I2C2 Status Structure
typedef struct
{
    i2c2_callback_t callbackTable[6];
    void *callbackPayload[6];           //  each callBack can have a payload
    uint16_t time_out;                  // I2C2 Timeout Counter between I2C2 Events.
    uint16_t time_out_value;            // Reload value for the timeouts
    i2c2_address_t address;             // The I2C2 Address
    uint8_t *data_ptr;                  // pointer to a data buffer
    size_t data_length;                 // Bytes in the data buffer
    i2c2_fsm_states_t state;            // Driver State
    i2c2_error_t error;
    unsigned addressNackCheck:1;
    unsigned busy:1;
    unsigned inUse:1;
    unsigned bufferFree:1;

} i2c2_status_t;

static void I2C2_SetCallback(i2c2_callbackIndex_t idx, i2c2_callback_t cb, void *ptr);
static void I2C2_MasterIsr(void);
static inline void I2C2_MasterFsm(void);

/* I2C2 interfaces */
static inline bool I2C2_MasterOpen(void);
static inline void I2C2_MasterClose(void);    
static inline uint8_t I2C2_MasterGetRxData(void);
static inline void I2C2_MasterSendTxData(uint8_t data);
static inline void I2C2_MasterEnableRestart(void);
static inline void I2C2_MasterDisableRestart(void);
static inline void I2C2_MasterStartRx(void);
static inline void I2C2_MasterStart(void);
static inline void I2C2_MasterStop(void);
static inline bool I2C2_MasterIsNack(void);
static inline void I2C2_MasterSendAck(void);
static inline void I2C2_MasterSendNack(void);
static inline void I2C2_MasterClearBusCollision(void);

/* Interrupt interfaces */
static inline void I2C2_MasterEnableIrq(void);
static inline bool I2C2_MasterIsIrqEnabled(void);
static inline void I2C2_MasterDisableIrq(void);
static inline void I2C2_MasterClearIrq(void);
static inline void I2C2_MasterSetIrq(void);
static inline void I2C2_MasterWaitForEvent(void);

static i2c2_fsm_states_t I2C2_DO_IDLE(void);
static i2c2_fsm_states_t I2C2_DO_SEND_ADR_READ(void);
static i2c2_fsm_states_t I2C2_DO_SEND_ADR_WRITE(void);
static i2c2_fsm_states_t I2C2_DO_TX(void);
static i2c2_fsm_states_t I2C2_DO_RX(void);
static i2c2_fsm_states_t I2C2_DO_RCEN(void);
static i2c2_fsm_states_t I2C2_DO_TX_EMPTY(void);
static i2c2_fsm_states_t I2C2_DO_SEND_RESTART_READ(void);
static i2c2_fsm_states_t I2C2_DO_SEND_RESTART_WRITE(void);
static i2c2_fsm_states_t I2C2_DO_SEND_RESTART(void);
static i2c2_fsm_states_t I2C2_DO_SEND_STOP(void);
static i2c2_fsm_states_t I2C2_DO_RX_ACK(void);
static i2c2_fsm_states_t I2C2_DO_RX_NACK_STOP(void);
static i2c2_fsm_states_t I2C2_DO_RX_NACK_RESTART(void);
static i2c2_fsm_states_t I2C2_DO_RESET(void);
static i2c2_fsm_states_t I2C2_DO_ADDRESS_NACK(void);


typedef i2c2_fsm_states_t (*fsmHandlerFunction)(void);
const fsmHandlerFunction fsmStateTable[] = {
    I2C2_DO_IDLE,
    I2C2_DO_SEND_ADR_READ,
    I2C2_DO_SEND_ADR_WRITE,
    I2C2_DO_TX,
    I2C2_DO_RX,
    I2C2_DO_RCEN,
    I2C2_DO_TX_EMPTY,
    I2C2_DO_SEND_RESTART_READ,
    I2C2_DO_SEND_RESTART_WRITE,
    I2C2_DO_SEND_RESTART,
    I2C2_DO_SEND_STOP,
    I2C2_DO_RX_ACK,
    I2C2_DO_RX_NACK_STOP,
    I2C2_DO_RX_NACK_RESTART,
    I2C2_DO_RESET,
    I2C2_DO_ADDRESS_NACK,
};

i2c2_status_t I2C2_Status = {0};

void I2C2_Initialize()
{
    SSP2STAT = 0x00;
    SSP2CON1 = 0x08;
    SSP2CON2 = 0x00;
    SSP2ADD  = 0x4F;
    SSP2CON1bits.SSPEN = 0;
}

i2c2_error_t I2C2_Open(i2c2_address_t address)
{
    i2c2_error_t returnValue = I2C2_BUSY;
    
    if(!I2C2_Status.inUse)
    {
        I2C2_Status.address = address;
        I2C2_Status.busy = 0;
        I2C2_Status.inUse = 1;
        I2C2_Status.addressNackCheck = 0;
        I2C2_Status.state = I2C2_RESET;
        I2C2_Status.time_out_value = 500; // MCC should determine a reasonable starting value here.
        I2C2_Status.bufferFree = 1;

        // set all the call backs to a default of sending stop
        I2C2_Status.callbackTable[I2C2_DATA_COMPLETE]=I2C2_CallbackReturnStop;
        I2C2_Status.callbackPayload[I2C2_DATA_COMPLETE] = NULL;
        I2C2_Status.callbackTable[I2C2_WRITE_COLLISION]=I2C2_CallbackReturnStop;
        I2C2_Status.callbackPayload[I2C2_WRITE_COLLISION] = NULL;
        I2C2_Status.callbackTable[I2C2_ADDR_NACK]=I2C2_CallbackReturnStop;
        I2C2_Status.callbackPayload[I2C2_ADDR_NACK] = NULL;
        I2C2_Status.callbackTable[I2C2_DATA_NACK]=I2C2_CallbackReturnStop;
        I2C2_Status.callbackPayload[I2C2_DATA_NACK] = NULL;
        I2C2_Status.callbackTable[I2C2_TIMEOUT]=I2C2_CallbackReturnReset;
        I2C2_Status.callbackPayload[I2C2_TIMEOUT] = NULL;
        
        I2C2_SetInterruptHandler(I2C2_MasterIsr);
        I2C2_MasterClearIrq();
        I2C2_MasterOpen();
        I2C2_MasterEnableIrq();
        returnValue = I2C2_NOERR;
    }
    return returnValue;
}

i2c2_error_t I2C2_Close(void)
{
    i2c2_error_t returnValue = I2C2_BUSY;
    if(!I2C2_Status.busy)
    {
        I2C2_Status.inUse = 0;
        I2C2_Status.address = 0xff;
        I2C2_MasterClearIrq();
        I2C2_MasterDisableIrq();
        I2C2_MasterClose();
        returnValue = I2C2_Status.error;
    }
    return returnValue;
}

i2c2_error_t I2C2_MasterOperation(bool read)
{
    i2c2_error_t returnValue = I2C2_BUSY;
    if(!I2C2_Status.busy)
    {
        I2C2_Status.busy = true;
        returnValue = I2C2_NOERR;

        if(read)
        {
            I2C2_Status.state = I2C2_SEND_ADR_READ;
        }
        else
        {
            I2C2_Status.state = I2C2_SEND_ADR_WRITE;
        }
        I2C2_MasterStart();
    }
    return returnValue;
}

i2c2_error_t I2C2_MasterRead(void)
{
    return I2C2_MasterOperation(true);
}

i2c2_error_t I2C2_MasterWrite(void)
{
    return I2C2_MasterOperation(false);
}

void I2C2_SetTimeOut(uint8_t timeOutValue)
{
    I2C2_MasterDisableIrq();
    I2C2_Status.time_out_value = timeOutValue;
    I2C2_MasterEnableIrq();
}

void I2C2_SetBuffer(void *buffer, size_t bufferSize)
{
    if(I2C2_Status.bufferFree)
    {
        I2C2_Status.data_ptr = buffer;
        I2C2_Status.data_length = bufferSize;
        I2C2_Status.bufferFree = false;
    }
}

void I2C2_SetDataCompleteCallback(i2c2_callback_t cb, void *ptr)
{
    I2C2_SetCallback(I2C2_DATA_COMPLETE, cb, ptr);
}

void I2C2_SetWriteCollisionCallback(i2c2_callback_t cb, void *ptr)
{
    I2C2_SetCallback(I2C2_WRITE_COLLISION, cb, ptr);
}

void I2C2_SetAddressNackCallback(i2c2_callback_t cb, void *ptr)
{
    I2C2_SetCallback(I2C2_ADDR_NACK, cb, ptr);
}

void I2C2_SetDataNackCallback(i2c2_callback_t cb, void *ptr)
{
    I2C2_SetCallback(I2C2_DATA_NACK, cb, ptr);
}

void I2C2_SetTimeoutCallback(i2c2_callback_t cb, void *ptr)
{
    I2C2_SetCallback(I2C2_TIMEOUT, cb, ptr);
}

void I2C2_SetInterruptHandler(void (* InterruptHandler)(void))
{
    MSSP2_InterruptHandler = InterruptHandler;
}

static void I2C2_SetCallback(i2c2_callbackIndex_t idx, i2c2_callback_t cb, void *ptr)
{
    if(cb)
    {
        I2C2_Status.callbackTable[idx] = cb;
        I2C2_Status.callbackPayload[idx] = ptr;
    }
    else
    {
        I2C2_Status.callbackTable[idx] = I2C2_CallbackReturnStop;
        I2C2_Status.callbackPayload[idx] = NULL;
    }
}

static void I2C2_MasterIsr()
{
    I2C2_MasterFsm();
}

static inline void I2C2_MasterFsm(void)
{
    I2C2_MasterClearIrq();

    if(I2C2_Status.addressNackCheck && I2C2_MasterIsNack())
    {
        I2C2_Status.state = I2C2_ADDRESS_NACK;
    }
    I2C2_Status.state = fsmStateTable[I2C2_Status.state]();
}


static i2c2_fsm_states_t I2C2_DO_IDLE(void)
{
    I2C2_Status.busy = false;
    I2C2_Status.error = I2C2_NOERR;
    return I2C2_RESET;
}

static i2c2_fsm_states_t I2C2_DO_SEND_ADR_READ(void)
{
    I2C2_Status.addressNackCheck = 1;
    I2C2_MasterSendTxData(I2C2_Status.address << 1 | 1);
    return I2C2_RCEN;
}

static i2c2_fsm_states_t I2C2_DO_SEND_ADR_WRITE(void)
{
    I2C2_Status.addressNackCheck = 1;
    I2C2_MasterSendTxData(I2C2_Status.address << 1);
    return I2C2_TX;
}

static i2c2_fsm_states_t I2C2_DO_TX(void)
{
    if(I2C2_MasterIsNack())
    {
        switch(I2C2_Status.callbackTable[I2C2_DATA_NACK](I2C2_Status.callbackPayload[I2C2_DATA_NACK]))
        {
            case I2C2_RESTART_READ:
                return I2C2_DO_SEND_RESTART_READ();
            case I2C2_RESTART_WRITE:
                  return I2C2_DO_SEND_RESTART_WRITE();
            default:
            case I2C2_CONTINUE:
            case I2C2_STOP:
                return I2C2_DO_SEND_STOP();
        }
    }
    else
    {
        I2C2_Status.addressNackCheck = 0;
        I2C2_MasterSendTxData(*I2C2_Status.data_ptr++);
        return (--I2C2_Status.data_length)?I2C2_TX:I2C2_TX_EMPTY;
    }
}

static i2c2_fsm_states_t I2C2_DO_RX(void)
{
    *I2C2_Status.data_ptr++ = I2C2_MasterGetRxData();
    if(--I2C2_Status.data_length)
    {
        I2C2_MasterSendAck();
        return I2C2_RCEN;
    }
    else
    {
        I2C2_Status.bufferFree = true;
        switch(I2C2_Status.callbackTable[I2C2_DATA_COMPLETE](I2C2_Status.callbackPayload[I2C2_DATA_COMPLETE]))
        {
            case I2C2_RESTART_WRITE:
            case I2C2_RESTART_READ:
                return I2C2_DO_RX_NACK_RESTART();
            default:
            case I2C2_CONTINUE:
            case I2C2_STOP:
                return I2C2_DO_RX_NACK_STOP();
        }
    }
}

static i2c2_fsm_states_t I2C2_DO_RCEN(void)
{
    I2C2_Status.addressNackCheck = 0;
    I2C2_MasterStartRx();
    return I2C2_RX;
}

static i2c2_fsm_states_t I2C2_DO_TX_EMPTY(void)
{
    I2C2_Status.bufferFree = true;
    switch(I2C2_Status.callbackTable[I2C2_DATA_COMPLETE](I2C2_Status.callbackPayload[I2C2_DATA_COMPLETE]))
    {
        case I2C2_RESTART_READ:
        case I2C2_RESTART_WRITE:
            return I2C2_DO_SEND_RESTART();
        case I2C2_CONTINUE:
            I2C2_MasterSetIrq();
            return I2C2_TX;
        default:
        case I2C2_STOP:
            return I2C2_DO_SEND_STOP();
    }
}

static i2c2_fsm_states_t I2C2_DO_RX_EMPTY(void)
{
    I2C2_Status.bufferFree = true;
    switch(I2C2_Status.callbackTable[I2C2_DATA_COMPLETE](I2C2_Status.callbackPayload[I2C2_DATA_COMPLETE]))
    {
        case I2C2_RESTART_WRITE:
            I2C2_MasterEnableRestart();
            return I2C2_SEND_RESTART_WRITE;
        case I2C2_RESTART_READ:
            I2C2_MasterEnableRestart();
            return I2C2_SEND_RESTART_READ;
        case I2C2_CONTINUE:
            return I2C2_RX;
        default:
        case I2C2_STOP:
            if(I2C2_Status.state != I2C2_SEND_RESTART_READ)
            {
                I2C2_MasterDisableRestart();
            }
            return I2C2_RESET;
    }
}

static i2c2_fsm_states_t I2C2_DO_SEND_RESTART_READ(void)
{
    I2C2_MasterEnableRestart();
    return I2C2_SEND_ADR_READ;
}

static i2c2_fsm_states_t I2C2_DO_SEND_RESTART_WRITE(void)
{
    I2C2_MasterEnableRestart();
    return I2C2_SEND_ADR_WRITE;
}


static i2c2_fsm_states_t I2C2_DO_SEND_RESTART(void)
{
    I2C2_MasterEnableRestart();
    return I2C2_SEND_ADR_READ;
}

static i2c2_fsm_states_t I2C2_DO_SEND_STOP(void)
{
    I2C2_MasterStop();
    return I2C2_IDLE;
}

static i2c2_fsm_states_t I2C2_DO_RX_ACK(void)
{
    I2C2_MasterSendAck();
    return I2C2_RCEN;
}


static i2c2_fsm_states_t I2C2_DO_RX_NACK_STOP(void)
{
    I2C2_MasterSendNack();
    return I2C2_SEND_STOP;
}

static i2c2_fsm_states_t I2C2_DO_RX_NACK_RESTART(void)
{
    I2C2_MasterSendNack();
    return I2C2_SEND_RESTART;
}

static i2c2_fsm_states_t I2C2_DO_RESET(void)
{
    I2C2_Status.busy = false;
    I2C2_Status.error = I2C2_NOERR;
    return I2C2_RESET;
}
static i2c2_fsm_states_t I2C2_DO_ADDRESS_NACK(void)
{
    I2C2_Status.addressNackCheck = 0;
    I2C2_Status.error = I2C2_FAIL;
    switch(I2C2_Status.callbackTable[I2C2_ADDR_NACK](I2C2_Status.callbackPayload[I2C2_ADDR_NACK]))
    {
        case I2C2_RESTART_READ:
        case I2C2_RESTART_WRITE:
            return I2C2_DO_SEND_RESTART();
        default:
            return I2C2_DO_SEND_STOP();
    }
}

void I2C2_BusCollisionIsr(void)
{
    I2C2_MasterClearBusCollision();
    I2C2_Status.state = I2C2_RESET;
}

i2c2_operations_t I2C2_CallbackReturnStop(void *funPtr)
{
    return I2C2_STOP;
}

i2c2_operations_t I2C2_CallbackReturnReset(void *funPtr)
{
    return I2C2_RESET_LINK;
}

i2c2_operations_t I2C2_CallbackRestartWrite(void *funPtr)
{
    return I2C2_RESTART_WRITE;
}

i2c2_operations_t I2C2_CallbackRestartRead(void *funPtr)
{
    return I2C2_RESTART_READ;
}



/* I2C2 Register Level interfaces */
static inline bool I2C2_MasterOpen(void)
{
    if(!SSP2CON1bits.SSPEN)
    {
        SSP2STAT = 0x00;
        SSP2CON1 = 0x08;
        SSP2CON2 = 0x00;
        SSP2ADD = 0x4F;
        SSP2CON1bits.SSPEN = 1;
        return true;
    }
    return false;
}

static inline void I2C2_MasterClose(void)
{
    //Disable I2C2
    SSP2CON1bits.SSPEN = 0;
}

static inline uint8_t I2C2_MasterGetRxData(void)
{
    return SSP2BUF;
}

static inline void I2C2_MasterSendTxData(uint8_t data)
{
    SSP2BUF  = data;
}

static inline void I2C2_MasterEnableRestart(void)
{
    SSP2CON2bits.RSEN = 1;
}

static inline void I2C2_MasterDisableRestart(void)
{
    SSP2CON2bits.RSEN = 0;
}

static inline void I2C2_MasterStartRx(void)
{
    SSP2CON2bits.RCEN = 1;
}

static inline void I2C2_MasterStart(void)
{
    SSP2CON2bits.SEN = 1;
}

static inline void I2C2_MasterStop(void)
{
    SSP2CON2bits.PEN = 1;
}

static inline bool I2C2_MasterIsNack(void)
{
    return SSP2CON2bits.ACKSTAT;
}

static inline void I2C2_MasterSendAck(void)
{
    SSP2CON2bits.ACKDT = 0;
    SSP2CON2bits.ACKEN = 1;
}

static inline void I2C2_MasterSendNack(void)
{
    SSP2CON2bits.ACKDT = 1;
    SSP2CON2bits.ACKEN = 1;
}

static inline void I2C2_MasterClearBusCollision(void)
{
    PIR3bits.BCL2IF = 0;
}


static inline bool I2C2_MasterIsRxBufFull(void)
{
    return SSP2STATbits.BF;
}

static inline void I2C2_MasterEnableIrq(void)
{
    PIE3bits.SSP2IE = 1;
}

static inline bool I2C2_MasterIsIrqEnabled(void)
{
    return PIE3bits.SSP2IE;
}

static inline void I2C2_MasterDisableIrq(void)
{
    PIE3bits.SSP2IE = 0;
}

static inline void I2C2_MasterClearIrq(void)
{
    PIR3bits.SSP2IF = 0;
}

static inline void I2C2_MasterSetIrq(void)
{
    PIR3bits.SSP2IF = 1;
}

static inline void I2C2_MasterWaitForEvent(void)
{
    while(1)
    {
        if(PIR3bits.SSP2IF)
        {    
            break;
        }
    }
}
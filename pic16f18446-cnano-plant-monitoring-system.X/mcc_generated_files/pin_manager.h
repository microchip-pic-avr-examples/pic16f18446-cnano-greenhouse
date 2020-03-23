/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.79.0
        Device            :  PIC16F18446
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set Relay_RL1 aliases
#define Relay_RL1_TRIS                 TRISAbits.TRISA1
#define Relay_RL1_LAT                  LATAbits.LATA1
#define Relay_RL1_PORT                 PORTAbits.RA1
#define Relay_RL1_WPU                  WPUAbits.WPUA1
#define Relay_RL1_OD                   ODCONAbits.ODCA1
#define Relay_RL1_ANS                  ANSELAbits.ANSA1
#define Relay_RL1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define Relay_RL1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define Relay_RL1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define Relay_RL1_GetValue()           PORTAbits.RA1
#define Relay_RL1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define Relay_RL1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define Relay_RL1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define Relay_RL1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define Relay_RL1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define Relay_RL1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define Relay_RL1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define Relay_RL1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set oledC_EN aliases
#define oledC_EN_TRIS                 TRISAbits.TRISA4
#define oledC_EN_LAT                  LATAbits.LATA4
#define oledC_EN_PORT                 PORTAbits.RA4
#define oledC_EN_WPU                  WPUAbits.WPUA4
#define oledC_EN_OD                   ODCONAbits.ODCA4
#define oledC_EN_ANS                  ANSELAbits.ANSA4
#define oledC_EN_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define oledC_EN_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define oledC_EN_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define oledC_EN_GetValue()           PORTAbits.RA4
#define oledC_EN_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define oledC_EN_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define oledC_EN_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define oledC_EN_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define oledC_EN_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define oledC_EN_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define oledC_EN_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define oledC_EN_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set oledC_RST aliases
#define oledC_RST_TRIS                 TRISAbits.TRISA5
#define oledC_RST_LAT                  LATAbits.LATA5
#define oledC_RST_PORT                 PORTAbits.RA5
#define oledC_RST_WPU                  WPUAbits.WPUA5
#define oledC_RST_OD                   ODCONAbits.ODCA5
#define oledC_RST_ANS                  ANSELAbits.ANSA5
#define oledC_RST_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define oledC_RST_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define oledC_RST_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define oledC_RST_GetValue()           PORTAbits.RA5
#define oledC_RST_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define oledC_RST_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define oledC_RST_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define oledC_RST_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define oledC_RST_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define oledC_RST_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define oledC_RST_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define oledC_RST_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set channel_ANB4 aliases
#define channel_ANB4_TRIS                 TRISBbits.TRISB4
#define channel_ANB4_LAT                  LATBbits.LATB4
#define channel_ANB4_PORT                 PORTBbits.RB4
#define channel_ANB4_WPU                  WPUBbits.WPUB4
#define channel_ANB4_OD                   ODCONBbits.ODCB4
#define channel_ANB4_ANS                  ANSELBbits.ANSB4
#define channel_ANB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define channel_ANB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define channel_ANB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define channel_ANB4_GetValue()           PORTBbits.RB4
#define channel_ANB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define channel_ANB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define channel_ANB4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define channel_ANB4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define channel_ANB4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define channel_ANB4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define channel_ANB4_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define channel_ANB4_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set channel_ANB6 aliases
#define channel_ANB6_TRIS                 TRISBbits.TRISB6
#define channel_ANB6_LAT                  LATBbits.LATB6
#define channel_ANB6_PORT                 PORTBbits.RB6
#define channel_ANB6_WPU                  WPUBbits.WPUB6
#define channel_ANB6_OD                   ODCONBbits.ODCB6
#define channel_ANB6_ANS                  ANSELBbits.ANSB6
#define channel_ANB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define channel_ANB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define channel_ANB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define channel_ANB6_GetValue()           PORTBbits.RB6
#define channel_ANB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define channel_ANB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define channel_ANB6_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define channel_ANB6_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define channel_ANB6_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define channel_ANB6_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define channel_ANB6_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define channel_ANB6_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)
#define RB7_SetAnalogMode()         do { ANSELBbits.ANSB7 = 1; } while(0)
#define RB7_SetDigitalMode()        do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set oledC_RW aliases
#define oledC_RW_TRIS                 TRISCbits.TRISC0
#define oledC_RW_LAT                  LATCbits.LATC0
#define oledC_RW_PORT                 PORTCbits.RC0
#define oledC_RW_WPU                  WPUCbits.WPUC0
#define oledC_RW_OD                   ODCONCbits.ODCC0
#define oledC_RW_ANS                  ANSELCbits.ANSC0
#define oledC_RW_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define oledC_RW_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define oledC_RW_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define oledC_RW_GetValue()           PORTCbits.RC0
#define oledC_RW_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define oledC_RW_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define oledC_RW_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define oledC_RW_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define oledC_RW_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define oledC_RW_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define oledC_RW_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define oledC_RW_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set Relay_RL2 aliases
#define Relay_RL2_TRIS                 TRISCbits.TRISC1
#define Relay_RL2_LAT                  LATCbits.LATC1
#define Relay_RL2_PORT                 PORTCbits.RC1
#define Relay_RL2_WPU                  WPUCbits.WPUC1
#define Relay_RL2_OD                   ODCONCbits.ODCC1
#define Relay_RL2_ANS                  ANSELCbits.ANSC1
#define Relay_RL2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define Relay_RL2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define Relay_RL2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define Relay_RL2_GetValue()           PORTCbits.RC1
#define Relay_RL2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define Relay_RL2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define Relay_RL2_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define Relay_RL2_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define Relay_RL2_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define Relay_RL2_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define Relay_RL2_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define Relay_RL2_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set channel_ANC2 aliases
#define channel_ANC2_TRIS                 TRISCbits.TRISC2
#define channel_ANC2_LAT                  LATCbits.LATC2
#define channel_ANC2_PORT                 PORTCbits.RC2
#define channel_ANC2_WPU                  WPUCbits.WPUC2
#define channel_ANC2_OD                   ODCONCbits.ODCC2
#define channel_ANC2_ANS                  ANSELCbits.ANSC2
#define channel_ANC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define channel_ANC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define channel_ANC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define channel_ANC2_GetValue()           PORTCbits.RC2
#define channel_ANC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define channel_ANC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define channel_ANC2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define channel_ANC2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define channel_ANC2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define channel_ANC2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define channel_ANC2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define channel_ANC2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set oledC_DC aliases
#define oledC_DC_TRIS                 TRISCbits.TRISC3
#define oledC_DC_LAT                  LATCbits.LATC3
#define oledC_DC_PORT                 PORTCbits.RC3
#define oledC_DC_WPU                  WPUCbits.WPUC3
#define oledC_DC_OD                   ODCONCbits.ODCC3
#define oledC_DC_ANS                  ANSELCbits.ANSC3
#define oledC_DC_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define oledC_DC_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define oledC_DC_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define oledC_DC_GetValue()           PORTCbits.RC3
#define oledC_DC_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define oledC_DC_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define oledC_DC_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define oledC_DC_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define oledC_DC_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define oledC_DC_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define oledC_DC_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define oledC_DC_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set oledC_nCS aliases
#define oledC_nCS_TRIS                 TRISCbits.TRISC7
#define oledC_nCS_LAT                  LATCbits.LATC7
#define oledC_nCS_PORT                 PORTCbits.RC7
#define oledC_nCS_WPU                  WPUCbits.WPUC7
#define oledC_nCS_OD                   ODCONCbits.ODCC7
#define oledC_nCS_ANS                  ANSELCbits.ANSC7
#define oledC_nCS_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define oledC_nCS_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define oledC_nCS_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define oledC_nCS_GetValue()           PORTCbits.RC7
#define oledC_nCS_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define oledC_nCS_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define oledC_nCS_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define oledC_nCS_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define oledC_nCS_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define oledC_nCS_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define oledC_nCS_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define oledC_nCS_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/
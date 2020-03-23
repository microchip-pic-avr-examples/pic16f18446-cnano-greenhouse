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

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/oledC_example.h"
#include "HTS221.h"
#include "analog_sensors.h"
#include "greenhouse_display.h"

#define HUMIDITY_VALUE          55
#define HUMIDIY_ERROR           3
#define SOIL_MOISTURE_VALUE     30
#define SOIL_MOISTURE_ERROR     3
#define OPTIMAL_WATER_LEVEL     20

volatile bool update = false;
volatile bool useWaterPump = false;
bool fanEngaged = false;
bool waterPumpEngaged = false;
bool refillMessage = false;
float temperature, humidity;
uint8_t soilMoisture, waterLevel;

static void GREEN_HOUSE_timerInterrupt(void);
static void GREEN_HOUSE_adjustHumidity();
static void GREEN_HOUSE_adjustSoilMoisture();
static void GREEN_HOUSE_readSensors(void);
static void GREEN_HOUSE_displayInfo(void);

/* Interrupt every 1 second to update the sensors, screen and adjust humidity */
static void GREEN_HOUSE_timer0Interrupt(void) {
    update = true;
}

void GREEN_HOUSE_init(void) {
    HTS221_init();
    GREEN_HOUSE_DISPLAY_init();

    TMR0_SetInterruptHandler(GREEN_HOUSE_timer0Interrupt);
    TMR0_StartTimer();
}

static void GREEN_HOUSE_adjustHumidity() {
    if (humidity > HUMIDITY_VALUE && !fanEngaged) {
        fanEngaged = true;
        RELAY_RL2_Engage();
    }

    if (humidity < (HUMIDITY_VALUE - HUMIDIY_ERROR) && fanEngaged) {
        fanEngaged = false;
        RELAY_RL2_Disengage();
    }
}

static void GREEN_HOUSE_adjustSoilMoisture() {
    if (soilMoisture < SOIL_MOISTURE_VALUE && !waterPumpEngaged) {
        waterPumpEngaged = true;
        RELAY_RL1_Engage();
    }

    if (soilMoisture > (SOIL_MOISTURE_VALUE + SOIL_MOISTURE_ERROR) && waterPumpEngaged) {
        waterPumpEngaged = false;
        RELAY_RL1_Disengage();
    }
}

static void GREEN_HOUSE_readSensors(void) {
    temperature = HTS221_readTemperature();
    humidity = HTS221_readHumidity();
    soilMoisture = ANALOG_readSoilMoisture();
    waterLevel = ANALOG_readWaterLevel();
}

static void GREEN_HOUSE_displayInfo(void) {
    GREEN_HOUSE_DISPLAY_temperature(temperature);
    GREEN_HOUSE_DISPLAY_humidity(humidity);
    GREEN_HOUSE_DISPLAY_soilMoisture(soilMoisture);
    GREEN_HOUSE_DISPLAY_waterLevel(waterLevel);

    if (waterLevel <= OPTIMAL_WATER_LEVEL && !refillMessage) {
        GREEN_HOUSE_DISPLAY_refillMessage(true);
        refillMessage = true;
    }

    if (waterLevel > OPTIMAL_WATER_LEVEL && refillMessage) {
        GREEN_HOUSE_DISPLAY_refillMessage(false);
        refillMessage = false;
    }
}

void GREEN_HOUSE_runApplication(void) {
    
    if (update) {
        /* Clear Watch Dog Timer */
        CLRWDT();

        GREEN_HOUSE_readSensors();
        GREEN_HOUSE_displayInfo();

        GREEN_HOUSE_adjustHumidity();
        GREEN_HOUSE_adjustSoilMoisture();
        
        update = false;
    }
}

void main(void) {
    SYSTEM_Initialize();

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    GREEN_HOUSE_init();

    while (1) {
        GREEN_HOUSE_runApplication();
    }
}

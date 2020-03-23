<div id="readme" class="Box-body readme blob js-code-block-container">
 <article class="markdown-body entry-content p-3 p-md-6" itemprop="text"><p><a href="https://www.microchip.com" rel="nofollow"><img src="images/MicrochipLogo.png" alt="MCHP" style="max-width:100%;"></a></p>

# Plant Monitoring System using PIC16F18446

## Objective:
Plant monitoring system that provides automated control of the soil moisture and air humidity in a greenhouse. The application features a display that shows all the environment information required for the proper development of a plant (humidity, temperature, soil moisture).

## Resources:
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- MPLAB® Code Configurator (MCC) 3.95.0 or newer [(microchip.com/mplab/mplab-code-configurator)](https://www.microchip.com/mplab/mplab-code-configurator)
- PIC16F18446 Curiosity Nano [(DM164144)](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/DM164144)
- Curiosity Nano Base for Click Boards™ [(AC164162)](https://www.microchip.com/Developmenttools/ProductDetails/AC164162)
- OLED C click [(oled-c-click)](https://www.mikroe.com/oled-c-click)
- RELAY click [(relay-click)](https://www.mikroe.com/relay-click)
- Temp&Hum click [(temp-hum-click)](https://www.mikroe.com/temp-hum-click)
- [PIC16F18446 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/40001985B.pdf) for more information or specifications.

## Hardware Configuration:

### Peripherals used:
- MSSP1 (SPI) to display data on OLED C click
- MSSP2 (I2C) to read data from Temp&Hum click
- ADCC to read analog sensors (soil moisture, water level sensor)
- TMR0 to generate interrupt every second

### Schematic:
<img src="images/schematic.png" alt="Hardware Setup"/>

## Results:
<img src="images/greenhouse.png" alt="Hardware Setup"/>

/*
 * ***************************************************************************
 * Component:    MAX17048 - Fuel Gauge
 * Manufacturer: Adafruit
 * Product:      MAX17048 - LiPoly / LiIon Fuel Gauge and Battery Monitor - STEMMA JST PH & QT / Qwiic
 * Product ID:   5580
 *
 * Product Page:
 *     https://www.adafruit.com/product/5580
 *
 * Datasheet:
 *     https://www.analog.com/media/en/technical-documentation/data-sheets/MAX17048-MAX17049.pdf
 *
 * ***************************************************************************
 */

#ifndef BR_MAX17048_H
#define BR_MAX17048_H

#include <Arduino.h>
#include <Wire.h>


class BR_MAX17048 {
    
    public:
        // MAX17048 I2C Address
        static constexpr uint8_t I2C_ADR = 0x36;

        // MAX17048 Registers
        static constexpr uint8_t VCELL = 0x02;            // ADC measurement of VCELL.
        static constexpr uint8_t SOC = 0x04;              // Battery state of charge.
        static constexpr uint8_t MODE = 0x06;             // Initiates quick-start, reports hibernate mode, and enables sleep mode.
        static constexpr uint8_t VERSION = 0x08;          // IC production version.
        static constexpr uint8_t HIBRT = 0x0A;            // Controls thresholds for entering and exiting hibernate mode.
        static constexpr uint8_t CONFIG = 0x0C;           // Compensation to optimize performance, sleep mode, alert indicators, and configuration.
        static constexpr uint8_t VALRT = 0x14;            // Configures the VCELL range outside of which alerts are generated.
        static constexpr uint8_t CRATE = 0x16;            // Approximate charge or discharge rate of the battery.
        static constexpr uint8_t VRESET_ID = 0x18;        // Configures VCELL threshold below which the IC resets itself, ID is a one-time factoryprogrammable identifier.
        static constexpr uint8_t STATUS = 0x1A;           // Indicates overvoltage, undervoltage, SOC change, SOC low, and reset alerts.
        static constexpr uint8_t TABLE = 0x40;            // Configures battery parameters.
        static constexpr uint8_t CMD = 0xFE;              // Sends POR command.


        // Constructor
        BR_MAX17048(uint8_t i2c_address = I2C_ADR);

        // Initialization
        bool begin();

        // Battery Measurements
        float getStateOfCharge();
        float getCellVoltage();
        float getCRate();


    private:

        // Configuration
        uint8_t _i2c_address;


        // Register Communication
        uint16_t readRegisterUnsigned(uint8_t reg);
        int16_t readRegisterSigned(uint8_t reg);

};



#endif

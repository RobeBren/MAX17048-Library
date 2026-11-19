#include <BR_MAX17048.h>

BR_MAX17048::BR_MAX17048(uint8_t i2c_address) {
    _i2c_address = i2c_address;
}


bool BR_MAX17048::begin() {
    Wire.beginTransmission(_i2c_address);

    if (Wire.endTransmission() == 0) {
        return true;
    }

    return false;
}


uint16_t BR_MAX17048::readRegisterUnsigned(uint8_t reg) {
    Wire.beginTransmission(_i2c_address);
    Wire.write(reg);

    Wire.endTransmission();

    // Request 2-bytes of data from MAX17048 within the given register
    Wire.requestFrom(_i2c_address, 2);

    if (Wire.available() == 2) {
        uint8_t msb = Wire.read();
        uint8_t lsb = Wire.read();
    
        uint16_t rawData = ((uint16_t)msb << 8) | lsb;

        return rawData;
    }else {
        Serial.println("Error in reading 2-bytes from MAX17048 register!");
        return 0x0000;
    }
}


int16_t BR_MAX17048::readRegisterSigned(uint8_t reg) {
    Wire.beginTransmission(_i2c_address);
    Wire.write(reg);

    Wire.endTransmission();

    // Request 2-bytes of data from MAX17048 within the given register
    Wire.requestFrom(_i2c_address, 2);

    if (Wire.available() == 2) {
        uint8_t msb = Wire.read();
        uint8_t lsb = Wire.read();
    
        uint16_t rawData = ((uint16_t)msb << 8) | lsb;

        return (int16_t)rawData;
    }else {
        Serial.println("Error in reading 2-bytes from MAX17048 register!");
        return 0x0000;
    }
}


float BR_MAX17048::getStateOfCharge() {
    uint16_t rawData = readRegisterUnsigned(BR_MAX17048::SOC);
    if (rawData == 0x0000) {
        return -1.0;
    }else {
        return rawData / 256.0;
    }
}


float BR_MAX17048::getCellVoltage() {
    uint16_t rawData = readRegisterUnsigned(BR_MAX17048::VCELL);
    if (rawData == 0x0000) {
        return -1.0;
    }else {
        return 0.000078125 * rawData;
    }

}


float BR_MAX17048::getCRate() {
    int16_t rawData = readRegisterSigned(BR_MAX17048::CRATE);
    if (rawData == 0x0000) {
        return -1.0;
    }else {
        return rawData * 0.208;
    }
}

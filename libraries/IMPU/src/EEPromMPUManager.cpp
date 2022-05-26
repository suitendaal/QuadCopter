#include "EEPromMPUManager.h"
#include "EEPROM.h"
#include "Arduino.h"

int EEPromMPUManager::readIntFromEeProm(int address)
{
    int val;
    val = EEPROM.read(address);
    val |= EEPROM.read(address + 1) << 8;
    return val;
}

void EEPromMPUManager::writeIntToEeProm(int address, int value)
{
    EEPROM.update(address, value & 0xff); // Write lower bite
    EEPROM.update(address + 1, value >> 8); // Write upper bite
}

int EEPromMPUManager::getXGyroOffset()
{
    return this->readIntFromEeProm(OffsetAddr::GyroX);
}

int EEPromMPUManager::getYGyroOffset()
{
    return this->readIntFromEeProm(OffsetAddr::GyroY);
}

int EEPromMPUManager::getZGyroOffset()
{
    return this->readIntFromEeProm(OffsetAddr::GyroZ);
}

int EEPromMPUManager::getXAccelOffset()
{
    return this->readIntFromEeProm(OffsetAddr::AccelX);
}

int EEPromMPUManager::getYAccelOffset()
{
    return this->readIntFromEeProm(OffsetAddr::AccelY);
}

int EEPromMPUManager::getZAccelOffset()
{
    return this->readIntFromEeProm(OffsetAddr::AccelZ);
}

void EEPromMPUManager::setXGyroOffset(int offset)
{
    this->writeIntToEeProm(OffsetAddr::GyroX, offset);
}

void EEPromMPUManager::setYGyroOffset(int offset)
{
    this->writeIntToEeProm(OffsetAddr::GyroY, offset);
}

void EEPromMPUManager::setZGyroOffset(int offset)
{
    this->writeIntToEeProm(OffsetAddr::GyroZ, offset);
}

void EEPromMPUManager::setXAccelOffset(int offset)
{
    this->writeIntToEeProm(OffsetAddr::AccelX, offset);
}

void EEPromMPUManager::setYAccelOffset(int offset)
{
    this->writeIntToEeProm(OffsetAddr::AccelY, offset);
}

void EEPromMPUManager::setZAccelOffset(int offset)
{
    this->writeIntToEeProm(OffsetAddr::AccelZ, offset);
}

bool EEPromMPUManager::getMPUCalibFlag()
{
    return (this->readIntFromEeProm(this->calibFlagAddr) == this->calibFlagTrue);
}

void EEPromMPUManager::setMPUCalibFlag()
{
    this->writeIntToEeProm(this->calibFlagAddr, this->calibFlagTrue);
}

void EEPromMPUManager::resetMPUCalibFlag()
{
    this->writeIntToEeProm(this->calibFlagAddr, this->calibFlagFalse);
    Serial.println("Calibration flag reset.");
}

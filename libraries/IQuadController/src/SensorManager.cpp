#include "SensorManager.h"
#include "Arduino.h"

SensorManager::SensorManager(IMPU& mpu, IRemoteController& remoteController)
    : mpu(mpu), remoteController(remoteController)
{
}

bool SensorManager::init()
{
    bool result = this->mpu.init() && this->remoteController.init();

    // Update MPU for 10 seconds so values have stabilized.
    long int currentTime = millis();
    while (millis() - currentTime < 10000) {
        this->mpu.update();
    }
    return result;
}

bool SensorManager::update()
{
    return this->mpu.update() && this->remoteController.update();
}

IMPU& SensorManager::getMPU()
{
    return this->mpu;
}

IRemoteController& SensorManager::getRemoteController()
{
    return this->remoteController;
}

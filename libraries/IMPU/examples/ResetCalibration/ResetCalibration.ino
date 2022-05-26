#include "IMPU.h"
#include "IMPUSampleConfig.h" // Create your own!

IMPUSampleConfig config;
IMPU& mpu = config.getMPU();

void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (!mpu.resetCalibration()) {
        while (true) {
            // Failure.
        }
    }
    delay(2000);
}

void loop() {
}

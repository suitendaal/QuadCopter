#include "IMPU.h"
#include "IMPUSampleConfig.h" // Create your own!

IMPUSampleConfig config;
IMPU& mpu = config.getMPU();

void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (!mpu.init()) {
        while (true) {
            // Failure
        }
    }
    delay(100);
}

void loop() {
    VectorFloat ypr;
    if (mpu.update()) {
        bool success = mpu.getYPR(ypr);

        Serial.print(ypr.x);
        Serial.print("\t");
        Serial.print(ypr.y);
        Serial.print("\t");
        Serial.println(ypr.z);
    }
    else {
        Serial.println("Updating MPU failed.");
    }
    
    delay(100);
}

#include "ESCSampleConfig.h"

ESCSampleConfig config;
IQuadMotors& quad = config.getQuadMotors();

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);

	quad.init();
	quad.calibrate();
}

// the loop function runs over and over again until power down or reset
void loop() {
}

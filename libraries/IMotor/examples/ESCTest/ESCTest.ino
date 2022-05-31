#include "ESCSampleConfig.h"

ESCSampleConfig config;
IQuadMotors& quad = config.getQuadMotors();

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);

	if (!quad.init()) {
		while (true) {
			// Failure.
		}
	}

	if (!quad.arm()) {
		while (true) {
			// Failure.
		}
	}
	quad.arm();

	// 7 seconds to connect esc to battery now
	delay(7000);
	Serial.println("ESCs should be connected now");
}

// the loop function runs over and over again until power down or reset
void loop() {
	// put your main code here, to run repeatedly:
	Serial.print("Speed of ");
	Serial.println(0.1 * 100);
	quad.setSpeed(0.1 * IQuadMotors::MaxSpeed);
	delay(2000);

	Serial.print("Speed of ");
	Serial.println(0.3 * 100);
	quad.setSpeed(0.3 * IQuadMotors::MaxSpeed);
	delay(2000);
}

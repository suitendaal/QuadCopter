#include "ControllerSampleConfig.h"

ControllerSampleConfig config;
IController& controller = config.getController();

void setup() {
	Serial.begin(115200);
	if (!controller.init()) {
		Serial.println("Initialization of controller went wrong.");
		while (true)
		{
			// Failure.
		}
	}
	Serial.println("Controller is initialized.");
}

void loop() {
	// controller.update();
}

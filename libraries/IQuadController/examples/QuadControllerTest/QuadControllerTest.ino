#include "ControllerSampleConfig.h"

ControllerSampleConfig config;
IController& controller = config.getController();
unsigned long currentTime;

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

	currentTime = millis();
}

void loop() {
	if (!controller.update()) {
		Serial.println("Something went wrong in updating the controller...");
	}

	Serial.println(millis() - currentTime);
	currentTime = millis();
}

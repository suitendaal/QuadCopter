#include "ControllerSampleConfig.h"

ControllerSampleConfig config;
IControlManager& controller = config.getController();
unsigned long currentTime;

void setup() {
	Serial.begin(115200);
	Serial.println("Initializing...");
	if (!controller.init()) {
		Serial.println("Initialization of controller went wrong.");
		while (true)
		{
			// Failure.
		}
	}
	Serial.println("Controller is initialized.");
	delay(5000);
	Serial.println("Starting...");

	currentTime = millis();
}

void loop() {
	if (!controller.updateSensors()) {
		Serial.println("Something went wrong in updating the controller...");
	}

	Serial.println(controller.toString());

	delay(100);
	currentTime = millis();
}

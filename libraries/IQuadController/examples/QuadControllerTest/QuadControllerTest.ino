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

	currentTime = millis();
}

void loop() {
	if (!controller.update()) {
		Serial.println("Something went wrong in updating the controller...");
	}

	Serial.print("Time since last update: ");
	Serial.print(millis() - currentTime);
	Serial.println(" ms");

	delay(10);
	currentTime = millis();
}

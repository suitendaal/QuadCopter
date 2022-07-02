#include "IRemoteController.h"
#include "SerialController.h"

SerialController mContr;
IRemoteController& controller = mContr;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	controller.init();
}

// the loop function runs over and over again until power down or reset
void loop() {
	controller.update();
	//if (controller.getVelRef() > 0) {
	Serial.println("hoi");
		Serial.println(controller.getVelRef());
		Serial.println(controller.getKRef());
	//}
	delay(100);
}

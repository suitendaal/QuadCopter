#pragma once

#include "QuadMotors.h"
#include "EEPromMPUManager.h"
#include "WMPU.h"
#include "SerialController.h"
#include "QuadController.h"
#include "IControlManager.h"
#include "SensorManager.h"
#include "Controller.h"

class ControllerSampleConfig
{
private:
	// Motors
	int quadPins[4] = { 3, 5, 6, 7 };
	QuadMotors quad = QuadMotors(quadPins);

	// Sensors
	EEPromMPUManager eePromMPUManager;
	WMPU mpu = WMPU(eePromMPUManager);
	SerialController remoteController;
	SensorManager sensors = SensorManager(mpu, remoteController);

	// Controllers
	Controller mController;

	// Quadcontroller
	QuadController controller = QuadController(sensors, quad, mController);
public:
	IControlManager& getController();
};


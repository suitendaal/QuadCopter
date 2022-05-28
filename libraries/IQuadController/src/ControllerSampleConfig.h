#pragma once

#include "QuadMotors.h"
#include "EEPromMPUManager.h"
#include "WMPU.h"
#include "QuadController.h"
#include "IController.h"

class ControllerSampleConfig
{
private:
	int quadPins[4] = { 3, 5, 6, 7 };
	QuadMotors quad = QuadMotors(quadPins[0], quadPins[1], quadPins[2], quadPins[3]);
	EEPromMPUManager eePromMPUManager;
	WMPU mpu = WMPU(eePromMPUManager);
	QuadController controller = QuadController(mpu, quad);
public:
	IController& getController();
};


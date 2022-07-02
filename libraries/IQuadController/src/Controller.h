#pragma once

#include "IController.h"
#include "PID.h"

class Controller : public IController
{
private:
	PID yawPID;
	PID pitchPID;
	PID rollPID;
public:
	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool calculate(ISensorManager& sensors, float(&motorSpeeds)[IQuadMotors::Motors]) override;
};


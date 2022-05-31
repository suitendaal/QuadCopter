#pragma once

#include "IController.h"

class Controller : public IController
{
	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool calculate(ISensorManager& sensors, float(&motorSpeeds)[IQuadMotors::Motors]) override;
};


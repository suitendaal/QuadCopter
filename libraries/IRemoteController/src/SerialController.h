#pragma once

#include "IRemoteController.h"

class SerialController : public IRemoteController
{
private:
	float velRef = 0;
public:
	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool update() override;

	/// <inheritdoc/>
	virtual float getVelRef() override;
};


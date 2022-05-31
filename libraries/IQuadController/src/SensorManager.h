#pragma once

#include "ISensorManager.h"

class SensorManager : public ISensorManager
{
private:
	IMPU& mpu;
	IRemoteController& remoteController;
public:
	SensorManager(IMPU& mpu, IRemoteController& remoteController);

	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool update() override;

	/// <inheritdoc/>
	virtual IMPU& getMPU() override;

	/// <inheritdoc/>
	virtual IRemoteController& getRemoteController() override;
};


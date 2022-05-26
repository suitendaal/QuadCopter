#pragma once

#include "IEEPromMPU.h"

class EEPromMPUManager : public IEEPromMPU
{
private:
	enum OffsetAddr
	{
		GyroX = 2,
		GyroY = 4,
		GyroZ = 6,
		AccelX = 8,
		AccelY = 10,
		AccelZ = 12
	};
	const int calibFlagAddr = 0;
	const int calibFlagTrue = 77;
	const int calibFlagFalse = 0;

	int readIntFromEeProm(int address);
	void writeIntToEeProm(int address, int value);

public:
	virtual int getXGyroOffset() override;
	virtual int getYGyroOffset() override;
	virtual int getZGyroOffset() override;
	virtual int getXAccelOffset() override;
	virtual int getYAccelOffset() override;
	virtual int getZAccelOffset() override;

	virtual void setXGyroOffset(int offset) override;
	virtual void setYGyroOffset(int offset) override;
	virtual void setZGyroOffset(int offset) override;
	virtual void setXAccelOffset(int offset) override;
	virtual void setYAccelOffset(int offset) override;
	virtual void setZAccelOffset(int offset) override;

	virtual bool getMPUCalibFlag() override;
	virtual void setMPUCalibFlag() override;
	virtual void resetMPUCalibFlag() override;
};


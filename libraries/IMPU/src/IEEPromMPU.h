#pragma once

class IEEPromMPU {
public:
	// Offset getters
	virtual int getXGyroOffset() = 0;
	virtual int getYGyroOffset() = 0;
	virtual int getZGyroOffset() = 0;
	virtual int getXAccelOffset() = 0;
	virtual int getYAccelOffset() = 0;
	virtual int getZAccelOffset() = 0;

	// Offset setters
	virtual void setXGyroOffset(int offset) = 0;
	virtual void setYGyroOffset(int offset) = 0;
	virtual void setZGyroOffset(int offset) = 0;
	virtual void setXAccelOffset(int offset) = 0;
	virtual void setYAccelOffset(int offset) = 0;
	virtual void setZAccelOffset(int offset) = 0;

	// Calibration flag
	virtual bool getMPUCalibFlag() = 0;
	virtual void setMPUCalibFlag() = 0; // Sets it to true value
	virtual void resetMPUCalibFlag() = 0; // Sets it to false value
};


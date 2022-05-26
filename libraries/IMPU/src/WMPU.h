#pragma once

#include "IMPU.h"
#include "IEEPromMPU.h"

class WMPU : public IMPU {
protected:
	/// <summary>
	/// EEPROM manager for storing calibration offsets.
	/// </summary>
	IEEPromMPU& eePromMPUManager;

	/// <summary>
	/// FIFO storage buffer for reading MPU values.
	/// </summary>
	uint8_t fifoBuffer[64];

	/// <summary>
	/// Sets hardcoded offsets.
	/// </summary>
	void guessOffsets();

	/// <summary>
	/// Read calibration from EEPROM.
	/// </summary>
	void loadCalibration();

	/// <summary>
	/// Initializations up to but not calibration.
	/// </summary>
	/// <returns>Devstatus indicating whether the initializations have succeeded.</returns>
	int begin();
public:
	/// <summary>
	/// Creates an instance of the WMPU class.
	/// </summary>
	WMPU(IEEPromMPU& iEePromMPUManager);

	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool update() override;

	/// <inheritdoc/>
	virtual bool getYPR(VectorFloat& ypr) override;

	/// <inheritdoc/>
	virtual bool calibrate() override;

	/// <inheritdoc/>
	virtual bool isCalibrated() override;

	/// <inheritdoc/>
	virtual bool resetCalibration() override;
};

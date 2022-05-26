#pragma once

#include "IMPU.h"
#include "WMPU.h"
#include <EEPromMPUManager.h>

class IMPUSampleConfig
{
private:
	EEPromMPUManager eePromManager;
	WMPU mpu = WMPU(eePromManager);

public:
	IMPU& getMPU();
};


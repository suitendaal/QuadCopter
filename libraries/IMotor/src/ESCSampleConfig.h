#pragma once

#include "IQuadMotors.h"
#include "QuadMotors.h"

class ESCSampleConfig
{
private:
	QuadMotors quadMotors = QuadMotors((int[4]){ 3, 5, 6, 7 });
public:
	IQuadMotors& getQuadMotors();
};


#pragma once

#include "timer.h"

class JobType
{
private:
	TimerType waitTime;
public:
	void IncrementWaitTime();
	int GetWaitTime() const; 
};
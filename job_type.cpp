#include "job_type.h"

void JobType::IncrementWaitTime()
{
	waitTime.Increment();
}

int JobType::GetWaitTime() const
{
	return waitTime.GetTime();
}
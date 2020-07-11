#pragma once

#include "timer.h"

enum class StatusType{BUSY, FREE};

class ServerType
{
private:
	StatusType status{ StatusType::FREE};
	TimerType timeRemaining;
public:
	bool IsFree() const;
	void SetBusy();
	void DecrementTimeRemaining();
	void SetTimeRemaining(int time);
};
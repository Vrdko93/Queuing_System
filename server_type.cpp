#include "server_type.h"

bool ServerType::IsFree() const
{
	return status == StatusType::FREE;
}

void ServerType::SetBusy()
{
	status = StatusType::BUSY;
}

void ServerType::DecrementTimeRemaining()
{
	timeRemaining.Decrement();
	if (timeRemaining.GetTime() == 0)
		status = StatusType::FREE;
}

void ServerType::SetTimeRemaining(int time)
{
	timeRemaining.SetTimer(time);
}
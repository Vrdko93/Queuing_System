#include "timer.h"

TimerType::TimerType()
{
	count = 0;
}

void TimerType::SetTimer(int value)
{
	count = value;
}

void TimerType::Increment()
{
	count++;
}

void TimerType::Decrement()
{
	count--;
}
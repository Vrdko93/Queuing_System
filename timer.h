#pragma once

class TimerType
{
private:
	int count;
public:
	TimerType();
	void SetTimer(int value);
	void Increment();
	void Decrement();
	int GetTime() const { return count; }
};
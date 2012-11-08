#pragma once

#define MaxTimers				5
#define CompareTimer			0
#define SiTimer					1
#define PiTimer					2
#define ViTimer					3
#define RspTimer				4

class Timers
{
public:
	Timers();
	int  CurrentTimerType;
	int  Timer;
	int  NextTimer[MaxTimers];
	bool Active[MaxTimers];

	void ChangeCompareTimer(word compare, word count);
	void ChangeTimer (int Type, int Value, word compare, word count);
	void CheckTimer(word compare, word count);
};
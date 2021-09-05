#pragma once
#include "SingletonBase.h"


class TimeManager : public SingletonBase<TimeManager>
{
public:
	TimeManager();
	~TimeManager();

public:
	HRESULT Init();

	void StartTimeStamp();
	void EndTimeStamp();

	void CheckTime();
	float GetElaspedTimeMS() const;
	float GetElaspedTimeSec() const;


	bool FPSCheck();

	// Getter
	float GetTargetElaspedTimeSec() { return _TargetElaspedTimeSec; }
	float GetFPS() { return _FPS; }

private:
	__int64 _Frequency;

	LARGE_INTEGER _StartTimeStamp;
	LARGE_INTEGER _EndTimeStamp;

	__int64 _ElaspedTime;


	float _FPS;						// 원하는 FPS (예: 60)
	float _TargetElaspedTimeSec;	// 그래서 도달해야 하는 시간 (예: 16.7ms)



	/// 1. FPS제어?

	/// 2. 특정 구간의 걸린 시간을 재 보고 싶다.
};


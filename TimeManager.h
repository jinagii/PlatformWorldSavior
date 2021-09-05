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


	float _FPS;						// ���ϴ� FPS (��: 60)
	float _TargetElaspedTimeSec;	// �׷��� �����ؾ� �ϴ� �ð� (��: 16.7ms)



	/// 1. FPS����?

	/// 2. Ư�� ������ �ɸ� �ð��� �� ���� �ʹ�.
};


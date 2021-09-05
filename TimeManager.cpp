#include "pch.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	: _Frequency(0)
	, _ElaspedTime(0)
	, _FPS(0.0f)
	, _TargetElaspedTimeSec(0.0f)
{
	ZeroMemory(&_StartTimeStamp, sizeof(LARGE_INTEGER));
	ZeroMemory(&_EndTimeStamp, sizeof(LARGE_INTEGER));
}

TimeManager::~TimeManager()
{
}

HRESULT TimeManager::Init()
{
	// 빈도를 얻어온다.
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	_Frequency = Frequency.QuadPart;

	/// FPS와 그에 따른 1프레임에 걸리는 시간을 미리 계산(초)
	_FPS = 60.0f;
	_TargetElaspedTimeSec = 1.0f / _FPS;

	return S_OK;
}

void TimeManager::StartTimeStamp()
{
	QueryPerformanceCounter(&_StartTimeStamp);
}

void TimeManager::EndTimeStamp()
{
	QueryPerformanceCounter(&_EndTimeStamp);
}

void TimeManager::CheckTime()
{
	_ElaspedTime = _EndTimeStamp.QuadPart - _StartTimeStamp.QuadPart;
}

float TimeManager::GetElaspedTimeMS() const
{
	return static_cast<float>(_ElaspedTime) / static_cast<float>(_Frequency) * 1000.0f;
}

float TimeManager::GetElaspedTimeSec() const
{
	return static_cast<float>(_ElaspedTime) / static_cast<float>(_Frequency);
}

/// <summary>
/// 원하는 FPS에 해당하는 시간이 지났는가?
/// </summary>

bool TimeManager::FPSCheck()
{
	// 지금까지의 걸린 시간을 잰다.
	EndTimeStamp();
	CheckTime();

	if ((_TargetElaspedTimeSec * 1000.0f) < GetElaspedTimeMS())
	{
		// 다음 프레임으로 갈 수 있다.
		// 시간을 재기 시작한다.
		StartTimeStamp();
	
		return true;
	}

	return false;
}

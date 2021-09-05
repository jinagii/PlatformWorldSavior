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
	// �󵵸� ���´�.
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	_Frequency = Frequency.QuadPart;

	/// FPS�� �׿� ���� 1�����ӿ� �ɸ��� �ð��� �̸� ���(��)
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
/// ���ϴ� FPS�� �ش��ϴ� �ð��� �����°�?
/// </summary>

bool TimeManager::FPSCheck()
{
	// ���ݱ����� �ɸ� �ð��� ���.
	EndTimeStamp();
	CheckTime();

	if ((_TargetElaspedTimeSec * 1000.0f) < GetElaspedTimeMS())
	{
		// ���� ���������� �� �� �ִ�.
		// �ð��� ��� �����Ѵ�.
		StartTimeStamp();
	
		return true;
	}

	return false;
}

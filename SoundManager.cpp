#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

HRESULT SoundManager::Init(void)
{
	return S_OK;
}

void SoundManager::Release(void)
{
	DeleteAll();
}

void SoundManager::Update(void)
{
}

void SoundManager::Render(void)
{
}

Sound* SoundManager::AddSound(string strKey, const char* filePath)
{
	// 먼저 해당하는 사운드가 있는지 찾음
	Sound* snd = FindSound(strKey);

	// 사운드가 있으면 그냥 그 사운드 리턴
	if (snd) return snd;

	// 사운드가 없다면 새로 만듬
	snd = new Sound;

	// 사운드 초기화가 실패하면
	if (!snd->soundOpen(filePath))
	{
		// 다시 안전하게 제거하고
		SAFE_DELETE(snd);

		// 널 포인터 반환
		return nullptr;
	}

	// 정상적으로 만들어 졌다면 추가해준다.
	_mSoundList.insert(std::make_pair(strKey, snd));

	return snd;
}

Sound* SoundManager::FindSound(std::string strKey)
{
	MapSoundIter key = _mSoundList.find(strKey);

	// 찾았다면
	if (key != _mSoundList.end())
	{
		return key->second;
	}

	// 실패하면(없으면)
	return nullptr;
}

BOOL SoundManager::DeleteAll(void)
{
	MapSoundIter iter = _mSoundList.begin();

	for (; iter != _mSoundList.end();)
	{
		// 사운드 정보가 있다!
		if (iter->second != NULL)
		{
			// 사운드 메모리 해제
			SAFE_DELETE(iter->second);

			// 리스트에서 제거
			iter = _mSoundList.erase(iter);
		}

		// 다음으로
		else ++iter;
	}

	_mSoundList.clear();

	return true;
}

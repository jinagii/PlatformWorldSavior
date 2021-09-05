#pragma once

#include "SingletonBase.h"
#include "Sound.h"

class SoundManager : public SingletonBase<SoundManager>
{

private:
	typedef std::map<std::string, Sound*>				MapSoundList;
	typedef std::map<std::string, Sound*>::iterator		MapSoundIter;

private :
	MapSoundList _mSoundList;	// 사운드 리스트

public:
	SoundManager();
	~SoundManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	// 사운드 추가 함수
	Sound* AddSound(string strKey, const char* filePath);

	// 키 값으로 사운드 찾기
	Sound* FindSound(std::string strKey);

	// 모든 사운드 제거
	BOOL DeleteAll(void);

};

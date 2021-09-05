#pragma once

#include "SingletonBase.h"
#include "Sound.h"

class SoundManager : public SingletonBase<SoundManager>
{

private:
	typedef std::map<std::string, Sound*>				MapSoundList;
	typedef std::map<std::string, Sound*>::iterator		MapSoundIter;

private :
	MapSoundList _mSoundList;	// ���� ����Ʈ

public:
	SoundManager();
	~SoundManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	// ���� �߰� �Լ�
	Sound* AddSound(string strKey, const char* filePath);

	// Ű ������ ���� ã��
	Sound* FindSound(std::string strKey);

	// ��� ���� ����
	BOOL DeleteAll(void);

};

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
	// ���� �ش��ϴ� ���尡 �ִ��� ã��
	Sound* snd = FindSound(strKey);

	// ���尡 ������ �׳� �� ���� ����
	if (snd) return snd;

	// ���尡 ���ٸ� ���� ����
	snd = new Sound;

	// ���� �ʱ�ȭ�� �����ϸ�
	if (!snd->soundOpen(filePath))
	{
		// �ٽ� �����ϰ� �����ϰ�
		SAFE_DELETE(snd);

		// �� ������ ��ȯ
		return nullptr;
	}

	// ���������� ����� ���ٸ� �߰����ش�.
	_mSoundList.insert(std::make_pair(strKey, snd));

	return snd;
}

Sound* SoundManager::FindSound(std::string strKey)
{
	MapSoundIter key = _mSoundList.find(strKey);

	// ã�Ҵٸ�
	if (key != _mSoundList.end())
	{
		return key->second;
	}

	// �����ϸ�(������)
	return nullptr;
}

BOOL SoundManager::DeleteAll(void)
{
	MapSoundIter iter = _mSoundList.begin();

	for (; iter != _mSoundList.end();)
	{
		// ���� ������ �ִ�!
		if (iter->second != NULL)
		{
			// ���� �޸� ����
			SAFE_DELETE(iter->second);

			// ����Ʈ���� ����
			iter = _mSoundList.erase(iter);
		}

		// ��������
		else ++iter;
	}

	_mSoundList.clear();

	return true;
}

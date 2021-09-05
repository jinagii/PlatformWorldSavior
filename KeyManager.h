#pragma once

#include "SingletonBase.h"

#define KEYMAX		256

class KeyManager : public SingletonBase<KeyManager>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:
	KeyManager();
	~KeyManager();

	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);	// Ű ���� ��
	bool IsOnceKeyUp(int key);		// Ű �� ��
	bool IsStayKeyDown(int key);	// Ű�� ������ �ִ� ����

	bool GetKeyUp(int i) { return _keyUp[i]; }
	bool GetKeyYDown(int i) { return _keyDown[i]; }

	void SetKeyUp  (int key, bool state) { _keyUp[key] = state; }
	void SetKeyDown(int key, bool state) { _keyDown[key] = state; }
};
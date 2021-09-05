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

	bool IsOnceKeyDown(int key);	// 키 누를 떄
	bool IsOnceKeyUp(int key);		// 키 뗄 때
	bool IsStayKeyDown(int key);	// 키를 누르고 있는 동안

	bool GetKeyUp(int i) { return _keyUp[i]; }
	bool GetKeyYDown(int i) { return _keyDown[i]; }

	void SetKeyUp  (int key, bool state) { _keyUp[key] = state; }
	void SetKeyDown(int key, bool state) { _keyDown[key] = state; }
};
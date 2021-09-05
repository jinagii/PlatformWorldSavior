#pragma once

#include "GameNode.h"

class MainGame : public GameNode
{
private:
	/// ���� ���� �ʿ��� �� 
	GameNode* _introScene;
	GameNode* _worldchoiceScene;
	GameNode* _cutScene;
	GameNode* _stageScene;
	GameNode* _ingameScene;
	GameNode* _resultScene;
	GameNode* _loadingScene;

public:
	MainGame();
	~MainGame();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render();

	// ���ӿ��� �� �̹��� �ε�
	HRESULT LoadAllImage();

	// ���ӿ��� �� �� ���
	HRESULT RegisterAllScene();

	// ���ӿ��� �� ���� ���
	HRESULT LoadAllSound();
};
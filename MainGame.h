#pragma once

#include "GameNode.h"

class MainGame : public GameNode
{
private:
	/// 게임 내에 필요한 씬 
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

	// 게임에서 쓸 이미지 로드
	HRESULT LoadAllImage();

	// 게임에서 쓸 씬 등록
	HRESULT RegisterAllScene();

	// 게임에서 쓸 사운드 등록
	HRESULT LoadAllSound();
};
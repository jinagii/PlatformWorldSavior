#pragma once

#include "GameNode.h"

class Scene_Loding : public GameNode
{
public:
	Image* _lodingImg;


private:
	float _timer;
public:
	Scene_Loding();
	~Scene_Loding();

	HRESULT Init(void);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};
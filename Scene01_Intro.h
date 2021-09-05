#pragma once

#include "GameNode.h"

class Scene01_Intro : public GameNode
{
public:
	Image* _introImg;
	Image* _intro02Img;

public:
	Scene01_Intro();
	~Scene01_Intro();
	
	HRESULT Init(void);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};
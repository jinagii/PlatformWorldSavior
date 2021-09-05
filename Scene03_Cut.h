#pragma once

#include "GameNode.h"

class Scene03_Cut : public GameNode
{
public:
	Image* _cut01Img;
	Image* _cut02Img;
	Image* _cut03Img;

	Sound* _sndStory;

	int _cutNum = 0;

public:
	Scene03_Cut();
	~Scene03_Cut();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render();
};
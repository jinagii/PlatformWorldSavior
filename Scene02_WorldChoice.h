#pragma once

#include "GameNode.h"

class Scene02_WorldChoice : public GameNode
{
public:
	Image* _worldchoiceImg;
	Image* _worldnewsaviorImg;

	Sound* _sndWorld;

public:
	Scene02_WorldChoice();
	~Scene02_WorldChoice();

	RECT _rcWorld01 = { 260, 200, 510, 530 };
	RECT _rcWorld02 = { 720, 200, 1110, 490 };
	RECT _rcWorld03 = { 1110, 420, 1310, 720 };
	RECT _rcWorld04 = { 700, 700, 980, 1030 };

	RECT _worldnewsaviorbtclose = { 310, 955, 355, 1000 };
	bool _worldnewsaviorbt = false;

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render();
};
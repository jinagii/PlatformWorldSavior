#pragma once

#include "GameNode.h"

class Scene04_Stage : public GameNode
{
private:
	Sound* _sndStage;

	Image* _stagebackbgImg;
	Image* _stagebgImg;
	Image* _stageuititleImg;
	Image* _toworldImg;
	Image* _stagenewsaviorImg;

	Image* _stagebtoff01;
	Image* _stagebtoff02;
	Image* _stagebtoff03;
	Image* _stagebtoff04;
	Image* _stagebtoff05;
	Image* _stagebtoff06;
	Image* _stagebtoff07;
	Image* _stagebtoff08;

	Image* _stagebton01;
	Image* _stagebton02;
	Image* _stagebton03;
	Image* _stagebton04;
	Image* _stagebton05;
	Image* _stagebton06;
	Image* _stagebton07;
	Image* _stagebton08;

	RECT _rcStage01 = { 270, 400, 400, 530 };
	RECT _rcStage02 = { 515, 400, 645, 530 };
	RECT _rcStage03 = { 760, 400, 890, 530 };
	RECT _rcStage04 = { 1005, 400, 1135, 530 };
	RECT _rcStage05 = { 270, 600, 400, 730 };
	RECT _rcStage06 = { 515, 600, 645, 730 };
	RECT _rcStage07 = { 760, 600, 890, 730 };
	RECT _rcStage08 = { 1005, 600, 1135, 730 };

	RECT _toWorld = { 860, 795, 1250, 920 };

	RECT _stagenewsaviorbtclose = { 310, 955, 355, 1000 };
	bool _stagenewsaviorbt = false;

public:
	Scene04_Stage();
	~Scene04_Stage();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render();
};
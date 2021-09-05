#pragma once

#include "GameNode.h"

class Scene06_Result : public GameNode
{
private:
	/// 사운드
	Sound* _sndResult;

	/// 이미지
	Image* _resultBackbgImg;

	Image* _resultbgImg;
	Image* _resultuititleImg;
	Image* _resultchoiceImg;

	Image* _resultnewsaviorImg;

	Image* _resultbtreturnImg;
	Image* _resultbtnextImg;

	Image* _resultstaremptyImg;
	Image* _resultstarsImg;
	Image* _resultstaroImg;
	Image* _resultstarpImg;

	RECT _buttonreturn = { 190, 790, 310, 910 };
	RECT _stagechoice = { 510, 790, 910, 910 };
	RECT _buttonplay = { 1095, 790, 1215, 910 };

	RECT _resultnewsaviorbtclose = { 310, 955, 355, 1000 };
	bool _resultnewsaviorbt = false;

public:
	Scene06_Result();
	~Scene06_Result();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render();
};
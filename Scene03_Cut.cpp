#include "pch.h"
#include "Scene03_Cut.h"

Scene03_Cut::Scene03_Cut()
{
	_cut01Img = nullptr;
	_cut02Img = nullptr;
	_cut03Img = nullptr;
}

Scene03_Cut::~Scene03_Cut()
{

}

HRESULT Scene03_Cut::Init(void)
{
	/// 이미지 연결
	_cut01Img = IMAGEMANAGER->FindImage("STORY_01");
	_cut02Img = IMAGEMANAGER->FindImage("STORY_02");
	_cut03Img = IMAGEMANAGER->FindImage("STORY_03");

	// 사운드 연결
	_sndStory = SOUNDMANAGER->FindSound("BGM_STORY");
	_sndStory->soundSeek(0);
	_sndStory->soundPlay();

	return S_OK;
}

void Scene03_Cut::Release(void)
{

}

void Scene03_Cut::Update(void)
{
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		_cutNum++;

		if (_cutNum == 3)
		{
			SCENEMANAGER->ChangeScene("_stageScene");
			_cutNum = 0;

			_sndStory->soundPause();
		}

		
	}
}

void Scene03_Cut::Render()
{
	if (_cutNum == 0)
	{
		_cut01Img->Render(g_backBuffer->GetMemDC(), 0, 0);
	}
	else if (_cutNum == 1)
	{
		_cut02Img->FrameRender(g_backBuffer->GetMemDC(), 0, 0, false);
	}
	else if (_cutNum == 2)
	{
		_cut03Img->Render(g_backBuffer->GetMemDC(), 0, 0);
	}
}
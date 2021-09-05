#include "pch.h"
#include "Scene01_Intro.h"
#include "Scene_Loding.h"

Scene01_Intro::Scene01_Intro()
{
	_introImg = nullptr;
}

Scene01_Intro::~Scene01_Intro()
{

}

HRESULT Scene01_Intro::Init(void)
{
	/// 이미지 연결
	_introImg = IMAGEMANAGER->FindImage("INTRO");
	_intro02Img = IMAGEMANAGER->FindImage("INTRO_PIXEL");

	return S_OK;
}

void Scene01_Intro::Release()
{

}

void Scene01_Intro::Update()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
	{
		if (g_introversion == 1)
		{
			SCENEMANAGER->ChangeScene("_cutScene");
		}
		else
		{
			SCENEMANAGER->ChangeScene("_worldchoiceScene");
		}
	}
}

void Scene01_Intro::Render()
{
	if (g_introversion == 1)
	{
		_intro02Img->Render(g_backBuffer->GetMemDC(), 0, -35);
	}

	if (g_introversion == 0)
	{
		_introImg->Render(g_backBuffer->GetMemDC(), 0, -25);
	}
}
#include "pch.h"
#include "Scene_Loding.h"
#include "Scene05_Ingame.h"

int g_introversion = 0;

Scene_Loding::Scene_Loding()
{
	_lodingImg = nullptr;
}

Scene_Loding::~Scene_Loding()
{

}

HRESULT Scene_Loding::Init(void)
{
	/// 이미지 연결
	_lodingImg = IMAGEMANAGER->FindImage("LODING");

	// 타이머 설정
	_timer = 0.0f;

	return S_OK;
}

void Scene_Loding::Release()
{

}

void Scene_Loding::Update()
{
	if (_timer > 1.5f)
	{
		g_introversion = 1;
		SCENEMANAGER->ChangeScene("_introScene");
	}


	_timer += TIMEMANAGER->GetElaspedTimeSec();

}

void Scene_Loding::Render()
{
	_lodingImg->FrameRender(g_backBuffer->GetMemDC(), 0, -25);
}
#include "pch.h"

//
#include "Player.h"
//#include "ObjectBox.h"
#include "Map.h"
//
#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

HRESULT StartScene::Init()
{
	

	return S_OK;
}

void StartScene::Release()
{
	
}

void StartScene::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('1'))
	{
		SCENEMANAGER->ChangeScene("_testScene");
	}

	if (KEYMANAGER->IsOnceKeyDown('2'))
	{
		SCENEMANAGER->ChangeScene("_introScene");
	}

	if (KEYMANAGER->IsOnceKeyDown('3'))
	{
		SCENEMANAGER->ChangeScene("_yhScene");
	}
}

void StartScene::Render()
{
	
}


#include "pch.h"
#include "Scene04_Stage.h"
#include "Scene05_Ingame.h"

//#include "YhScene.h"

Scene04_Stage::Scene04_Stage()
{
	_stagebackbgImg = nullptr;
	_stagebgImg = nullptr;
	_stageuititleImg = nullptr;
	_toworldImg = nullptr;
	_stagenewsaviorImg = nullptr;

	_stagebtoff01 = nullptr;
	_stagebtoff02 = nullptr;
	_stagebtoff03 = nullptr;
	_stagebtoff04 = nullptr;
	_stagebtoff05 = nullptr;
	_stagebtoff06 = nullptr;
	_stagebtoff07 = nullptr;
	_stagebtoff08 = nullptr;

	_stagebton01 = nullptr;
	_stagebton02 = nullptr;
	_stagebton03 = nullptr;
	_stagebton04 = nullptr;
	_stagebton05 = nullptr;
	_stagebton06 = nullptr;
	_stagebton07 = nullptr;
	_stagebton08 = nullptr;
}

Scene04_Stage::~Scene04_Stage()
{

}

HRESULT Scene04_Stage::Init(void)
{
	/// 이미지 연결
	_stagebackbgImg = IMAGEMANAGER->FindImage("INTRO_BLUR");
	_stagebgImg = IMAGEMANAGER->FindImage("UI_BG_03");
	_stageuititleImg = IMAGEMANAGER->FindImage("UI_STAGE_TITLE");
	_toworldImg = IMAGEMANAGER->FindImage("UI_WORLD_MAP");
	_stagenewsaviorImg = IMAGEMANAGER->FindImage("UI_NEW_SAVIOR");

	_stagebtoff01 = IMAGEMANAGER->FindImage("UI_STEMP_OFF_01");
	_stagebtoff02 = IMAGEMANAGER->FindImage("UI_STEMP_OFF_02");
	_stagebtoff03 = IMAGEMANAGER->FindImage("UI_STEMP_OFF_03");
	_stagebtoff04 = IMAGEMANAGER->FindImage("UI_STEMP_OFF_04");
	_stagebtoff05 = IMAGEMANAGER->FindImage("UI_STEMP_OFF_05");
	_stagebtoff06 = IMAGEMANAGER->FindImage("UI_STEMP_OFF_06");
	_stagebtoff07 = IMAGEMANAGER->FindImage("UI_STEMP_OFF_07");
	_stagebtoff08 = IMAGEMANAGER->FindImage("UI_STEMP_OFF_08");

	_stagebton01 = IMAGEMANAGER->FindImage("UI_STEMP_ON_01");
	_stagebton02 = IMAGEMANAGER->FindImage("UI_STEMP_ON_02");
	_stagebton03 = IMAGEMANAGER->FindImage("UI_STEMP_ON_03");
	_stagebton04 = IMAGEMANAGER->FindImage("UI_STEMP_ON_04");
	_stagebton05 = IMAGEMANAGER->FindImage("UI_STEMP_ON_05");
	_stagebton06 = IMAGEMANAGER->FindImage("UI_STEMP_ON_06");
	_stagebton07 = IMAGEMANAGER->FindImage("UI_STEMP_ON_07");
	_stagebton08 = IMAGEMANAGER->FindImage("UI_STEMP_ON_08");

	_sndStage = SOUNDMANAGER->FindSound("BGM_STAGE");
	_sndStage->soundSeek(0);
	_sndStage->soundPlay();

	return S_OK;
}

void Scene04_Stage::Release(void)
{

}

void Scene04_Stage::Update(void)
{
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcStage01, g_ptMouse))
		{
			g_stageNum = 1;
			SCENEMANAGER->ChangeScene("_ingameScene");
			_stagenewsaviorbt = false;
			cout << "씬 체인지 - _ingameScene " << g_stageNum << "\n\n";

			_sndStage->soundPause();
		}

		else if (PtInRect(&_rcStage02, g_ptMouse))
		{
			g_stageNum = 2;
			SCENEMANAGER->ChangeScene("_ingameScene");
			_stagenewsaviorbt = false;
			g_editModeCameraReset = true;

			_sndStage->soundPause();
		}

		else if (PtInRect(&_rcStage03, g_ptMouse))
		{
			g_stageNum = 3;
			SCENEMANAGER->ChangeScene("_ingameScene");
			_stagenewsaviorbt = false;

			_sndStage->soundPause();
		}

		else if (PtInRect(&_toWorld, g_ptMouse))
		{
			SCENEMANAGER->ChangeScene("_worldchoiceScene");
			_stagenewsaviorbt = false;

			_sndStage->soundPause();
		}

		else if (PtInRect(&_rcStage04, g_ptMouse) || PtInRect(&_rcStage05, g_ptMouse) ||
			PtInRect(&_rcStage06, g_ptMouse) || PtInRect(&_rcStage07, g_ptMouse) || PtInRect(&_rcStage08, g_ptMouse))
		{
			_stagenewsaviorbt = true;
		}

		else if (PtInRect(&_stagenewsaviorbtclose, g_ptMouse))
		{
			// 행성 잠김 문구 출력
			_stagenewsaviorbt = false;
		}

	}
}

void Scene04_Stage::Render()
{
	// 월드맵 버튼 클릭용 렉트 드로우
	DrawRect(g_backBuffer->GetMemDC(), _toWorld.left, _toWorld.top, _toWorld.right, _toWorld.bottom);

	// 비활성화 스테이지 눌렀을때 뜨는 이미지 닫기버튼
	DrawRect(g_backBuffer->GetMemDC(), _stagenewsaviorbtclose.left, _stagenewsaviorbtclose.top, _stagenewsaviorbtclose.right, _stagenewsaviorbtclose.bottom);

	_stagebackbgImg->Render(g_backBuffer->GetMemDC(), 0, 0);
	_stagebgImg->Render(g_backBuffer->GetMemDC(), 72, 100);
	_stageuititleImg->Render(g_backBuffer->GetMemDC(), 285, 160);
	_toworldImg->Render(g_backBuffer->GetMemDC(), 850, 786);

	if (_stagenewsaviorbt == true)
	{
		_stagenewsaviorImg->Render(g_backBuffer->GetMemDC(), 283, 950);
	}

	// 비 활성화 버튼
	//  _stagebtoff01->Render(g_backBuffer->GetMemDC(), 265, 365);
	// 	_stagebtoff02->Render(g_backBuffer->GetMemDC(), 510, 365);
	//	_stagebtoff03->Render(g_backBuffer->GetMemDC(), 755, 365);
	_stagebtoff04->Render(g_backBuffer->GetMemDC(), 1000, 365);
	_stagebtoff05->Render(g_backBuffer->GetMemDC(), 265, 565);
	_stagebtoff06->Render(g_backBuffer->GetMemDC(), 510, 565);
	_stagebtoff07->Render(g_backBuffer->GetMemDC(), 755, 565);
	_stagebtoff08->Render(g_backBuffer->GetMemDC(), 1000, 565);

	// 활성화 버튼
	_stagebton01->Render(g_backBuffer->GetMemDC(), 265, 365);
	_stagebton02->Render(g_backBuffer->GetMemDC(), 510, 365);
	_stagebton03->Render(g_backBuffer->GetMemDC(), 755, 365);
	//	_stagebton04->Render(g_backBuffer->GetMemDC(), 1000, 365);
	//	_stagebton05->Render(g_backBuffer->GetMemDC(), 265, 565);
	//	_stagebton06->Render(g_backBuffer->GetMemDC(), 510, 565);
	//	_stagebton07->Render(g_backBuffer->GetMemDC(), 755, 565);
	//	_stagebton08->Render(g_backBuffer->GetMemDC(), 1000, 565);
}
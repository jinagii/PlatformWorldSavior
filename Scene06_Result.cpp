#include "pch.h"
#include "Scene06_Result.h"

int g_clearLevel = 0;

Scene06_Result::Scene06_Result()
{
	_resultBackbgImg = nullptr;
	_resultbgImg = nullptr;
	_resultuititleImg = nullptr;
	_resultchoiceImg = nullptr;

	_resultnewsaviorImg = nullptr;

	_resultbtreturnImg = nullptr;
	_resultbtnextImg = nullptr;

	_resultstaremptyImg = nullptr;
	_resultstarsImg = nullptr;
	_resultstaroImg = nullptr;
	_resultstarpImg = nullptr;
}

Scene06_Result::~Scene06_Result()
{

}

HRESULT Scene06_Result::Init(void)
{
	/// 이미지 연결
	_resultBackbgImg = IMAGEMANAGER->FindImage("INTRO_BLUR");

	_resultbgImg = IMAGEMANAGER->FindImage("UI_BG_03");
	_resultuititleImg = IMAGEMANAGER->FindImage("UI_CLEAR_STAGE");
	_resultchoiceImg = IMAGEMANAGER->FindImage("UI_SELECT_STAGE");

	_resultnewsaviorImg = IMAGEMANAGER->FindImage("UI_NEW_SAVIOR");
	
	_resultbtreturnImg = IMAGEMANAGER->FindImage("UI_BUTTON_RESTART");
	_resultbtnextImg = IMAGEMANAGER->FindImage("UI_BUTTON_NEXTSTAGE");
	
	_resultstaremptyImg = IMAGEMANAGER->FindImage("UI_STAR_EMPTY");
	_resultstarsImg = IMAGEMANAGER->FindImage("UI_STAR_S");
	_resultstaroImg = IMAGEMANAGER->FindImage("UI_STAR_O");
	_resultstarpImg = IMAGEMANAGER->FindImage("UI_STAR_P");

	_sndResult = SOUNDMANAGER->FindSound("BGM_CLEAR");
	_sndResult->soundSeek(0);
	_sndResult->soundPlay();

	return S_OK;
}

void Scene06_Result::Release(void)
{

}

void Scene06_Result::Update(void)
{
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_stagechoice, g_ptMouse))
		{
			// 스테이지 선택 씬으로 전환
			SCENEMANAGER->ChangeScene("_stageScene");
			cout << "스테이지 선택 씬으로~ \n\n";

			// 클리어 레벨 초기화
			g_clearLevel = 0;

			_sndResult->soundPause();
		}

		else if (PtInRect(&_buttonreturn, g_ptMouse))
		{
			// 인게임 씬으로 전환
			cout << "인게임 씬 " << g_stageNum << "으로~" << "\n\n";

			// 1번 스테이지 플레이 했다면 다시 1번 스테이지로
			if (g_stageNum == 1)
			{
				SCENEMANAGER->ChangeScene("_ingameScene");

				// 클리어 레벨 초기화
				g_clearLevel = 0;

				_sndResult->soundPause();
			}
			// 2번 스테이지 플레이 했다면 다시 2번 스테이지로
			else if (g_stageNum == 2)
			{
				SCENEMANAGER->ChangeScene("_ingameScene");

				// 클리어 레벨 초기화
				g_clearLevel = 0;

				_sndResult->soundPause();
			}
			// 3번 스테이지 플레이 했다면 다시 3번 스테이지로
			else if (g_stageNum == 3)
			{
				SCENEMANAGER->ChangeScene("_ingameScene");

				// 클리어 레벨 초기화
				g_clearLevel = 0;

				_sndResult->soundPause();
			}
		}

		else if (PtInRect(&_buttonplay, g_ptMouse))
		{
			// 1번 스테이지 플레이 했다면 2번 스테이지로
			if (g_stageNum == 1)
			{
				g_stageNum = 2;
				SCENEMANAGER->ChangeScene("_ingameScene");

				// 클리어 레벨 초기화
				g_clearLevel = 0;

				_sndResult->soundPause();
			}
			// 2번 스테이지 플레이 했다면 3번 스테이지로
			else if (g_stageNum == 2)
			{
				g_stageNum = 3;
				SCENEMANAGER->ChangeScene("_ingameScene");

				// 클리어 레벨 초기화
				g_clearLevel = 0;

				_sndResult->soundPause();
			}
			// 3번 스테이지 플레이 했다면
			else if (g_stageNum == 3)
			{
				// 비활성화 넘어갈 다음 스테이지가 없음
				_resultnewsaviorbt = true;
			}
		}

		else if (PtInRect(&_resultnewsaviorbtclose, g_ptMouse))
		{
			// 행성 잠김 문구 출력
			_resultnewsaviorbt = false;
		}
	}
}

void Scene06_Result::Render()
{
	_resultBackbgImg->Render(g_backBuffer->GetMemDC(), 0, 0);
	_resultbgImg->Render(g_backBuffer->GetMemDC(), 72, 100);

	// 버튼 스테이지 다시하기, 다음 버튼 클릭용 렉트 드로우 
	//DrawRect(g_backBuffer->GetMemDC(), _buttonreturn.left, _buttonreturn.top, _buttonreturn.right, _buttonreturn.bottom);
	//DrawRect(g_backBuffer->GetMemDC(), _buttonplay.left, _buttonplay.top, _buttonplay.right, _buttonplay.bottom);
	//DrawRect(g_backBuffer->GetMemDC(), _resultnewsaviorbtclose.left, _resultnewsaviorbtclose.top, _resultnewsaviorbtclose.right, _resultnewsaviorbtclose.bottom);

	// 스테이지 선택 클릭용 렉트 드로우
	//DrawRect(g_backBuffer->GetMemDC(), _stagechoice.left, _stagechoice.top, _stagechoice.right, _stagechoice.bottom);
	
	/// 클리어레벨에 따라서 별 출력
	// 클리어레벨 1 이상일 때(항상) 별(S) 출력
	_resultstarsImg->Render(g_backBuffer->GetMemDC(), 293, 370);
	
	// 클리어레벨 2이상일 때 별(P)출력
	if(g_clearLevel >= 2) _resultstarpImg->Render(g_backBuffer->GetMemDC(), 865, 376);
	
	// 클리어레벨 3이상일 때 별(O) 출력
	if(g_clearLevel >= 3) _resultstaroImg->Render(g_backBuffer->GetMemDC(), 580, 360);
	
	_resultuititleImg->Render(g_backBuffer->GetMemDC(), 288, 160);
	_resultchoiceImg->Render(g_backBuffer->GetMemDC(), 505, 780);

	_resultbtreturnImg->Render(g_backBuffer->GetMemDC(), 180, 780);
	_resultbtnextImg->Render(g_backBuffer->GetMemDC(), 1085, 780);

	if (_resultnewsaviorbt == true)
	{
		_resultnewsaviorImg->Render(g_backBuffer->GetMemDC(), 283, 950);
	}
}
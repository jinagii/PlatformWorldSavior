#include "pch.h"
#include "Scene02_WorldChoice.h"
#include "Scene01_Intro.h"

Scene02_WorldChoice::Scene02_WorldChoice()
{
	_worldchoiceImg = nullptr;
	_worldnewsaviorImg = nullptr;
}

Scene02_WorldChoice::~Scene02_WorldChoice()
{

}

HRESULT Scene02_WorldChoice::Init(void)
{
	/// 이미지 연결
	_worldchoiceImg = IMAGEMANAGER->FindImage("WORLD_CHOICE");
	_worldnewsaviorImg = IMAGEMANAGER->FindImage("UI_NEW_SAVIOR");

	/// 사운드 연결
	_sndWorld = SOUNDMANAGER->FindSound("BGM_WORLD");
	_sndWorld->soundSeek(0);
	_sndWorld->soundPlay();


	return S_OK;
}

void Scene02_WorldChoice::Release(void)
{

}

void Scene02_WorldChoice::Update(void)
{
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		

		if (PtInRect(&_rcWorld01, g_ptMouse))
		{
			if (g_introversion == 1)
			{
				SCENEMANAGER->ChangeScene("_cutScene");
				_worldnewsaviorbt = false;

				_sndWorld->soundPause();
			}

			else if (g_introversion != 1)
			{
				SCENEMANAGER->ChangeScene("_lodingScene");
				_worldnewsaviorbt = false;

				_sndWorld->soundPause();
			}
		}

		else if (PtInRect(&_rcWorld02, g_ptMouse) || PtInRect(&_rcWorld03, g_ptMouse) || PtInRect(&_rcWorld04, g_ptMouse))
		{
			// 행성 잠김 문구 출력
			_worldnewsaviorbt = true;
		}

		else if (PtInRect(&_worldnewsaviorbtclose, g_ptMouse))
		{
			// 행성 잠김 문구 출력
			_worldnewsaviorbt = false;
		}
	}
}

void Scene02_WorldChoice::Render()
{
	// 월드 선택 클릭용 렉트 드로우
	DrawEllipse(g_backBuffer->GetMemDC(), _rcWorld01.left, _rcWorld01.top, _rcWorld01.right, _rcWorld01.bottom);
	DrawEllipse(g_backBuffer->GetMemDC(), _rcWorld02.left, _rcWorld02.top, _rcWorld02.right, _rcWorld02.bottom);
	DrawEllipse(g_backBuffer->GetMemDC(), _rcWorld03.left, _rcWorld03.top, _rcWorld03.right, _rcWorld03.bottom);
	DrawEllipse(g_backBuffer->GetMemDC(), _rcWorld04.left, _rcWorld04.top, _rcWorld04.right, _rcWorld04.bottom);

	DrawRect(g_backBuffer->GetMemDC(), _worldnewsaviorbtclose.left, _worldnewsaviorbtclose.top, _worldnewsaviorbtclose.right, _worldnewsaviorbtclose.bottom);

	_worldchoiceImg->Render(g_backBuffer->GetMemDC(), 0, 0);

	if (_worldnewsaviorbt == true)
	{
		_worldnewsaviorImg->Render(g_backBuffer->GetMemDC(), 283, 950);
	}
}
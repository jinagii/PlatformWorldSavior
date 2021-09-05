#include "pch.h"
#include "Map.h"
#include "GameNode.h"

GameNode::GameNode()
{
}

GameNode::~GameNode()
{

}

HRESULT GameNode::Init()
{
	// 전역으로 설정해둔 윈도우 핸들로 씬들이 사용할 DC를 만든다
	_hdc = GetDC(g_hWnd);

	_managerInit = false;

	// 매니저 초기화
	TIMEMANAGER->Init();
	IMAGEMANAGER->Init();
	SCENEMANAGER->Init();
	KEYMANAGER->Init();
	SOUNDMANAGER->Init();

	return S_OK;
}

HRESULT GameNode::Init(bool managerInit)
{

	_hdc = GetDC(g_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		IMAGEMANAGER->Init();
		TIMEMANAGER->Init();
		SCENEMANAGER->Init();
		KEYMANAGER->Init();
		SOUNDMANAGER->Init();
	}

	return S_OK;
}



//메모리 해제(내용 번부 변경)
void GameNode::Release()
{
	if (_managerInit)
	{

		IMAGEMANAGER->Release();
		IMAGEMANAGER->ReleaseSingleton();

		TIMEMANAGER->ReleaseSingleton();

		SCENEMANAGER->Release();
		SCENEMANAGER->ReleaseSingleton();

		KEYMANAGER->Release();
		KEYMANAGER->ReleaseSingleton();

		SOUNDMANAGER->Release();
		SOUNDMANAGER->ReleaseSingleton();

	}

	ReleaseDC(g_hWnd, _hdc);
}

void GameNode::Update()
{

}

void GameNode::Render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
		case WM_CREATE:
		{

			break;
		}


		case WM_MOUSEMOVE:
		{
			g_ptMouse.x = static_cast<float>LOWORD(lParam);
			g_ptMouse.y = static_cast<float>HIWORD(lParam);

			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

	}// end of switch

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

/// 타입(1 == 이미지, 2 == 사운드)과 경로를 받아서 완성된 경로를 반환한다.
/// 0은 디폴트(_Resources의 경로로 자동으로 설정한다)
const char* GameNode::ConvertPath(string path, int type)
{
	/// 디폴트 경로 설정
	/// DEFAULT_PATH  : "_Resources/" 폴더
	/// IMAGE_PATH : "_Resources/_Images/" 
	/// SOUND_PATH : "_Resources/_Sounds/" 

	_path.clear();

	switch (type)
	{
	case 0:
		_path = RESOURCES_PATH + path;
		break;

	case 1:
		_path = IMAGE_PATH + path;
		break;

	case 2:
		_path = SOUND_PATH + path;
		break;

	}	

	return _path.c_str();
	
}


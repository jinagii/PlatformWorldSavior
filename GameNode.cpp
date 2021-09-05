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
	// �������� �����ص� ������ �ڵ�� ������ ����� DC�� �����
	_hdc = GetDC(g_hWnd);

	_managerInit = false;

	// �Ŵ��� �ʱ�ȭ
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



//�޸� ����(���� ���� ����)
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

/// Ÿ��(1 == �̹���, 2 == ����)�� ��θ� �޾Ƽ� �ϼ��� ��θ� ��ȯ�Ѵ�.
/// 0�� ����Ʈ(_Resources�� ��η� �ڵ����� �����Ѵ�)
const char* GameNode::ConvertPath(string path, int type)
{
	/// ����Ʈ ��� ����
	/// DEFAULT_PATH  : "_Resources/" ����
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


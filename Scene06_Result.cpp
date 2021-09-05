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
	/// �̹��� ����
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
			// �������� ���� ������ ��ȯ
			SCENEMANAGER->ChangeScene("_stageScene");
			cout << "�������� ���� ������~ \n\n";

			// Ŭ���� ���� �ʱ�ȭ
			g_clearLevel = 0;

			_sndResult->soundPause();
		}

		else if (PtInRect(&_buttonreturn, g_ptMouse))
		{
			// �ΰ��� ������ ��ȯ
			cout << "�ΰ��� �� " << g_stageNum << "����~" << "\n\n";

			// 1�� �������� �÷��� �ߴٸ� �ٽ� 1�� ����������
			if (g_stageNum == 1)
			{
				SCENEMANAGER->ChangeScene("_ingameScene");

				// Ŭ���� ���� �ʱ�ȭ
				g_clearLevel = 0;

				_sndResult->soundPause();
			}
			// 2�� �������� �÷��� �ߴٸ� �ٽ� 2�� ����������
			else if (g_stageNum == 2)
			{
				SCENEMANAGER->ChangeScene("_ingameScene");

				// Ŭ���� ���� �ʱ�ȭ
				g_clearLevel = 0;

				_sndResult->soundPause();
			}
			// 3�� �������� �÷��� �ߴٸ� �ٽ� 3�� ����������
			else if (g_stageNum == 3)
			{
				SCENEMANAGER->ChangeScene("_ingameScene");

				// Ŭ���� ���� �ʱ�ȭ
				g_clearLevel = 0;

				_sndResult->soundPause();
			}
		}

		else if (PtInRect(&_buttonplay, g_ptMouse))
		{
			// 1�� �������� �÷��� �ߴٸ� 2�� ����������
			if (g_stageNum == 1)
			{
				g_stageNum = 2;
				SCENEMANAGER->ChangeScene("_ingameScene");

				// Ŭ���� ���� �ʱ�ȭ
				g_clearLevel = 0;

				_sndResult->soundPause();
			}
			// 2�� �������� �÷��� �ߴٸ� 3�� ����������
			else if (g_stageNum == 2)
			{
				g_stageNum = 3;
				SCENEMANAGER->ChangeScene("_ingameScene");

				// Ŭ���� ���� �ʱ�ȭ
				g_clearLevel = 0;

				_sndResult->soundPause();
			}
			// 3�� �������� �÷��� �ߴٸ�
			else if (g_stageNum == 3)
			{
				// ��Ȱ��ȭ �Ѿ ���� ���������� ����
				_resultnewsaviorbt = true;
			}
		}

		else if (PtInRect(&_resultnewsaviorbtclose, g_ptMouse))
		{
			// �༺ ��� ���� ���
			_resultnewsaviorbt = false;
		}
	}
}

void Scene06_Result::Render()
{
	_resultBackbgImg->Render(g_backBuffer->GetMemDC(), 0, 0);
	_resultbgImg->Render(g_backBuffer->GetMemDC(), 72, 100);

	// ��ư �������� �ٽ��ϱ�, ���� ��ư Ŭ���� ��Ʈ ��ο� 
	//DrawRect(g_backBuffer->GetMemDC(), _buttonreturn.left, _buttonreturn.top, _buttonreturn.right, _buttonreturn.bottom);
	//DrawRect(g_backBuffer->GetMemDC(), _buttonplay.left, _buttonplay.top, _buttonplay.right, _buttonplay.bottom);
	//DrawRect(g_backBuffer->GetMemDC(), _resultnewsaviorbtclose.left, _resultnewsaviorbtclose.top, _resultnewsaviorbtclose.right, _resultnewsaviorbtclose.bottom);

	// �������� ���� Ŭ���� ��Ʈ ��ο�
	//DrawRect(g_backBuffer->GetMemDC(), _stagechoice.left, _stagechoice.top, _stagechoice.right, _stagechoice.bottom);
	
	/// Ŭ������� ���� �� ���
	// Ŭ����� 1 �̻��� ��(�׻�) ��(S) ���
	_resultstarsImg->Render(g_backBuffer->GetMemDC(), 293, 370);
	
	// Ŭ����� 2�̻��� �� ��(P)���
	if(g_clearLevel >= 2) _resultstarpImg->Render(g_backBuffer->GetMemDC(), 865, 376);
	
	// Ŭ����� 3�̻��� �� ��(O) ���
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
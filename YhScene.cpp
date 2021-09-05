#include "pch.h"
#include "YHScene.h"

//
#include "Player.h"
#include "Map.h"
//
//int g_YH_stageNum = 0;

YHScene::YHScene()
{
	
}

YHScene::~YHScene()
{
	
}

HRESULT YHScene::Init(void)
{
	switch (g_stageNum)
	{
	case 1:
		cout << "�������� 01 Init\n\n";
		Init_Stage01();
		break;

	case 2:
		cout << "�������� 02 Init\n\n";
		Init_Stage01();
		break;
	}

	return S_OK;
}

void YHScene::Init_Stage01()
{
	// �� ���� ����
	m_pMap = new Map();
	m_pMap->Initialize();
	InputBoardData();

	/// �̹��� ����
	// ��׶��� �̹���
	_bgImg = IMAGEMANAGER->FindImage("BG_MOUNTAIN");
	_grass01Img = IMAGEMANAGER->FindImage("GRASS_01");

	//���� Ű
	_key = IMAGEMANAGER->FindImage("KEY");
	_doorClose = IMAGEMANAGER->FindImage("DOOR_CLOSE");
	_doorOpen = IMAGEMANAGER->FindImage("DOOR_OPEN");

	// ĳ������ ���� Ÿ�� ���ϱ�
	//POINT pos = CalcCharSetPos(15, MAPSIZE_Y - 9);
	POINT pos = CalcCharSetPos(10, 4);

	// �÷��̾� ����
	_player = new Player;
	_player->Initialize(70, pos.x, pos.y);
	_player->_img = IMAGEMANAGER->FindImage("PLAYER");
	printf_s("ĳ���� ��ġ[%f,%f] \n\n", _player->m_PosX, _player->m_PosY);

	/// ���� �߿�

	// ī�޶� ��ġ ����
	MoveCamera();

	// �ΰ��� ���콺 ��ǥ ����
	MappingMousePoint();

	// ��ġ Ÿ�� ��ư
	_btnDeployTile_01 = IMAGEMANAGER->FindImage("BLOCK");
	IMAGEMANAGER->AddImage("longblock", ConvertPath("longblock.bmp", 1), 350, 70, true, RGB(255, 0, 255));
	_btnDeployTile_02 = IMAGEMANAGER->FindImage("longblock");

	MappingUI();

	_gameState = Game_State::Edit;
}

void YHScene::Release(void)
{
	SAFE_DELETE(_player);

	//for (int j = 0; j < MAPSIZE_Y; j++)
	//{
	//	for (int i = 0; i < MAPSIZE_X; i++)
	//		SAFE_DELETE(_floor[j][i]);
	//}
}

void YHScene::Update(void)
{
	/// ���� ��ũ��(DC)�� �������Ե� ���� ����(ī�޶� �̵�)
	MoveCamera();

	/// ���� ��ġ�� ������(â) ���̿� ����� ��ǥ ���� ����
	MappingMousePoint();
	MappingUI();

	////////////////
	/// �ΰ��� �� ĳ���� �Ӽ� ����
	if (KEYMANAGER->IsOnceKeyDown(VK_UP))
	{
		_player->MaxJumpPower -= 1;
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
	{
		_player->MaxJumpPower += 1.0;
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
	{
		_player->m_Speed -= 1;
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
	{
		_player->m_Speed += 1.0;
	}

	if (KEYMANAGER->IsOnceKeyDown('W'))
	{
		_player->SpringJumpPower -= 2.0f;
	}
	if (KEYMANAGER->IsOnceKeyDown('S'))
	{
		_player->SpringJumpPower += 2.0f;
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_CONTROL))
	{
		_player->ChangeDirection();
	}

	////////////////

	switch (_gameState)
	{

		/// �÷��� ���
	case Game_State::Play:
	{
		if (IsChangeMode())
		{
			// ��尡 �ٲ������ �����ϰ� �ٽ� �������� ������
			return;
		}

		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			DebugShowMouseClickState();
			CheckCurrentBoard(_ptMouse.x, _ptMouse.y);
		}

		_player->GetMapInfo(m_pMap);

		_player->PlayerAutoMove();
		
		_player->PlayerGravity();
		
		_player->PlayerCheckEmptyFloor(m_pMap);
		
		_player->PlayerCheckFloor(m_pMap);
		
		_player->PlayerCheckUpTile(m_pMap);
		
		_player->PlayerCheckDoor(m_pMap);
		
		_player->PlayerCheckWall(m_pMap);
		
		_player->PlayerCheckKey(m_pMap);
		
		_player->PlayerCheckSpring(m_pMap);
		
		_player->PlayerCheckRoof(m_pMap);
		
		CheckPlayerPos(_player->m_PosX, _player->m_PosY);
	}
	break;

	case Game_State::Edit:
	{
		if (IsChangeMode())
		{
			// ��尡 �ٲ������ �����ϰ� �ٽ� �������� ������
			return;
		}

		// ���콺 �� Ŭ���� ������
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			cout << "���콺 ��Ŭ�� \n\n";
			SelectDeployButton();
		}

		//DebugShowMouseClickState();

		break;
	}

	case Game_State::Stop:
	{

		break;
	}

	}// end of switch
}

void YHScene::Render()
{
	// ����� ���� �׸���.
	_bgImg->Render(g_backBuffer->GetMemDC(), 0, 0);

	// Ÿ��(���)�� �׸���.
	RenderTile();

	// �÷��̾ �׸���.(������ �ִϸ��̼�)
	_player->_img->FrameRender(g_backBuffer->GetMemDC(), _player->m_PosX, _player->m_PosY);

	_player->DebugShowPlayerPosArray();

	DebugShowMouseInfo();


	// ��ġ��� UI ����
	if (_gameState == Game_State::Edit)
	{
		RenderUI();
		//. ���� ���� �׸���
		m_pMap->DrawGrid();

	}

	if (_isSelectMode)
	{
		switch (PickedMouseBlockType)
		{
			// 1ĭ ����� ���� ���� ��
		case Block::BLOCK_ROCK:
		{
			_btnDeployTile_01->Render(g_backBuffer->GetMemDC(), _ptMouse.x - TILESIZE / 2, _ptMouse.y - TILESIZE / 2);
			break;
		}

		// 5ĭ ����� ���� ���� ��
		case Block::BLOCK_LONG_ROCK:
		{
			_btnDeployTile_02->Render(g_backBuffer->GetMemDC(), _ptMouse.x - TILESIZE / 2, _ptMouse.y - TILESIZE / 2);
			break;
		}

		}// end of switch
	}

	// ī�޶� ����
	g_backBuffer->Render(g_backBuffer->GetMemDC(), 0, 0, _cameraX, _cameraY, BACKDCSIZEX, BACKDCSIZEY);
	//g_backBuffer->Render(g_backBuffer->GetMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);

}

void YHScene::InputBoardData()
{
	for (int j = 0; j < YH_MAPSIZE_Y; j++)
	{
		for (int i = 0; i < YH_MAPSIZE_X; i++)
		{
			m_pMap->SetType(i, j, (Block)m_StageOneData[j][i]);
		}
	}
}

void YHScene::MoveCamera()
{
	// ī�޶� ��ǥ ����
	_cameraX = _player->m_PosX - (WINSIZEX / 2);
	_cameraY = _player->m_PosY - (WINSIZEY / 2);

	// ********* ī�޶� ���� ����� �ʵ��� ��ġ ���� **********************

	// ĳ���Ͱ� ���� ���� ������� ī�޶� �������� �̵��ϸ� �ȵ� ��
	if (_player->m_PosX - WINSIZEX / 2 <= 0) _cameraX = 0;

	// ĳ���Ͱ� ���� ���� ������� ī�޶� �������� �̵��ϸ� �ȵ� ��
	if (_player->m_PosY - WINSIZEY / 2 <= 0) _cameraY = 0;

	// ĳ���Ͱ� ������ ���� ������� ī�޶� ���������� �̵��ϸ� �ȵ� ��
	if (_player->m_PosX + WINSIZEX / 2 > _bgImg->GetWidth()) _cameraX = _bgImg->GetWidth() - WINSIZEX;

	// ĳ���Ͱ� �Ʒ��� ���� ������� ī�޶� �Ʒ������� �̵��ϸ� �ȵ� ��
	if (_player->m_PosY + WINSIZEY / 2 > _bgImg->GetWidth()) _cameraY = _bgImg->GetHeight() - WINSIZEY;

}

void YHScene::MappingMousePoint()
{
	_ptMouse.x = g_ptMouse.x + _cameraX;
	_ptMouse.y = g_ptMouse.y + _cameraY;
}

void YHScene::MappingUI()
{
	_btnDeployTile_01->SetX(_cameraX + 70);
	_btnDeployTile_01->SetY(_cameraY + 980);

	_btnDeployTile_02->SetX(_cameraX + 300);
	_btnDeployTile_02->SetY(_cameraY + 980);

}

// �迭���� 0������ size-1 �� ��ǥ�� �Է��Ͻÿ�.
// 0 ~ MAPSIZE - 1
POINT YHScene::CalcCharSetPos(int x, int y)
{
	POINT pos;
	pos.x = x * TILESIZE;
	pos.y = (y * TILESIZE) - TILESIZE;	// ĳ���Ͱ� Ÿ�� ������ ���� 1*2 �������(70px,140px) y�� 70��ŭ ���� ������ ��

	return pos;
}

bool YHScene::CheckPlayerPos(float x, float y)
{
	int PlayerPosX = _player->m_PosX + TILESIZE / 2;				// �߽� ��ǥ
	int PlayerPosY = _player->m_PosY + TILESIZE + TILESIZE / 2;

	// �� ���ʿ� ����� �� ���� ��ȯ
	if (PlayerPosX < (0 + TILESIZE / 2))
	{
		_player->ChangeDirection();
	}

	// �� ���� �հ� �ö� �� ���� �����Ѵ�.
	if (PlayerPosY < (0 + TILESIZE / 2))
	{
		_player->m_PosY += 100;	
	}
	// �� �����ʿ� ����� �� 
	if (PlayerPosX > (YH_MAPSIZE_X * TILESIZE - TILESIZE / 2))
	{
		// ������ȯ
		_player->ChangeDirection();
	}
	if (PlayerPosY > (YH_MAPSIZE_Y * TILESIZE - 70))
	{
		this->Init();
	}
	
	return false;
}

void YHScene::DebugDrawGrid()
{
	for (int j = 0; j < YH_MAPSIZE_Y; j++)
	{
		for (int i = 0; i < YH_MAPSIZE_X; i++)
		{
			if (m_pMap->GetType(i, j) == Block::BLOCK_EMPTY)
			{
				DrawRectangleForDebug(g_backBuffer->GetMemDC(),
					m_pMap->GetBox(i, j).left,
					m_pMap->GetBox(i, j).top,
					m_pMap->GetBox(i, j).right - 1,
					m_pMap->GetBox(i, j).bottom - 1,
					RGB(0, 255, 0));
			}
			else
			{
				DrawRectangleForDebug(g_backBuffer->GetMemDC(),
					m_pMap->GetBox(i, j).left,
					m_pMap->GetBox(i, j).top,
					m_pMap->GetBox(i, j).right - 1,
					m_pMap->GetBox(i, j).bottom - 1,
					RGB(255, 0, 255));
			}
		}
	}
}

void YHScene::DebugDrawPlayerCollisionBox()
{
	int CurPosInTileX = ((int)(_player->m_PosX + TILESIZE / 2) / TILESIZE) * TILESIZE;
	int CurPosInTileY = ((int)(_player->m_PosY + TILESIZE / 2 + TILESIZE) / TILESIZE) * TILESIZE;

	DrawRectangleForDebug(g_backBuffer->GetMemDC(),		// ���� �Ҽ� �׸��� �Ķ� �ڽ�
		CurPosInTileX,				// left
		CurPosInTileY,				// top
		CurPosInTileX + TILESIZE,	// right 
		CurPosInTileY + TILESIZE,	// bottom
		RGB(0, 0, 255));

	DrawRectangleForDebug(g_backBuffer->GetMemDC(),		// �߽� ��ǥ ��� �ڽ�
		_player->m_PosX,
		_player->m_PosY + TILESIZE,
		_player->m_PosX + TILESIZE,
		_player->m_PosY + TILESIZE * 2,
		RGB(255, 255, 0));

	DrawRectangleForDebug(g_backBuffer->GetMemDC(),		// �߽� ��ǥ ������ ��
		_player->m_PosX + TILESIZE / 2 - 1,
		_player->m_PosY + TILESIZE + TILESIZE / 2 - 1,
		_player->m_PosX + TILESIZE / 2 + 1,
		_player->m_PosY + TILESIZE + TILESIZE / 2 + 1,
		RGB(255, 0, 255));
}

void YHScene::DebugShowMouseInfo()
{
	// ���� ���콺 ��ǥ
	TCHAR mouseInfo[100];
	wsprintf(mouseInfo, TEXT("���콺 X ��ǥ = %d, ���콺 Y ��ǥ = %d"), _ptMouse.x, _ptMouse.y);
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 30 + _cameraY, mouseInfo, lstrlen(mouseInfo));

	// ���� ���콺�� Ŭ���� �迭 Ÿ�� ��
	TCHAR mousePickedBlockInfo[100];
	wsprintf(mousePickedBlockInfo, TEXT("���콺 Picked Block_Type = %d"), PickedMouseBlockType);
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 50 + _cameraY, mousePickedBlockInfo, lstrlen(mousePickedBlockInfo));

	// ���� ĳ���� ����
	// �̵��ӵ�
	TCHAR playerSpeed[100];
	wsprintf(playerSpeed, TEXT("ĳ���� Speed = %d"), _player->m_Speed);
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 70 + _cameraY, playerSpeed, lstrlen(playerSpeed));

	// ���� �����Ŀ�
	TCHAR current_playerJumpPower[100];
	wsprintf(current_playerJumpPower, TEXT("���� �ӵ� = %d"), static_cast<int>(_player->JumpPower));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 90 + _cameraY, current_playerJumpPower, lstrlen(current_playerJumpPower));

	// �Ϲ� �����Ŀ�
	TCHAR Max_playerJumpPower[150];
	wsprintf(Max_playerJumpPower, TEXT("ĳ���� JumpPower = %d"), static_cast<int>(_player->MaxJumpPower));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 110 + _cameraY, Max_playerJumpPower, lstrlen(Max_playerJumpPower));

	// ������ �����Ŀ�
	TCHAR springJumpPower[150];
	wsprintf(springJumpPower, TEXT("ĳ���� ������ JumpPower = %d"), static_cast<int>(_player->SpringJumpPower));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 130 + _cameraY, springJumpPower, lstrlen(springJumpPower));

	//

	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 150 + _cameraY, L"�Ϲ�   ���ǵ� ���� [�� ��]", lstrlen(L"�Ϲ�   ���ǵ� ���� [�� ��]"));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 170 + _cameraY, L"�Ϲ�   ������ ���� [�� �Ʒ�]", lstrlen(L"�Ϲ�   ������ ���� [�� �Ʒ�]"));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 190 + _cameraY, L"������ ������ ���� [W S]", lstrlen(L"������ ������ ���� [W S]"));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 210 + _cameraY, L"ĳ���� ���� ��ȯ [��Ʈ��Ctrl]", lstrlen(L"ĳ���� ���� ��ȯ [��Ʈ��Ctrl]"));


	//cout << "ĳ���� JumpPower = " << _player->JumpPower << "\n\n";

}

void YHScene::DebugShowMouseClickState()
{
	cout << "[���콺 ��Ŭ��] \n";
	cout << "_ptMouse.x = " << _ptMouse.x << "\n";
	cout << "_ptMouse.y = " << _ptMouse.y << "\n";
	cout << "���� ���� xĭ = " << _ptMouse.x / TILESIZE << "\n";
	cout << "���� ���� yĭ = " << _ptMouse.y / TILESIZE << "\n\n";

	//
	cout << "m_CurPickedGameBoard = " << m_CurPickedGameBoard << "\n";
	cout << "PickedMouseBlockType = " << (int)PickedMouseBlockType << "\n\n";

	// ���� ���� ������ ���
	cout << "[���� m_FirstGameBoard] \n";
	for (int j = 0; j < MAPSIZE_Y; j++)
	{
		for (int i = 0; i < MAPSIZE_X; i++)
		{
			cout << (int)m_pMap->GetType(i, j) << " ";	/// �𸣰���...;;
		}
		cout << "\n\n";
	}
}

void YHScene::CheckCurrentBoard(int x, int y)
{
	int CurMouseX = _ptMouse.x / TILESIZE;
	int CurMouseY = _ptMouse.y / TILESIZE;

	m_CurPickedGameBoard = m_pMap->GetBoardSet(CurMouseX, CurMouseY);

}

bool YHScene::IsChangeMode()
{
	// Q �Է½� ��� ��ȯ
	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
	{
		// ���Ӹ�� ��ȯ�ϰ�
		if (_gameState == Game_State::Play)
		{
			cout << "Game Mode Change! [Play -> Edit]\n\n";
			_gameState = Game_State::Edit;
		}

		else if (_gameState == Game_State::Edit)
		{
			cout << "Game Mode Change! [Edit -> Play]\n\n";
			_gameState = Game_State::Play;
		}

		// ���� true
		return true;
	}

	// ���Ӹ�尡 �ٲ��� �ʾ���. ���� ��� ����..
	return false;
}

void YHScene::SelectDeployButton()
{
	cout << "[SelectDeployButtocn]\n";

	RECT btnButton01 = _btnDeployTile_01->GetCollisionBox();
	RECT btnButton02 = _btnDeployTile_02->GetCollisionBox();

	// ���� �������� �ƴѵ� ��ư01�� Ŭ���߳�?
	if (!_isSelectMode && PtInRect(&btnButton01, _ptMouse))
	{
		// ���� Ÿ���� �������� ���·� ����
		_isSelectMode = true;

		// ��ư01�� Ÿ��(ROCK) ����
		PickedMouseBlockType = Block::BLOCK_ROCK;

		cout << "��ư 01 Ŭ��\n";
		cout << "���� ���õ� ��� = " << static_cast<int>(PickedMouseBlockType) << "\n";
	}

	else if (!_isSelectMode && PtInRect(&btnButton02, _ptMouse))
	{
		// ���� Ÿ���� �������� ���·� ����
		_isSelectMode = true;

		// ��ư01�� Ÿ��(ROCK) ����
		PickedMouseBlockType = Block::BLOCK_LONG_ROCK;

		cout << "��ư 02 Ŭ��\n";
		cout << "���� ���õ� ��� = " << static_cast<int>(PickedMouseBlockType) << "\n";
	}

	else
	{
		// ���콺�� ��ǥ�� �迭 ��ҷ� ���ø� �Ѵ�
		int CurMouseX = _ptMouse.x / TILESIZE;
		int CurMouseY = _ptMouse.y / TILESIZE;

		// ���� ���忡�� ���� ������ ���� Ÿ���� ���´�.
		Block temp = m_pMap->CheckCurrentBoard(CurMouseX, CurMouseY);

		cout << "Ŭ���� ���� ��� Ÿ���� -> " << static_cast<int>(temp) << "\n\n";

		// ���� �����ÿ� ���õǾ� �ִ� ����� �����ϰ� ��ġ�� �� �ִ� ���̸�
		if (temp == Block::BLOCK_EMPTY)
		{
			// ���� ���� ����� Ÿ���� 1ĭ¥�� ����̸�
			if (PickedMouseBlockType == Block::BLOCK_ROCK)
			{
				// �� Ÿ��(ĭ)�� ��ĭ¥�� ����� �ִ´�.
				m_pMap->SetType(CurMouseX, CurMouseY, Block::BLOCK_ROCK);


				printf("��ġ ��ġ = [%d,%d] / ��ġ Ÿ�� = [%d]\n\n", CurMouseX, CurMouseY, Block::BLOCK_ROCK);

				// �ٽ� �ƹ� ��(���)�� ��� ���� �ʴ� ���·� ����
				PickedMouseBlockType = Block::BLOCK_MOUSEEMPTY;
			}

			// ���� ���� ����� Ÿ���� 5ĭ¥�� ����̸�
			else if (PickedMouseBlockType == Block::BLOCK_LONG_ROCK)
			{
				// ������ ĭ���� ���������� 5ĭ�� Ÿ���� �˾ƿͼ� ��ġ�������� �Ǵ��Ѵ�
				for (int x = CurMouseX; x < CurMouseX + 5; x++)
				{
					if (m_pMap->GetType(x, CurMouseY) != Block::BLOCK_EMPTY)
					{
						cout << "�� ������ ��ġ �� �� ����!\n\n";
						return;
					}
				}

				// ��ġ�� �� �ִٰ� �Ǵ� �Ǹ�
				for (int x = CurMouseX; x < CurMouseX + 5; x++)
				{
					// �����ؼ� ��� Ÿ������ �����Ѵ�.
					m_pMap->SetType(x, CurMouseY, Block::BLOCK_ROCK);
					printf("��ġ ��ġ = [%d,%d] / ��ġ Ÿ�� = [%d]\n\n", CurMouseX, CurMouseY, Block::BLOCK_ROCK);

				}

				// �ٽ� �ƹ� ��(���)�� ��� ���� �ʴ� ���·� ����
				PickedMouseBlockType = Block::BLOCK_MOUSEEMPTY;
			}

		}

		_isSelectMode = false;
		cout << "���ø�� ����~~~~\n\n";
	}
}

void YHScene::RenderTile()
{
	Block checkBlockType = Block::BLOCK_EMPTY;
	int renderPosX = 0;
	int renderPosY = 0;

	for (int y = 0; y < MAPSIZE_Y; y++)
	{
		for (int x = 0; x < MAPSIZE_X; x++)
		{
			checkBlockType = m_pMap->GetType(x, y);
			renderPosX = m_pMap->GetBox(x, y).left;
			renderPosY = m_pMap->GetBox(x, y).top;

			switch (checkBlockType)
			{
				// ���� Ÿ���� ����ִ� ���̸�
			case Block::BLOCK_EMPTY:
			{
				// �ƹ��͵� �� �׸�
				break;
			}

			// ���� Ÿ���� �⺻ ����� �ִ� ���̸�
			case Block::BLOCK_BASIC:
			{
				// �� ��ġ��  grass01 �� �׸�
				_grass01Img->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

				break;
			}

			// ���� Ÿ���� ����(8) ����� �ִ� ���̸�
			case Block::BLOCK_ROCK:
			{
				// �� ��ġ��  BLOCK �� �׸�
				_btnDeployTile_01->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

				break;
			}

			case Block::BLOCK_KEY:
			{
				// �� ��ġ��  grass01 �� �׸�
				_key->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

				break;
			}
			case Block::BLOCK_DOOR_CLOSE:
			{
				// �� ��ġ��  grass01 �� �׸�
				_doorClose->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

				break;
			}
			case Block::BLOCK_DOOR_OPEN:
			{
				// �� ��ġ��  grass01 �� �׸�
				_doorOpen->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

				break;
			}

			}// end of Switch
		}
	}
}

void YHScene::RenderUI()
{
	//cout << "Edit Mode UI Render \n\n";
	_btnDeployTile_01->Render(g_backBuffer->GetMemDC(), _btnDeployTile_01->GetX(), _btnDeployTile_01->GetY());
	_btnDeployTile_02->Render(g_backBuffer->GetMemDC(), _btnDeployTile_02->GetX(), _btnDeployTile_02->GetY());

}

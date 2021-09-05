#include "pch.h"

//
#include "Player.h"
//#include "ObjectBox.h"
#include "Map.h"
//
#include "TestScene.h"

TestScene::TestScene()
	: _bgImg(nullptr)
	, _player(nullptr)
{
}

TestScene::~TestScene()
{
}

HRESULT TestScene::Init()
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

	_player = new Player;
	_player->Initialize(70, 100, 700);
	_player->_img = IMAGEMANAGER->FindImage("PLAYER");

	/*for (int j = 0; j < MAPSIZE_Y; j++)
	{
		for (int i = 0; i < MAPSIZE_X; i++)
		{
			_floor[j][i] = new ObjectBox;
			_floor[j][i]->Initialize(70, 70 * i, 70 * j);
			_floor[j][i]->_img = IMAGEMANAGER->FindImage("GRASS_01");
		}
	}*/

	return S_OK;
}

void TestScene::Release()
{
	SAFE_DELETE(_player);
	/*for (int j = 0; j < MAPSIZE_Y; j++)
	{
		for (int i = 0; i < MAPSIZE_X; i++)
			SAFE_DELETE(_floor[j][i]);
	}*/
}

void TestScene::Update()
{
	//if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	//{
	//	DebugShowMouseClickState();
	//
	//	CheckCurrentBoard(g_ptMouse.x, g_ptMouse.y);
	//
	//	//if (PickedMouseBlockType == Block::BLOCK_MOUSEEMPTY)
	//	//{
	//	//	CopyCurMouseBlockType();
	//	//}
	//	//else if (PickedMouseBlockType != Block::BLOCK_MOUSEEMPTY)
	//	//{
	//	//	PasteCurMouseBlockType(g_ptMouse.x, g_ptMouse.y);
	//	//}
	//}

	_player->PlayerAutoMove();

	_player->PlayerGravity();

	_player->PlayerCheckFloor(m_pMap);

	_player->PlayerCheckEmptyFloor(m_pMap);

	_player->PlayerCheckWall(m_pMap);

	_player->PlayerCheckKey(m_pMap);

	_player->ConfinePlayerinMap();

	_player->GetMapInfo(m_pMap);

	_player->PlayerCheckDoor(m_pMap);

	_player->PlayerCheckUpTile(m_pMap);
}

void TestScene::Render()
{
	_bgImg->Render(g_backBuffer->GetMemDC(), 0, -380);

	RenderTile();

	_player->_img->FrameRender(g_backBuffer->GetMemDC(), _player->m_PosX, _player->m_PosY);

	DebugDrawGrid();

	DebugDrawPlayerCollisionBox();

	_player->DebugShowPlayerPosArray();

	DebugShowMouseInfo();
}

void TestScene::InputBoardData()
{
	for (int j = 0; j < MAPSIZE_Y; j++)
	{
		for (int i = 0; i < MAPSIZE_X; i++)
		{
			m_pMap->SetType(i, j, (Block)m_StageOneData[j][i]);
		}
	}
}

void TestScene::DebugDrawGrid()
{
	for (int j = 0; j < MAPSIZE_Y; j++)
	{
		for (int i = 0; i < MAPSIZE_X; i++)
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

void TestScene::DebugDrawPlayerCollisionBox()
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

void TestScene::DebugShowMouseInfo()
{
	// ���� ���콺 ��ǥ
	TCHAR mouseInfo[100];
	wsprintf(mouseInfo, TEXT("���콺 X ��ǥ = %d, ���콺 Y ��ǥ = %d"), g_ptMouse.x, g_ptMouse.y);
	TextOut(g_backBuffer->GetMemDC(), 10, 30, mouseInfo, lstrlen(mouseInfo));

	// ���� ���콺�� Ŭ���� �迭 Ÿ�� ��
	TCHAR mousePickedBlockInfo[100];
	wsprintf(mousePickedBlockInfo, TEXT("���콺 Picked Block_Type = %d"), PickedMouseBlockType);
	TextOut(g_backBuffer->GetMemDC(), 10, 50, mousePickedBlockInfo, lstrlen(mousePickedBlockInfo));
}

void TestScene::DebugShowMouseClickState()
{
	cout << "[���콺 ��Ŭ��] \n";
	cout << "g_ptMouse.x = " << g_ptMouse.x << "\n";
	cout << "g_ptMouse.y = " << g_ptMouse.y << "\n";
	cout << "���� ���� xĭ = " << g_ptMouse.x / TILESIZE << "\n";
	cout << "���� ���� yĭ = " << g_ptMouse.y / TILESIZE << "\n\n";

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

void TestScene::CheckCurrentBoard(int x, int y)
{
	int CurMouseX = g_ptMouse.x / TILESIZE;
	int CurMouseY = g_ptMouse.y / TILESIZE;

	m_CurPickedGameBoard = m_pMap->GetBoardSet(CurMouseX, CurMouseY);
}

void TestScene::CopyCurMouseBlockType()
{
	PickedMouseBlockType = m_CurPickedGameBoard->m_Type;
}

void TestScene::PasteCurMouseBlockType(int x, int y)
{
	int CurMouseX = g_ptMouse.x / TILESIZE;
	int CurMouseY = g_ptMouse.y / TILESIZE;

	m_CurPickedGameBoard->m_Type = (Block)PickedMouseBlockType;

	m_pMap->SetType(CurMouseX, CurMouseY, m_CurPickedGameBoard->m_Type);

	PickedMouseBlockType = Block::BLOCK_MOUSEEMPTY;
}

void TestScene::RenderTile()
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

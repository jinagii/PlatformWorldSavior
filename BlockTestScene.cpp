#include "pch.h"

//
#include "Player.h"
//#include "ObjectBox.h"
#include "Map.h"

//
#include "BlockTestScene.h"

BlockTestScene::BlockTestScene()
	: _bgImg(nullptr)
	, _player(nullptr)
{
	PickedMouseBlockType = (Block)MOUSE_EMPTY;
}

BlockTestScene::~BlockTestScene()
{
}

HRESULT BlockTestScene::Init()
{
	// 맵 정보 세팅
	m_pMap = new Map();
	m_pMap->Initialize();
	InputBoardData();

	/// 이미지 연결
	// 백그라운드 이미지
	_bgImg = IMAGEMANAGER->FindImage("BG_MOUNTAIN");
	_grass01Img = IMAGEMANAGER->FindImage("GRASS_01");
	_ground01Img = IMAGEMANAGER->FindImage("GROUND_01");
	_ground02Img = IMAGEMANAGER->FindImage("GROUND_02");
	_unground03Img = IMAGEMANAGER->FindImage("UGROUND_01");

	_player = new Player;
	_player->Initialize(70, 100, 700);
	_player->_img = IMAGEMANAGER->FindImage("PLAYER");

	//for (int j = 0; j < MAPSIZE_Y; j++)
	//{
	//	for (int i = 0; i < MAPSIZE_X; i++)
	//	{
	//		//_floor[j][i] = new ObjectBox;
	//		_floor[j][i]->Initialize(70, 70 * i, 70 * j);
	//		_floor[j][i]->_img = IMAGEMANAGER->FindImage("GRASS_01");
	//	}
	//}

	return S_OK;
}

void BlockTestScene::Release()
{
	SAFE_DELETE(_player);
	//for (int j = 0; j < MAPSIZE_Y; j++)
	//{
	//	for (int i = 0; i < MAPSIZE_X; i++)
	//		SAFE_DELETE(_floor[j][i]);
	//}
}

void BlockTestScene::Update()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		m_pMap->ShowMouseInfo();
		m_pMap->CheckCurrentBoard(g_ptMouse.x, g_ptMouse.y);
	}

	_player->PlayerAutoMove();

	//_player->PlayerGravity();

	_player->PlayerCheckFloor(m_pMap);

	_player->PlayerCheckWall(m_pMap);

	_player->ConfinePlayerinMap();

	_player->PlayerCheckUpTile(m_pMap);
}

void BlockTestScene::Render()
{
	_bgImg->Render(g_backBuffer->GetMemDC(), 0, -380);

	RenderTile();

	_player->_img->FrameRender(g_backBuffer->GetMemDC(), _player->m_PosX, _player->m_PosY);

	//m_pMap->DrawGrid();

	m_pMap->ShowMouseInfo();

	_player->DebugShowPlayerPosArray();
}

void BlockTestScene::InputBoardData()
{
	for (int j = 0; j < MAPSIZE_Y; j++)
	{
		for (int i = 0; i < MAPSIZE_X; i++)
		{
			m_pMap->SetType(i, j, (Block)m_StageOneData[j][i]);
		}
	}
}

void BlockTestScene::CopyCurMouseBlockType(int x, int y)
{
	int CurMouseX = g_ptMouse.x / TILESIZE;
	int CurMouseY = g_ptMouse.y / TILESIZE;

	m_pMap->GetBoardSet(CurMouseX, CurMouseY)->m_Type = PickedMouseBlockType;
	//PickedMouseBlockType = m_CurPickedGameBoard->m_Type;
}

void BlockTestScene::PasteCurMouseBlockType(int x, int y)
{
	int CurMouseX = g_ptMouse.x / TILESIZE;
	int CurMouseY = g_ptMouse.y / TILESIZE;

	//m_CurPickedGameBoard->m_Type = (Block)PickedMouseBlockType;

	m_pMap->m_pGameBoard[CurMouseY][CurMouseX]->m_Type = m_pMap->GetBoardSet(CurMouseX, CurMouseY)->m_Type;

	PickedMouseBlockType = (Block)MOUSE_EMPTY;
}

// 멀티 블럭 구현중
void BlockTestScene::PasteCurMouseMultiBlockType(int x, int y)
{
	int CurMouseX = g_ptMouse.x / TILESIZE;
	int CurMouseY = g_ptMouse.y / TILESIZE;

	m_CurPickedGameBoard->m_Type = (Block)PickedMouseBlockType;

	m_pMap->SetType(CurMouseX, CurMouseY, m_CurPickedGameBoard->m_Type);

	PickedMouseBlockType = (Block)MOUSE_EMPTY;
}

void BlockTestScene::RenderTile()
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
				// 현재 타일이 비어있는 곳이면
				case Block::BLOCK_EMPTY:
				{
					// 아무것도 안 그림
					break;
				}

				// 현재 타일이 기본으로 설치된 블록이 있는 곳이면
				case Block::BLOCK_BASIC:
				{
					// 이 위치에  grass01 을 그림
					_grass01Img->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

					break;
				}

				case Block::BLOCK_UNDERGROUND02:
				{
					// 이 위치에  grass01 을 그림
					_ground02Img->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

					break;
				}

				case Block::BLOCK_UNDERGROUND03:
				{
					// 이 위치에  grass01 을 그림
					_unground03Img->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

					break;
				}
			}// end of Switch
		}
	}
}
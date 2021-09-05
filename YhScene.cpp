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
		cout << "스테이지 01 Init\n\n";
		Init_Stage01();
		break;

	case 2:
		cout << "스테이지 02 Init\n\n";
		Init_Stage01();
		break;
	}

	return S_OK;
}

void YHScene::Init_Stage01()
{
	// 맵 정보 세팅
	m_pMap = new Map();
	m_pMap->Initialize();
	InputBoardData();

	/// 이미지 연결
	// 백그라운드 이미지
	_bgImg = IMAGEMANAGER->FindImage("BG_MOUNTAIN");
	_grass01Img = IMAGEMANAGER->FindImage("GRASS_01");

	//문과 키
	_key = IMAGEMANAGER->FindImage("KEY");
	_doorClose = IMAGEMANAGER->FindImage("DOOR_CLOSE");
	_doorOpen = IMAGEMANAGER->FindImage("DOOR_OPEN");

	// 캐릭터의 시작 타일 구하기
	//POINT pos = CalcCharSetPos(15, MAPSIZE_Y - 9);
	POINT pos = CalcCharSetPos(10, 4);

	// 플레이어 세팅
	_player = new Player;
	_player->Initialize(70, pos.x, pos.y);
	_player->_img = IMAGEMANAGER->FindImage("PLAYER");
	printf_s("캐릭터 위치[%f,%f] \n\n", _player->m_PosX, _player->m_PosY);

	/// 순서 중요

	// 카메라 위치 세팅
	MoveCamera();

	// 인게임 마우스 좌표 세팅
	MappingMousePoint();

	// 배치 타일 버튼
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
	/// 메인 스크린(DC)에 보여지게될 영역 조정(카메라 이동)
	MoveCamera();

	/// 실제 위치와 윈도우(창) 사이에 생기는 좌표 오차 조정
	MappingMousePoint();
	MappingUI();

	////////////////
	/// 인게임 내 캐릭터 속성 조절
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

		/// 플레이 모드
	case Game_State::Play:
	{
		if (IsChangeMode())
		{
			// 모드가 바뀌었으면 리턴하고 다시 프레임을 돌린다
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
			// 모드가 바뀌었으면 리턴하고 다시 프레임을 돌린다
			return;
		}

		// 마우스 왼 클릭이 됐으면
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			cout << "마우스 왼클릭 \n\n";
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
	// 배경을 먼저 그린다.
	_bgImg->Render(g_backBuffer->GetMemDC(), 0, 0);

	// 타일(블록)을 그린다.
	RenderTile();

	// 플레이어를 그린다.(프레임 애니메이션)
	_player->_img->FrameRender(g_backBuffer->GetMemDC(), _player->m_PosX, _player->m_PosY);

	_player->DebugShowPlayerPosArray();

	DebugShowMouseInfo();


	// 배치모드 UI 렌더
	if (_gameState == Game_State::Edit)
	{
		RenderUI();
		//. 라인 격자 그리기
		m_pMap->DrawGrid();

	}

	if (_isSelectMode)
	{
		switch (PickedMouseBlockType)
		{
			// 1칸 블록을 선택 중일 때
		case Block::BLOCK_ROCK:
		{
			_btnDeployTile_01->Render(g_backBuffer->GetMemDC(), _ptMouse.x - TILESIZE / 2, _ptMouse.y - TILESIZE / 2);
			break;
		}

		// 5칸 블록을 선택 중일 때
		case Block::BLOCK_LONG_ROCK:
		{
			_btnDeployTile_02->Render(g_backBuffer->GetMemDC(), _ptMouse.x - TILESIZE / 2, _ptMouse.y - TILESIZE / 2);
			break;
		}

		}// end of switch
	}

	// 카메라 렌더
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
	// 카메라 좌표 설정
	_cameraX = _player->m_PosX - (WINSIZEX / 2);
	_cameraY = _player->m_PosY - (WINSIZEY / 2);

	// ********* 카메라가 맵을 벗어나지 않도록 위치 조정 **********************

	// 캐릭터가 왼쪽 끝에 가까워져 카메라가 왼쪽으로 이동하면 안될 때
	if (_player->m_PosX - WINSIZEX / 2 <= 0) _cameraX = 0;

	// 캐릭터가 위쪽 끝에 가까워져 카메라가 위쪽으로 이동하면 안될 때
	if (_player->m_PosY - WINSIZEY / 2 <= 0) _cameraY = 0;

	// 캐릭터가 오른쪽 끝에 가까워져 카메라가 오른쪽으로 이동하면 안될 때
	if (_player->m_PosX + WINSIZEX / 2 > _bgImg->GetWidth()) _cameraX = _bgImg->GetWidth() - WINSIZEX;

	// 캐릭터가 아래쪽 끝에 가까워져 카메라가 아래쪽으로 이동하면 안될 때
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

// 배열원소 0번부터 size-1 의 좌표로 입력하시오.
// 0 ~ MAPSIZE - 1
POINT YHScene::CalcCharSetPos(int x, int y)
{
	POINT pos;
	pos.x = x * TILESIZE;
	pos.y = (y * TILESIZE) - TILESIZE;	// 캐릭터가 타일 사이즈 기준 1*2 사이즈라(70px,140px) y는 70만큼 위로 보정해 줌

	return pos;
}

bool YHScene::CheckPlayerPos(float x, float y)
{
	int PlayerPosX = _player->m_PosX + TILESIZE / 2;				// 중심 좌표
	int PlayerPosY = _player->m_PosY + TILESIZE + TILESIZE / 2;

	// 맵 왼쪽에 닿았을 때 방향 전환
	if (PlayerPosX < (0 + TILESIZE / 2))
	{
		_player->ChangeDirection();
	}

	// 맵 위로 뚫고 올라갈 떄 대충 보정한다.
	if (PlayerPosY < (0 + TILESIZE / 2))
	{
		_player->m_PosY += 100;	
	}
	// 맵 오른쪽에 닿았을 때 
	if (PlayerPosX > (YH_MAPSIZE_X * TILESIZE - TILESIZE / 2))
	{
		// 방향전환
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

	DrawRectangleForDebug(g_backBuffer->GetMemDC(),		// 현재 소속 그리드 파랑 박스
		CurPosInTileX,				// left
		CurPosInTileY,				// top
		CurPosInTileX + TILESIZE,	// right 
		CurPosInTileY + TILESIZE,	// bottom
		RGB(0, 0, 255));

	DrawRectangleForDebug(g_backBuffer->GetMemDC(),		// 중심 좌표 노랑 박스
		_player->m_PosX,
		_player->m_PosY + TILESIZE,
		_player->m_PosX + TILESIZE,
		_player->m_PosY + TILESIZE * 2,
		RGB(255, 255, 0));

	DrawRectangleForDebug(g_backBuffer->GetMemDC(),		// 중심 좌표 빨강색 점
		_player->m_PosX + TILESIZE / 2 - 1,
		_player->m_PosY + TILESIZE + TILESIZE / 2 - 1,
		_player->m_PosX + TILESIZE / 2 + 1,
		_player->m_PosY + TILESIZE + TILESIZE / 2 + 1,
		RGB(255, 0, 255));
}

void YHScene::DebugShowMouseInfo()
{
	// 현재 마우스 좌표
	TCHAR mouseInfo[100];
	wsprintf(mouseInfo, TEXT("마우스 X 좌표 = %d, 마우스 Y 좌표 = %d"), _ptMouse.x, _ptMouse.y);
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 30 + _cameraY, mouseInfo, lstrlen(mouseInfo));

	// 현재 마우스가 클릭한 배열 타입 값
	TCHAR mousePickedBlockInfo[100];
	wsprintf(mousePickedBlockInfo, TEXT("마우스 Picked Block_Type = %d"), PickedMouseBlockType);
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 50 + _cameraY, mousePickedBlockInfo, lstrlen(mousePickedBlockInfo));

	// 현재 캐릭터 정보
	// 이동속도
	TCHAR playerSpeed[100];
	wsprintf(playerSpeed, TEXT("캐릭터 Speed = %d"), _player->m_Speed);
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 70 + _cameraY, playerSpeed, lstrlen(playerSpeed));

	// 현재 점프파워
	TCHAR current_playerJumpPower[100];
	wsprintf(current_playerJumpPower, TEXT("현재 속도 = %d"), static_cast<int>(_player->JumpPower));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 90 + _cameraY, current_playerJumpPower, lstrlen(current_playerJumpPower));

	// 일반 점프파워
	TCHAR Max_playerJumpPower[150];
	wsprintf(Max_playerJumpPower, TEXT("캐릭터 JumpPower = %d"), static_cast<int>(_player->MaxJumpPower));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 110 + _cameraY, Max_playerJumpPower, lstrlen(Max_playerJumpPower));

	// 스프링 점프파워
	TCHAR springJumpPower[150];
	wsprintf(springJumpPower, TEXT("캐릭터 스프링 JumpPower = %d"), static_cast<int>(_player->SpringJumpPower));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 130 + _cameraY, springJumpPower, lstrlen(springJumpPower));

	//

	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 150 + _cameraY, L"일반   스피드 조절 [좌 우]", lstrlen(L"일반   스피드 조절 [좌 우]"));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 170 + _cameraY, L"일반   점프력 조절 [위 아래]", lstrlen(L"일반   점프력 조절 [위 아래]"));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 190 + _cameraY, L"스프링 점프력 조절 [W S]", lstrlen(L"스프링 점프력 조절 [W S]"));
	TextOut(g_backBuffer->GetMemDC(), 10 + _cameraX, 210 + _cameraY, L"캐릭터 방향 전환 [컨트롤Ctrl]", lstrlen(L"캐릭터 방향 전환 [컨트롤Ctrl]"));


	//cout << "캐릭터 JumpPower = " << _player->JumpPower << "\n\n";

}

void YHScene::DebugShowMouseClickState()
{
	cout << "[마우스 왼클릭] \n";
	cout << "_ptMouse.x = " << _ptMouse.x << "\n";
	cout << "_ptMouse.y = " << _ptMouse.y << "\n";
	cout << "현재 선택 x칸 = " << _ptMouse.x / TILESIZE << "\n";
	cout << "현재 선택 y칸 = " << _ptMouse.y / TILESIZE << "\n\n";

	//
	cout << "m_CurPickedGameBoard = " << m_CurPickedGameBoard << "\n";
	cout << "PickedMouseBlockType = " << (int)PickedMouseBlockType << "\n\n";

	// 보드 내용 디버깅용 출력
	cout << "[현재 m_FirstGameBoard] \n";
	for (int j = 0; j < MAPSIZE_Y; j++)
	{
		for (int i = 0; i < MAPSIZE_X; i++)
		{
			cout << (int)m_pMap->GetType(i, j) << " ";	/// 모르겠음...;;
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
	// Q 입력시 모드 전환
	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
	{
		// 게임모드 전환하고
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

		// 리턴 true
		return true;
	}

	// 게임모드가 바뀌지 않았음. 현재 모드 진행..
	return false;
}

void YHScene::SelectDeployButton()
{
	cout << "[SelectDeployButtocn]\n";

	RECT btnButton01 = _btnDeployTile_01->GetCollisionBox();
	RECT btnButton02 = _btnDeployTile_02->GetCollisionBox();

	// 현재 선택중이 아닌데 버튼01을 클릭했나?
	if (!_isSelectMode && PtInRect(&btnButton01, _ptMouse))
	{
		// 뭔가 타일을 선택중인 상태로 변경
		_isSelectMode = true;

		// 버튼01의 타입(ROCK) 저장
		PickedMouseBlockType = Block::BLOCK_ROCK;

		cout << "버튼 01 클릭\n";
		cout << "현재 선택된 블록 = " << static_cast<int>(PickedMouseBlockType) << "\n";
	}

	else if (!_isSelectMode && PtInRect(&btnButton02, _ptMouse))
	{
		// 뭔가 타일을 선택중인 상태로 변경
		_isSelectMode = true;

		// 버튼01의 타입(ROCK) 저장
		PickedMouseBlockType = Block::BLOCK_LONG_ROCK;

		cout << "버튼 02 클릭\n";
		cout << "현재 선택된 블록 = " << static_cast<int>(PickedMouseBlockType) << "\n";
	}

	else
	{
		// 마우스의 좌표를 배열 요소로 샘플링 한다
		int CurMouseX = _ptMouse.x / TILESIZE;
		int CurMouseY = _ptMouse.y / TILESIZE;

		// 게임 보드에서 현재 선택한 곳의 타입을 얻어온다.
		Block temp = m_pMap->CheckCurrentBoard(CurMouseX, CurMouseY);

		cout << "클릭한 곳의 블록 타입은 -> " << static_cast<int>(temp) << "\n\n";

		// 선택 해제시에 선택되어 있던 블록이 존재하고 설치할 수 있는 곳이면
		if (temp == Block::BLOCK_EMPTY)
		{
			// 내가 집은 블록의 타입이 1칸짜리 블록이면
			if (PickedMouseBlockType == Block::BLOCK_ROCK)
			{
				// 그 타일(칸)에 한칸짜리 블록을 넣는다.
				m_pMap->SetType(CurMouseX, CurMouseY, Block::BLOCK_ROCK);


				printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX, CurMouseY, Block::BLOCK_ROCK);

				// 다시 아무 것(블록)도 들고 있지 않는 상태로 변경
				PickedMouseBlockType = Block::BLOCK_MOUSEEMPTY;
			}

			// 내가 집은 블록의 타입이 5칸짜리 블록이면
			else if (PickedMouseBlockType == Block::BLOCK_LONG_ROCK)
			{
				// 선택한 칸부터 오른쪽으로 5칸의 타입을 알아와서 설치가능한지 판단한다
				for (int x = CurMouseX; x < CurMouseX + 5; x++)
				{
					if (m_pMap->GetType(x, CurMouseY) != Block::BLOCK_EMPTY)
					{
						cout << "그 곳에는 설치 할 수 없다!\n\n";
						return;
					}
				}

				// 설치할 수 있다고 판단 되면
				for (int x = CurMouseX; x < CurMouseX + 5; x++)
				{
					// 연속해서 블록 타입으로 설정한다.
					m_pMap->SetType(x, CurMouseY, Block::BLOCK_ROCK);
					printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX, CurMouseY, Block::BLOCK_ROCK);

				}

				// 다시 아무 것(블록)도 들고 있지 않는 상태로 변경
				PickedMouseBlockType = Block::BLOCK_MOUSEEMPTY;
			}

		}

		_isSelectMode = false;
		cout << "선택모드 해제~~~~\n\n";
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
				// 현재 타일이 비어있는 곳이면
			case Block::BLOCK_EMPTY:
			{
				// 아무것도 안 그림
				break;
			}

			// 현재 타일이 기본 블록이 있는 곳이면
			case Block::BLOCK_BASIC:
			{
				// 이 위치에  grass01 을 그림
				_grass01Img->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

				break;
			}

			// 현재 타일이 벽돌(8) 블록이 있는 곳이면
			case Block::BLOCK_ROCK:
			{
				// 이 위치에  BLOCK 을 그림
				_btnDeployTile_01->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

				break;
			}

			case Block::BLOCK_KEY:
			{
				// 이 위치에  grass01 을 그림
				_key->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

				break;
			}
			case Block::BLOCK_DOOR_CLOSE:
			{
				// 이 위치에  grass01 을 그림
				_doorClose->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

				break;
			}
			case Block::BLOCK_DOOR_OPEN:
			{
				// 이 위치에  grass01 을 그림
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

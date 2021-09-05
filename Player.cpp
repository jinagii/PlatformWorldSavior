#include "pch.h"
#include "Player.h"
//#include "AABB.h"
//#include "TestScene.h"
#include "Map.h"

Player::Player()
{
	// 사운드 연결
	m_JumpSound		= SOUNDMANAGER->FindSound("JUMP");
	m_SpringJumpSound	= SOUNDMANAGER->FindSound("SPRINGJUMP");
	m_LandingSound		= SOUNDMANAGER->FindSound("LAND");
	m_DyingSound			= SOUNDMANAGER->FindSound("DIE");
}

Player::~Player()
{

}

// 플레이어 자동 움직임 함수
void Player::PlayerAutoMove()
{
	m_PosX += m_Speed * m_XDirection;
}

// 플레이어 중력 함수
void Player::PlayerGravity()
{
	if (m_JumpPower > 0)
	{
		m_PlayerState = DOWN;

		m_Gravity = 2.0f;
	}
	else if (m_JumpPower < 0)
	{
		m_PlayerState = UP;

		m_Gravity = 2.0f;
	}

	if (m_PlayerState == UP || m_PlayerState == DOWN)
	{
		m_JumpPower += m_Gravity;

		m_PosY = m_PosY + m_JumpPower;
	}
}

// 좌우 방향 전환 함수
void Player::ChangeDirection()
{
	m_XDirection = m_XDirection * -1;

	if (m_XDirection == 1)
	{
		_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_R");
		_img->SetCurFrameX(0);
      cout << "방향 전환" << endl;
	}

	if (m_XDirection == -1)
	{
		_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_L");
		_img->SetCurFrameX(0);
      cout << "방향 전환" << endl;
	}
}

// 플레이어 점프 함수
/// 분석 필요
void Player::PlayerJump()
{
	m_PlayerState = UP;

	m_JumpPower = m_MaxJumpPower;

	// 스프라이트 이미지 변경	
	if (m_XDirection == 1)
	{
		_img = IMAGEMANAGER->FindImage("PLAYER_JUMP_R");
		_img->SetCurFrameX(0);
	}
	
	if (m_XDirection == -1)
	{
		_img = IMAGEMANAGER->FindImage("PLAYER_JUMP_L");
		_img->SetCurFrameX(0);
	}

	// 점프 사운드 재생
	m_JumpSound->soundSeek(0);
	cout << m_JumpSound->soundPlay() << endl;
	cout << "노말 점프" << endl;
}

void Player::SpringJump()
{
	m_PlayerState = UP;

	m_JumpPower = m_SpringJumpPower;

	//m_Speed = 4;

	// 스프라이트 이미지 변경
	if (m_XDirection == 1)
	{
		_img = IMAGEMANAGER->FindImage("PLAYER_JUMP_R");
		_img->SetCurFrameX(0);
	}

	if (m_XDirection == -1)
	{
		_img = IMAGEMANAGER->FindImage("PLAYER_JUMP_L");
		_img->SetCurFrameX(0);
	}

	// 점프 사운드 재생
	m_SpringJumpSound->soundSeek(0);
	cout << m_SpringJumpSound->soundPlay() << endl;
	cout << "스프링 점프" << endl;
}



// 벽 감지 함수
void Player::PlayerCheckWall(Map* Curboard)
{
	int GridX_3 = (int)(m_PosX + TILESIZE) / TILESIZE;
	int GridX_1 = (int)(m_PosX + TILESIZE - TILESIZE) / TILESIZE;

	int GridY_3 = (int)(m_PosY + TILESIZE + TILESIZE / 2) / TILESIZE;

	if ((Curboard->m_pGameBoard[GridY_3][GridX_3]->m_Type != Block::BLOCK_EMPTY &&
		Curboard->m_pGameBoard[GridY_3][GridX_3]->m_Type != Block::BLOCK_KEY &&
		Curboard->m_pGameBoard[GridY_3][GridX_3]->m_Type != Block::BLOCK_SPRING &&
		Curboard->m_pGameBoard[GridY_3][GridX_3]->m_Type != Block::BLOCK_DOOR_OPEN &&
		Curboard->m_pGameBoard[GridY_3][GridX_3]->m_Type != Block::CHAR_START_POS &&
		Curboard->m_pGameBoard[GridY_3][GridX_3]->m_Type != Block::BLOCK_EMPTY &&
		Curboard->m_pGameBoard[GridY_3][GridX_3]->m_Type != Block::BLOCK_WATER &&
		Curboard->m_pGameBoard[GridY_3][GridX_3]->m_Type != Block::BLOCK_UWATER &&
		m_XDirection == 1) || (
			Curboard->m_pGameBoard[GridY_3][GridX_1]->m_Type != Block::BLOCK_EMPTY &&
			Curboard->m_pGameBoard[GridY_3][GridX_1]->m_Type != Block::BLOCK_KEY &&
			Curboard->m_pGameBoard[GridY_3][GridX_1]->m_Type != Block::BLOCK_SPRING &&
			Curboard->m_pGameBoard[GridY_3][GridX_1]->m_Type != Block::BLOCK_DOOR_OPEN &&
			Curboard->m_pGameBoard[GridY_3][GridX_1]->m_Type != Block::CHAR_START_POS &&
			Curboard->m_pGameBoard[GridY_3][GridX_1]->m_Type != Block::BLOCK_UWATER &&
			Curboard->m_pGameBoard[GridY_3][GridX_1]->m_Type != Block::BLOCK_WATER &&
			m_XDirection == -1))
	{
		ChangeDirection();
	}
}

// 바닥 감지 함수
void Player::PlayerCheckFloor(Map* Curboard)
{
	int GridX_2 = (int)(m_PosX + (TILESIZE / 2)) / TILESIZE;
	int GridY_4 = (int)(m_PosY + 2 * TILESIZE + TILESIZE / 2) / TILESIZE;

	if (Curboard->m_pGameBoard[GridY_4][GridX_2]->m_Type != Block::BLOCK_EMPTY &&
		Curboard->m_pGameBoard[GridY_4][GridX_2]->m_Type != Block::CHAR_START_POS && 
		Curboard->m_pGameBoard[GridY_4][GridX_2]->m_Type != Block::BLOCK_WATER &&
		Curboard->m_pGameBoard[GridY_4][GridX_2]->m_Type != Block::BLOCK_UWATER &&
		Curboard->m_pGameBoard[GridY_4][GridX_2]->m_Type != Block::BLOCK_DOOR_OPEN &&
		Curboard->m_pGameBoard[GridY_4][GridX_2]->m_Type != Block::BLOCK_SPRING &&
		m_PlayerState == DOWN)
	{
		m_PlayerState = ONFLOOR;

		// 착지 사운드 재생
		m_LandingSound->soundSeek(0);
		cout << m_LandingSound->soundPlay() << endl;
		cout << "착지" << endl;

		m_Gravity = 0.0f;

		m_JumpPower = 0;

		//m_Speed = 7;

		m_PosY = (int)((m_PosY + TILESIZE / 2) / TILESIZE) * TILESIZE;

		if (m_XDirection == 1)
		{
			_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_R");
			_img->SetCurFrameX(0);
		}

		if (m_XDirection == -1)
		{
			_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_L");
			_img->SetCurFrameX(0);
		}
	}
}

// 절벽 감지 함수
void Player::PlayerCheckEmptyFloor(Map* Curboard)
{
	int GridX_2 = (int)(m_PosX + (TILESIZE / 2)) / TILESIZE;
	int GridY_4 = (int)(m_PosY + 2 * TILESIZE + TILESIZE / 2) / TILESIZE;

	if (Curboard->m_pGameBoard[GridY_4][GridX_2]->m_Type == Block::BLOCK_EMPTY ||
		 Curboard->m_pGameBoard[GridY_4][GridX_2]->m_Type == Block::BLOCK_WATER ||
		 Curboard->m_pGameBoard[GridY_4][GridX_2]->m_Type == Block::BLOCK_UWATER ||
		 Curboard->m_pGameBoard[GridY_4][GridX_2]->m_Type == Block::CHAR_START_POS)
	{
		m_PlayerState = DOWN;

		m_Gravity = 2.0;

		// 스프라이트 이미지 변경
		if (m_XDirection == 1)
		{
			_img = IMAGEMANAGER->FindImage("PLAYER_FALL_R");
			_img->SetCurFrameX(0);
		}

		if (m_XDirection == -1)
		{
			_img = IMAGEMANAGER->FindImage("PLAYER_FALL_L");
			_img->SetCurFrameX(0);
		}
	}
}

// 점프 감지 함수
void Player::PlayerCheckUpTile(Map* Curboard)
{
	int GridX_0 = (int)(m_PosX + TILESIZE / 2 - 3 * TILESIZE) / TILESIZE;				// X 좌표
	int GridX_4 = (int)(m_PosX + TILESIZE / 2 + 3 * TILESIZE) / TILESIZE;
	int GridY_0 = (int)((m_PosY + TILESIZE + TILESIZE / 2) - 3 * TILESIZE) / TILESIZE;	// Y 좌표
	

	if ((Curboard->m_pGameBoard[GridY_0][GridX_0]->m_Type != Block::BLOCK_EMPTY &&
		Curboard->m_pGameBoard[GridY_0][GridX_0]->m_Type != Block::BLOCK_DOOR_CLOSE &&
		Curboard->m_pGameBoard[GridY_0][GridX_0 + 1]->m_Type == Block::BLOCK_EMPTY &&
		Curboard->m_pGameBoard[GridY_0][GridX_0 + 2]->m_Type == Block::BLOCK_EMPTY &&
		m_XDirection == -1 && m_PlayerState == ONFLOOR) ||
		(Curboard->m_pGameBoard[GridY_0][GridX_4]->m_Type != Block::BLOCK_EMPTY &&
			Curboard->m_pGameBoard[GridY_0][GridX_4]->m_Type != Block::BLOCK_DOOR_CLOSE &&
			Curboard->m_pGameBoard[GridY_0][GridX_4 - 1]->m_Type == Block::BLOCK_EMPTY &&
			Curboard->m_pGameBoard[GridY_0][GridX_4 - 2]->m_Type == Block::BLOCK_EMPTY &&
			m_XDirection == 1 && m_PlayerState == ONFLOOR))
	{
		PlayerJump();
	}
}

// 스프링 확인 함수 
void Player::PlayerCheckSpring(Map* Curboard)	/// 추가 예정
{
	int PosGridX = (int)(m_PosX + (TILESIZE / 2)) / TILESIZE;
	int PosGridY = (int)(m_PosY + TILESIZE + TILESIZE / 2) / TILESIZE;

	if (Curboard->m_pGameBoard[PosGridY][PosGridX]->m_Type == Block::BLOCK_SPRING &&
		m_PlayerState == ONFLOOR)
	{
		SpringJump();
	}
}

// 플레이어 맵에 가두기
void Player::ConfinePlayerinMap()
{
	int PlayerPosX = m_PosX + TILESIZE / 2;				// 중심 좌표
	int PlayerPosY = m_PosY + TILESIZE + TILESIZE / 2;

	if (PlayerPosX < TILESIZE / 2)
	{
		ChangeDirection();
	}
	if (PlayerPosX > WINSIZEX - TILESIZE / 2)
	{
		ChangeDirection();
	}
	if (PlayerPosY < 0)
	{
		m_PosY = m_PosY + TILESIZE + TILESIZE / 2;
	}
	if (PlayerPosY > MAPSIZE_Y)
	{
		m_PosY = WINSIZEY;
	}
}

// 키 들고있는지 확인
void Player::PlayerCheckKey(Map* Curboard)
{
	int PlayerPosX = (int)(m_PosX + (TILESIZE / 2)) / TILESIZE;
	int PlayerPosY = (int)(m_PosY + TILESIZE + TILESIZE / 2) / TILESIZE;

	if (Curboard->m_pGameBoard[PlayerPosY][PlayerPosX]->m_Type == Block::BLOCK_KEY)
	{
		m_IsPlayerGotKey = TRUE;
      cout << "키 획득" << endl;

		Curboard->m_pGameBoard[PlayerPosY][PlayerPosX]->m_Type = Block::BLOCK_EMPTY;
	}
}

// 문을 통과하기 위한 조건 확인
void Player::PlayerCheckDoor(Map* Curboard)
{
	int GridX_3 = (int)(m_PosX + TILESIZE) / TILESIZE;				// X 좌표
	int GridX_1 = (int)((m_PosX + TILESIZE) - TILESIZE) / TILESIZE;

	int GridY_0 = (int)(m_PosY + TILESIZE + TILESIZE / 2) / TILESIZE;	// Y 좌표

	if (Curboard->m_pGameBoard[GridY_0][GridX_3]->m_Type == Block::BLOCK_DOOR_CLOSE &&
		m_IsPlayerGotKey == TRUE)
	{
		// 게임 보드의 모든 문(5)를 연다.
		for (int y = 0; y < MAPSIZE_Y; y++)
		{
			for (int x = 0; x < MAPSIZE_X; x++)
			{
				if (Curboard->m_pGameBoard[y][x]->m_Type == Block::BLOCK_DOOR_CLOSE)
				{
					Curboard->m_pGameBoard[y][x]->m_Type = Block::BLOCK_DOOR_OPEN;
					cout << "모든 문 (열림) \n\n";
				}
			}
		}		
	}

	if (Curboard->m_pGameBoard[GridY_0][GridX_1]->m_Type == Block::BLOCK_DOOR_CLOSE &&
		m_IsPlayerGotKey == TRUE)
	{
		// 게임 보드의 모든 문(5)를 연다.
		for (int y = 0; y < MAPSIZE_Y; y++)
		{
			for (int x = 0; x < MAPSIZE_X; x++)
			{
				if (Curboard->m_pGameBoard[y][x]->m_Type == Block::BLOCK_DOOR_CLOSE)
				{
					Curboard->m_pGameBoard[y][x]->m_Type = Block::BLOCK_DOOR_OPEN;
					cout << "모든 문 (열림) \n\n";
				}
			}
		}
	}
}

// 지붕 감지 함수
void Player::PlayerCheckRoof(Map* Curboard)
{
	int GridX_2 = (int)(m_PosX + TILESIZE / 2) / TILESIZE;
	int GridY_2 = (int)(m_PosY + TILESIZE / 2) / TILESIZE;

	if (Curboard->m_pGameBoard[GridY_2][GridX_2]->m_Type == Block::BLOCK_WOOD ||
		Curboard->m_pGameBoard[GridY_2][GridX_2]->m_Type == Block::BLOCK_WOOD_L||
		Curboard->m_pGameBoard[GridY_2][GridX_2]->m_Type == Block::BLOCK_WOOD_M ||
		Curboard->m_pGameBoard[GridY_2][GridX_2]->m_Type == Block::BLOCK_WOOD_R ||
		Curboard->m_pGameBoard[GridY_2][GridX_2]->m_Type == Block::BLOCK_GRASS_02 ||
		Curboard->m_pGameBoard[GridY_2][GridX_2]->m_Type == Block::BLOCK_GRASS_03 ||
		Curboard->m_pGameBoard[GridY_2][GridX_2]->m_Type == Block::BLOCK_GRASS_L ||
		Curboard->m_pGameBoard[GridY_2][GridX_2]->m_Type == Block::BLOCK_GRASS_L2 ||
		Curboard->m_pGameBoard[GridY_2][GridX_2]->m_Type == Block::BLOCK_GRASS_R ||
		Curboard->m_pGameBoard[GridY_2][GridX_2]->m_Type == Block::BLOCK_GRASS_R2)
	{
		m_PlayerState = DOWN;
		m_JumpPower = 0;
		m_PosY = m_PosY /* / TILESIZE) * TILESIZE*/;
      cout << "지붕감지" << endl;

	}
}

// 맵정보 가져오기
void Player::GetMapInfo(Map* CurBoard)
{
	m_pCurBoard = CurBoard;
}

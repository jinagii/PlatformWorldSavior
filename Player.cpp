#include "pch.h"
#include "Player.h"
//#include "AABB.h"
//#include "TestScene.h"
#include "Map.h"

Player::Player()
{
	// ���� ����
	m_JumpSound		= SOUNDMANAGER->FindSound("JUMP");
	m_SpringJumpSound	= SOUNDMANAGER->FindSound("SPRINGJUMP");
	m_LandingSound		= SOUNDMANAGER->FindSound("LAND");
	m_DyingSound			= SOUNDMANAGER->FindSound("DIE");
}

Player::~Player()
{

}

// �÷��̾� �ڵ� ������ �Լ�
void Player::PlayerAutoMove()
{
	m_PosX += m_Speed * m_XDirection;
}

// �÷��̾� �߷� �Լ�
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

// �¿� ���� ��ȯ �Լ�
void Player::ChangeDirection()
{
	m_XDirection = m_XDirection * -1;

	if (m_XDirection == 1)
	{
		_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_R");
		_img->SetCurFrameX(0);
      cout << "���� ��ȯ" << endl;
	}

	if (m_XDirection == -1)
	{
		_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_L");
		_img->SetCurFrameX(0);
      cout << "���� ��ȯ" << endl;
	}
}

// �÷��̾� ���� �Լ�
/// �м� �ʿ�
void Player::PlayerJump()
{
	m_PlayerState = UP;

	m_JumpPower = m_MaxJumpPower;

	// ��������Ʈ �̹��� ����	
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

	// ���� ���� ���
	m_JumpSound->soundSeek(0);
	cout << m_JumpSound->soundPlay() << endl;
	cout << "�븻 ����" << endl;
}

void Player::SpringJump()
{
	m_PlayerState = UP;

	m_JumpPower = m_SpringJumpPower;

	//m_Speed = 4;

	// ��������Ʈ �̹��� ����
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

	// ���� ���� ���
	m_SpringJumpSound->soundSeek(0);
	cout << m_SpringJumpSound->soundPlay() << endl;
	cout << "������ ����" << endl;
}



// �� ���� �Լ�
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

// �ٴ� ���� �Լ�
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

		// ���� ���� ���
		m_LandingSound->soundSeek(0);
		cout << m_LandingSound->soundPlay() << endl;
		cout << "����" << endl;

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

// ���� ���� �Լ�
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

		// ��������Ʈ �̹��� ����
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

// ���� ���� �Լ�
void Player::PlayerCheckUpTile(Map* Curboard)
{
	int GridX_0 = (int)(m_PosX + TILESIZE / 2 - 3 * TILESIZE) / TILESIZE;				// X ��ǥ
	int GridX_4 = (int)(m_PosX + TILESIZE / 2 + 3 * TILESIZE) / TILESIZE;
	int GridY_0 = (int)((m_PosY + TILESIZE + TILESIZE / 2) - 3 * TILESIZE) / TILESIZE;	// Y ��ǥ
	

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

// ������ Ȯ�� �Լ� 
void Player::PlayerCheckSpring(Map* Curboard)	/// �߰� ����
{
	int PosGridX = (int)(m_PosX + (TILESIZE / 2)) / TILESIZE;
	int PosGridY = (int)(m_PosY + TILESIZE + TILESIZE / 2) / TILESIZE;

	if (Curboard->m_pGameBoard[PosGridY][PosGridX]->m_Type == Block::BLOCK_SPRING &&
		m_PlayerState == ONFLOOR)
	{
		SpringJump();
	}
}

// �÷��̾� �ʿ� ���α�
void Player::ConfinePlayerinMap()
{
	int PlayerPosX = m_PosX + TILESIZE / 2;				// �߽� ��ǥ
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

// Ű ����ִ��� Ȯ��
void Player::PlayerCheckKey(Map* Curboard)
{
	int PlayerPosX = (int)(m_PosX + (TILESIZE / 2)) / TILESIZE;
	int PlayerPosY = (int)(m_PosY + TILESIZE + TILESIZE / 2) / TILESIZE;

	if (Curboard->m_pGameBoard[PlayerPosY][PlayerPosX]->m_Type == Block::BLOCK_KEY)
	{
		m_IsPlayerGotKey = TRUE;
      cout << "Ű ȹ��" << endl;

		Curboard->m_pGameBoard[PlayerPosY][PlayerPosX]->m_Type = Block::BLOCK_EMPTY;
	}
}

// ���� ����ϱ� ���� ���� Ȯ��
void Player::PlayerCheckDoor(Map* Curboard)
{
	int GridX_3 = (int)(m_PosX + TILESIZE) / TILESIZE;				// X ��ǥ
	int GridX_1 = (int)((m_PosX + TILESIZE) - TILESIZE) / TILESIZE;

	int GridY_0 = (int)(m_PosY + TILESIZE + TILESIZE / 2) / TILESIZE;	// Y ��ǥ

	if (Curboard->m_pGameBoard[GridY_0][GridX_3]->m_Type == Block::BLOCK_DOOR_CLOSE &&
		m_IsPlayerGotKey == TRUE)
	{
		// ���� ������ ��� ��(5)�� ����.
		for (int y = 0; y < MAPSIZE_Y; y++)
		{
			for (int x = 0; x < MAPSIZE_X; x++)
			{
				if (Curboard->m_pGameBoard[y][x]->m_Type == Block::BLOCK_DOOR_CLOSE)
				{
					Curboard->m_pGameBoard[y][x]->m_Type = Block::BLOCK_DOOR_OPEN;
					cout << "��� �� (����) \n\n";
				}
			}
		}		
	}

	if (Curboard->m_pGameBoard[GridY_0][GridX_1]->m_Type == Block::BLOCK_DOOR_CLOSE &&
		m_IsPlayerGotKey == TRUE)
	{
		// ���� ������ ��� ��(5)�� ����.
		for (int y = 0; y < MAPSIZE_Y; y++)
		{
			for (int x = 0; x < MAPSIZE_X; x++)
			{
				if (Curboard->m_pGameBoard[y][x]->m_Type == Block::BLOCK_DOOR_CLOSE)
				{
					Curboard->m_pGameBoard[y][x]->m_Type = Block::BLOCK_DOOR_OPEN;
					cout << "��� �� (����) \n\n";
				}
			}
		}
	}
}

// ���� ���� �Լ�
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
      cout << "���ذ���" << endl;

	}
}

// ������ ��������
void Player::GetMapInfo(Map* CurBoard)
{
	m_pCurBoard = CurBoard;
}

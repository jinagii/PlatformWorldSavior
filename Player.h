#pragma once
#include "ObjectBase.h"

// �÷��̾� ������Ʈ ����
#define UP 1
#define DOWN 2
#define ONFLOOR 3

enum class Block;
class Map;
class TestScene;

// �÷��̾� Ŭ����
class Player : public ObjectBase
{
	// Con/destructor
public:
	Player();
	~Player();

	void PlayerAutoMove();				// �÷��̾� �ڵ� ������ �Լ�
	void PlayerGravity();				// �÷��̾� �߷� �Լ�
	void ChangeDirection();				// �¿� ���� ��ȯ �Լ�
	void PlayerJump();					// �÷��̾� ���� �Լ�
	void SpringJump();					// ������ ���� 
	void PlayerCheckWall(Map* Curboard);	// �� ���� �Լ�
	void PlayerCheckFloor(Map* Curboard);	// �ٴ� ���� �Լ�
	void PlayerCheckEmptyFloor(Map* Curboard);	// ���� ���� �Լ�
	void PlayerCheckUpTile(Map* Curboard);		// ������ �� ���� �Լ�
	void PlayerCheckSpring(Map* Curboard);		// ������ �Լ�
	void ConfinePlayerinMap();					// �ʿ� ĳ���� ���δ� �Լ� 
	void PlayerCheckKey(Map* Curboard);			// Ű�� ���ϰ� �ִ°�
	void PlayerCheckDoor(Map* Curboard);		// �� ���� �Լ�
	void PlayerCheckRoof(Map* Curboard);		// ���� ���� �Լ�
	void GetMapInfo(Map* Curboard);				// �� �ҷ����� �Լ�

	//void PlayerCheckFail(Map* Curboard);		// ���� �۾�

	Map* m_pCurBoard;
	bool m_IsPlayerGotKey = FALSE;	// �÷��̾ Ű�� ��������
	int m_PlayerState = ONFLOOR;

	//bool Up;
	//bool OnFloor;

	float m_JumpPower = 0.0f;
	float m_MaxJumpPower = -38.f;
	float m_SpringJumpPower = -60.0f;

	float m_Speed = 8.0f;	// �÷��̾� �ӵ�
	int m_XDirection = 1;		// ���� ��ȯ�� ����
	float m_Gravity = 2.0f;		// �߷� ��

private:
	Sound* m_JumpSound;		// ������ �� ȿ����
	Sound* m_SpringJumpSound;	// ������ ������ �� ȿ����
	Sound* m_LandingSound;		// ���� ȿ����
	Sound* m_DyingSound;			// ���� ȿ����
	//bool _isDead;			// True -> Die / False -> Life
};
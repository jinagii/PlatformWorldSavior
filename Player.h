#pragma once
#include "ObjectBase.h"

// 플레이어 스테이트 정의
#define UP 1
#define DOWN 2
#define ONFLOOR 3

enum class Block;
class Map;
class TestScene;

// 플레이어 클래스
class Player : public ObjectBase
{
	// Con/destructor
public:
	Player();
	~Player();

	void PlayerAutoMove();				// 플레이어 자동 움직임 함수
	void PlayerGravity();				// 플레이어 중력 함수
	void ChangeDirection();				// 좌우 방향 전환 함수
	void PlayerJump();					// 플레이어 점프 함수
	void SpringJump();					// 스프링 점프 
	void PlayerCheckWall(Map* Curboard);	// 벽 감지 함수
	void PlayerCheckFloor(Map* Curboard);	// 바닥 감지 함수
	void PlayerCheckEmptyFloor(Map* Curboard);	// 절벽 감지 함수
	void PlayerCheckUpTile(Map* Curboard);		// 점프할 곳 감지 함수
	void PlayerCheckSpring(Map* Curboard);		// 스프링 함수
	void ConfinePlayerinMap();					// 맵에 캐릭터 가두는 함수 
	void PlayerCheckKey(Map* Curboard);			// 키를 지니고 있는가
	void PlayerCheckDoor(Map* Curboard);		// 문 감지 함수
	void PlayerCheckRoof(Map* Curboard);		// 지붕 감지 함수
	void GetMapInfo(Map* Curboard);				// 맵 불러오는 함수

	//void PlayerCheckFail(Map* Curboard);		// 실패 작업

	Map* m_pCurBoard;
	bool m_IsPlayerGotKey = FALSE;	// 플레이어가 키를 가졌는지
	int m_PlayerState = ONFLOOR;

	//bool Up;
	//bool OnFloor;

	float m_JumpPower = 0.0f;
	float m_MaxJumpPower = -38.f;
	float m_SpringJumpPower = -60.0f;

	float m_Speed = 8.0f;	// 플레이어 속도
	int m_XDirection = 1;		// 방향 전환용 변수
	float m_Gravity = 2.0f;		// 중력 값

private:
	Sound* m_JumpSound;		// 점프할 때 효과음
	Sound* m_SpringJumpSound;	// 스프링 점프할 때 효과음
	Sound* m_LandingSound;		// 착지 효과음
	Sound* m_DyingSound;			// 데쓰 효과음
	//bool _isDead;			// True -> Die / False -> Life
};
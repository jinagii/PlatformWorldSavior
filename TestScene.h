#pragma once
#include "GameNode.h"
//#include "Map.h"

class Player;
class ObjectBox;
class Map;

class TestScene : public GameNode
{
public:
	Image*	_bgImg;				// 백그라운드 이미지
	Image*	_grass01Img;		// 그레스 타일 1번
	Image* _key;				// 키
	Image* _doorClose;			// 열린 문
	Image* _doorOpen;			// 닫힌 문

	//Image* _player;			// 플레이어

	Map* m_pMap;

	Player* _player;

	//ObjectBox* _floor[MAPSIZE_Y][MAPSIZE_X];
	//ObjectBox* _wall;

	// map
	// 메인 게임 보드(배열을 타일단위로) -> 스크린상에서 출력될 좌표

	// 첫번째 스테이지의 블록 타입 값들 
	int m_StageOneData[MAPSIZE_Y][MAPSIZE_X] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	/// 마우스가 가리키는 특정 칸
	BoardSet* m_CurPickedGameBoard;

	/// 마우스가 들고있는 블럭타입
	Block PickedMouseBlockType;

public:
	TestScene();
	~TestScene();

	HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

public:
	// 게임보드 초기화
	void InputBoardData();

public:
	/// 디버그용 함수들
	// 그리드로 사용할 사각형 생성
	void DebugDrawGrid();

	void DebugDrawPlayerCollisionBox();

	// 현재 마우스좌표 출력
	void DebugShowMouseInfo();
	// 
	void DebugShowMouseClickState();

	// 마우스가 가리키는 현재 배열
	void CheckCurrentBoard(int x, int y);
	// 마우스를 클릭할때 블럭정보 복사/붙여넣기
	void CopyCurMouseBlockType();

	void PasteCurMouseBlockType(int x, int y);

	// 타일 렌더(렌더부분에서 사용하자)
	void RenderTile();
};
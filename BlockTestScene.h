#pragma once

#include "GameNode.h"
//#include "Map.h"

class Player;
//class ObjectBox;
class Map;

class BlockTestScene : public GameNode
{
public:
	Image* _bgImg;				// 백그라운드 이미지
	Image* _grass01Img;			// 그레스 타일 1번
	Image* _ground01Img;		// 땅속 그라운드 타일 이미지1번
	Image* _ground02Img;		// 땅속 그라운드 타일 이미지2번
	Image* _unground03Img;		// 땅속 그라운드 타일 이미지3번

	Map* m_pMap;

	Player* _player;

	//ObjectBox* _floor[MAPSIZE_Y][MAPSIZE_X];
	//ObjectBox* _wall;

	// 첫번째 스테이지의 블록 타입 값들, 캐릭터 스크린 뷰 배열
	int m_StageOneData[MAPSIZE_Y][MAPSIZE_X] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	};

	/// 마우스가 가리키는 특정 칸
	BoardSet* m_CurPickedGameBoard;

	/// 마우스가 들고있는 블럭타입
	Block PickedMouseBlockType;

public:
	BlockTestScene();
	~BlockTestScene();

	HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

public:
	// 게임보드 초기화
	void InputBoardData();

public:
	// 마우스를 클릭할때 블럭정보 복사
	void CopyCurMouseBlockType(int x, int y);

	// 마우스를 클릭할때 블럭정보 붙여넣기
	void PasteCurMouseBlockType(int x, int y);
	void PasteCurMouseMultiBlockType(int x, int y);

	// 타일 렌더(렌더부분에서 사용하자)
	void RenderTile();
};
#pragma once

enum class Block
{
	BLOCK_MOUSEEMPTY	= 99,	// 픽 마우스 초기값
		
	CHAR_START_POS		= -1,	// 캐릭터의 시작 위치를 정할 위치

	BLOCK_EMPTY			= 0,	// 비어 있는 칸
	BLOCK_BASIC			= 1,	// 맵에 기본으로 있는 블럭

	BLOCK_UNDERGROUND02 = 2,	// 
	BLOCK_UNDERGROUND03 = 3,

	BLOCK_KEY			= 4,	// 키와 문
	BLOCK_DOOR_CLOSE	= 5,	// 닫힌 문
	BLOCK_DOOR_OPEN	= 6,	// 열린 문
	BLOCK_ROCK			= 7,	// 일반 블록(벽돌)
	BLOCK_LONG_ROCK	= 8,	// 5칸 블록(벽돌)

	BLOCK_SPRING		= 9,	// 스프링 점프대
								
	BLOCK_WOOD			= 10,	// 1칸 통나무
	BLOCK_WOOD_LONG	= 11,	// 현재 사용하지 않는다
								
	BLOCK_FRUIT			= 12,	// 골인 지점(열매)
	
	BLOCK_WATER			= 13,
	BLOCK_UWATER		= 14,

	BLOCK_GRASS_02		= 15,
	BLOCK_GRASS_03		= 16,

	BLOCK_GRASS_L		= 17,
	BLOCK_GRASS_L2		= 18,
	BLOCK_GRASS_R		= 19,
	BLOCK_GRASS_R2		= 20,
	
	/////////////////////////////////////////////////

	BLOCK_WOOD_L		= 21,
	BLOCK_WOOD_M		= 22,
	BLOCK_WOOD_R		= 23,
	

	// 장식 풀, 돌
	BLOCK_ROCK_01		=24,
	BLOCK_ROCK_02		=25,
	BLOCK_BUSH_01		=26,
	BLOCK_BUSH_02		=27
};

class BoardSet
{
public:
	BoardSet(Block type, int x, int y);
	~BoardSet();

	Block m_Type;
	RECT m_Box;
};

/// 2020.11.21. JinHak
/// 게임 맵 클래스
class Map
{
public:
	static const int m_MapSizeX = 50;
	static const int m_MapSizeY = 50;
	static const int m_BlockSize = 70;

	// 메인 게임 보드(배열을 타일단위로) -> 스크린상에서 출력될 좌표
	BoardSet* m_pGameBoard[m_MapSizeY][m_MapSizeX];

	// 마우스가 들고있는 블럭타입
	Block PickedMouseBlockType;

	/// 정보를 넣어야 함.
	void SetType(int x, int y, Block type);

	/// 정보를 꺼내야 함.
	Block GetType(int x, int y);
	RECT GetBox(int x, int y);

	BoardSet* GetBoardSet(int x, int y);

	/// 맵을 초기화.
	void Initialize();

	/// 디버그용 함수들
	// 그리드 그리기
	void DrawGrid();

	// 현재 마우스 정보 출력
	void ShowMouseInfo();

	// 마우스가 클릭한 현재 배열체크
	Block CheckCurrentBoard(int x, int y);
};
#pragma once

enum class Block
{
	BLOCK_MOUSEEMPTY	= 99,	// �� ���콺 �ʱⰪ
		
	CHAR_START_POS		= -1,	// ĳ������ ���� ��ġ�� ���� ��ġ

	BLOCK_EMPTY			= 0,	// ��� �ִ� ĭ
	BLOCK_BASIC			= 1,	// �ʿ� �⺻���� �ִ� ��

	BLOCK_UNDERGROUND02 = 2,	// 
	BLOCK_UNDERGROUND03 = 3,

	BLOCK_KEY			= 4,	// Ű�� ��
	BLOCK_DOOR_CLOSE	= 5,	// ���� ��
	BLOCK_DOOR_OPEN	= 6,	// ���� ��
	BLOCK_ROCK			= 7,	// �Ϲ� ���(����)
	BLOCK_LONG_ROCK	= 8,	// 5ĭ ���(����)

	BLOCK_SPRING		= 9,	// ������ ������
								
	BLOCK_WOOD			= 10,	// 1ĭ �볪��
	BLOCK_WOOD_LONG	= 11,	// ���� ������� �ʴ´�
								
	BLOCK_FRUIT			= 12,	// ���� ����(����)
	
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
	

	// ��� Ǯ, ��
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
/// ���� �� Ŭ����
class Map
{
public:
	static const int m_MapSizeX = 50;
	static const int m_MapSizeY = 50;
	static const int m_BlockSize = 70;

	// ���� ���� ����(�迭�� Ÿ�ϴ�����) -> ��ũ���󿡼� ��µ� ��ǥ
	BoardSet* m_pGameBoard[m_MapSizeY][m_MapSizeX];

	// ���콺�� ����ִ� ��Ÿ��
	Block PickedMouseBlockType;

	/// ������ �־�� ��.
	void SetType(int x, int y, Block type);

	/// ������ ������ ��.
	Block GetType(int x, int y);
	RECT GetBox(int x, int y);

	BoardSet* GetBoardSet(int x, int y);

	/// ���� �ʱ�ȭ.
	void Initialize();

	/// ����׿� �Լ���
	// �׸��� �׸���
	void DrawGrid();

	// ���� ���콺 ���� ���
	void ShowMouseInfo();

	// ���콺�� Ŭ���� ���� �迭üũ
	Block CheckCurrentBoard(int x, int y);
};
#include "pch.h"
#include "Map.h"

BoardSet::BoardSet(Block type, int x, int y)
{

}

BoardSet::~BoardSet()
{

}

void Map::SetType(int x, int y, Block type)
{
	m_pGameBoard[y][x]->m_Type = type;
}

Block Map::GetType(int x, int y)
{
	return m_pGameBoard[y][x]->m_Type;
}

RECT Map::GetBox(int x, int y)
{
	return m_pGameBoard[y][x]->m_Box;
}

BoardSet* Map::GetBoardSet(int x, int y)
{
	return m_pGameBoard[y][x];
}

void Map::Initialize()
{
	for (int y = 0; y < m_MapSizeY; y++)
	{
		for (int x = 0; x < m_MapSizeX; x++)
		{
			m_pGameBoard[y][x] = new BoardSet(Block::BLOCK_EMPTY, x, y);
			m_pGameBoard[y][x]->m_Box.left = x * Map::m_BlockSize;
			m_pGameBoard[y][x]->m_Box.top = y * Map::m_BlockSize;
			m_pGameBoard[y][x]->m_Box.right = (x * Map::m_BlockSize) + Map::m_BlockSize;
			m_pGameBoard[y][x]->m_Box.bottom = (y * Map::m_BlockSize) + Map::m_BlockSize;
		}
	}
}


void Map::DrawGrid()
{
	for (int y = 0; y < MAPSIZE_Y; y++)
	{
		DrawLine(g_backBuffer->GetMemDC(), 0, y * TILESIZE,
			2800, y * TILESIZE, RGB(0, 255, 0));
	}

	for (int x = 0; x < MAPSIZE_X; x++)
	{
		DrawLine(g_backBuffer->GetMemDC(), x * TILESIZE, 0,
			x * TILESIZE, 2100, RGB(0, 255, 0));
	}
}

void Map::ShowMouseInfo()
{
	// ���� ���콺 ��ǥ
	TCHAR curmousePos[100];
	wsprintf(curmousePos, TEXT("���콺 X ��ǥ = %d, ���콺 Y ��ǥ = %d"), g_ptMouse.x, g_ptMouse.y);
	TextOut(g_backBuffer->GetMemDC(), 10, 30, curmousePos, lstrlen(curmousePos));

	// ���� ���콺�� Ŭ���� �迭 Ÿ�� ��
	TCHAR pickedmouseBlocktype[100];
	wsprintf(pickedmouseBlocktype, TEXT("���콺 Picked Block_Type = %d"), PickedMouseBlockType);
	TextOut(g_backBuffer->GetMemDC(), 10, 50, pickedmouseBlocktype, lstrlen(pickedmouseBlocktype));

	cout << "[���콺 ��Ŭ��] \n";
	cout << "g_ptMouse.x = " << g_ptMouse.x << "\n";
	cout << "g_ptMouse.y = " << g_ptMouse.y << "\n";
	cout << "���� ���� xĭ = " << g_ptMouse.x / TILESIZE << "\n";
	cout << "���� ���� yĭ = " << g_ptMouse.y / TILESIZE << "\n\n";

	cout << "PickedMouseBlockType = " << (int)PickedMouseBlockType << "\n\n";

	// ���� ���� ������ ���
	cout << "[���� m_FirstGameBoard] \n";
	for (int y = 0; y < MAPSIZE_Y; y++)
	{
		for (int x = 0; x < MAPSIZE_X; x++)
		{
			cout << (int)GetType(x, y) << " ";
		}
		cout << "\n\n";
	}
}

Block Map::CheckCurrentBoard(int x, int y)
{
	int CurMouseX = g_ptMouse.x / TILESIZE;
	int CurMouseY = g_ptMouse.y / TILESIZE;

	return GetBoardSet(CurMouseX, CurMouseY)->m_Type;
}
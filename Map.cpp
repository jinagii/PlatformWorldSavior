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
	// 현재 마우스 좌표
	TCHAR curmousePos[100];
	wsprintf(curmousePos, TEXT("마우스 X 좌표 = %d, 마우스 Y 좌표 = %d"), g_ptMouse.x, g_ptMouse.y);
	TextOut(g_backBuffer->GetMemDC(), 10, 30, curmousePos, lstrlen(curmousePos));

	// 현재 마우스가 클릭한 배열 타입 값
	TCHAR pickedmouseBlocktype[100];
	wsprintf(pickedmouseBlocktype, TEXT("마우스 Picked Block_Type = %d"), PickedMouseBlockType);
	TextOut(g_backBuffer->GetMemDC(), 10, 50, pickedmouseBlocktype, lstrlen(pickedmouseBlocktype));

	cout << "[마우스 왼클릭] \n";
	cout << "g_ptMouse.x = " << g_ptMouse.x << "\n";
	cout << "g_ptMouse.y = " << g_ptMouse.y << "\n";
	cout << "현재 선택 x칸 = " << g_ptMouse.x / TILESIZE << "\n";
	cout << "현재 선택 y칸 = " << g_ptMouse.y / TILESIZE << "\n\n";

	cout << "PickedMouseBlockType = " << (int)PickedMouseBlockType << "\n\n";

	// 보드 내용 디버깅용 출력
	cout << "[현재 m_FirstGameBoard] \n";
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
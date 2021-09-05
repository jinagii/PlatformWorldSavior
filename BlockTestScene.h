#pragma once

#include "GameNode.h"
//#include "Map.h"

class Player;
//class ObjectBox;
class Map;

class BlockTestScene : public GameNode
{
public:
	Image* _bgImg;				// ��׶��� �̹���
	Image* _grass01Img;			// �׷��� Ÿ�� 1��
	Image* _ground01Img;		// ���� �׶��� Ÿ�� �̹���1��
	Image* _ground02Img;		// ���� �׶��� Ÿ�� �̹���2��
	Image* _unground03Img;		// ���� �׶��� Ÿ�� �̹���3��

	Map* m_pMap;

	Player* _player;

	//ObjectBox* _floor[MAPSIZE_Y][MAPSIZE_X];
	//ObjectBox* _wall;

	// ù��° ���������� ��� Ÿ�� ����, ĳ���� ��ũ�� �� �迭
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

	/// ���콺�� ����Ű�� Ư�� ĭ
	BoardSet* m_CurPickedGameBoard;

	/// ���콺�� ����ִ� ��Ÿ��
	Block PickedMouseBlockType;

public:
	BlockTestScene();
	~BlockTestScene();

	HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

public:
	// ���Ӻ��� �ʱ�ȭ
	void InputBoardData();

public:
	// ���콺�� Ŭ���Ҷ� ������ ����
	void CopyCurMouseBlockType(int x, int y);

	// ���콺�� Ŭ���Ҷ� ������ �ٿ��ֱ�
	void PasteCurMouseBlockType(int x, int y);
	void PasteCurMouseMultiBlockType(int x, int y);

	// Ÿ�� ����(�����κп��� �������)
	void RenderTile();
};
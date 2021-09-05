#pragma once
#include "GameNode.h"
//#include "Map.h"

class Player;
class ObjectBox;
class Map;

class TestScene : public GameNode
{
public:
	Image*	_bgImg;				// ��׶��� �̹���
	Image*	_grass01Img;		// �׷��� Ÿ�� 1��
	Image* _key;				// Ű
	Image* _doorClose;			// ���� ��
	Image* _doorOpen;			// ���� ��

	//Image* _player;			// �÷��̾�

	Map* m_pMap;

	Player* _player;

	//ObjectBox* _floor[MAPSIZE_Y][MAPSIZE_X];
	//ObjectBox* _wall;

	// map
	// ���� ���� ����(�迭�� Ÿ�ϴ�����) -> ��ũ���󿡼� ��µ� ��ǥ

	// ù��° ���������� ��� Ÿ�� ���� 
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

	/// ���콺�� ����Ű�� Ư�� ĭ
	BoardSet* m_CurPickedGameBoard;

	/// ���콺�� ����ִ� ��Ÿ��
	Block PickedMouseBlockType;

public:
	TestScene();
	~TestScene();

	HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

public:
	// ���Ӻ��� �ʱ�ȭ
	void InputBoardData();

public:
	/// ����׿� �Լ���
	// �׸���� ����� �簢�� ����
	void DebugDrawGrid();

	void DebugDrawPlayerCollisionBox();

	// ���� ���콺��ǥ ���
	void DebugShowMouseInfo();
	// 
	void DebugShowMouseClickState();

	// ���콺�� ����Ű�� ���� �迭
	void CheckCurrentBoard(int x, int y);
	// ���콺�� Ŭ���Ҷ� ������ ����/�ٿ��ֱ�
	void CopyCurMouseBlockType();

	void PasteCurMouseBlockType(int x, int y);

	// Ÿ�� ����(�����κп��� �������)
	void RenderTile();
};
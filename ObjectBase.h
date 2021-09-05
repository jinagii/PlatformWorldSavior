#pragma once

#include "AABB.h"

/// ���� ���� ��� ������Ʈ�� �θ�
class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

public:
	
	Image* _img;	// �̹���
	
	// ��ġ
	float m_PosX;
	float m_PosY;
	
	// ���� ���̴� ��ǥ (�� �̸� ������ �θ� �۵��� ������...?)
	//int PlayerPosX = (int)(m_PosX + BLOCKSIZE / 2);
	//int PlayerPosY = (int)(m_PosY + BLOCKSIZE + BLOCKSIZE / 2);


	/// �浿 ���� ���
	// �浹 ���� ��

	bool m_IsCollided;
	bool m_IsCollidedX;
	bool m_IsCollidedY;

	RECT m_BoundingBox;

public:
	// �ʱ�ȭ
	void Initialize(int size, int x, int y);
	void RectInitialize(int x1, int y1, int x2, int y2);

	RECT GetWorldAABB();

	void IsCollided(bool val) { m_IsCollided = val; }
	void IsCollidedX(bool val); //{ m_IsCollidedX = val; }
	void IsCollidedY(bool val); //{ m_IsCollidedY = val; }

	// ���������� ó���ؾ� �� ��

private:
	//void LoadBitmap();
	//void ResetPath();


public:
	void DrawBoundingVolume();


};


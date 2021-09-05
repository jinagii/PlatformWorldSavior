#pragma once

#include "AABB.h"

/// 게임 내의 모든 오브젝트의 부모
class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

public:
	
	Image* _img;	// 이미지
	
	// 위치
	float m_PosX;
	float m_PosY;
	
	// 실제 보이는 좌표 (왜 미리 선언해 두면 작동을 안하지...?)
	//int PlayerPosX = (int)(m_PosX + BLOCKSIZE / 2);
	//int PlayerPosY = (int)(m_PosY + BLOCKSIZE + BLOCKSIZE / 2);


	/// 충동 감지 기능
	// 충돌 영역 등

	bool m_IsCollided;
	bool m_IsCollidedX;
	bool m_IsCollidedY;

	RECT m_BoundingBox;

public:
	// 초기화
	void Initialize(int size, int x, int y);
	void RectInitialize(int x1, int y1, int x2, int y2);

	RECT GetWorldAABB();

	void IsCollided(bool val) { m_IsCollided = val; }
	void IsCollidedX(bool val); //{ m_IsCollidedX = val; }
	void IsCollidedY(bool val); //{ m_IsCollidedY = val; }

	// 내부적으로 처리해야 할 것

private:
	//void LoadBitmap();
	//void ResetPath();


public:
	void DrawBoundingVolume();


};


#pragma once


// 4개의 꼭짓점(사각형이라)
// 4개의 점의 정보가 필요하나 2개로 충분 
//RECT BoundingVolume;

//int m_CenterPosX;	// 원의 중점
//int m_CenterPosy;
//
//int m_Width;		// 폭
//int m_Height;		// 높이


/// Collision Check Function (AABB)
bool CheckCollision_AABB(RECT source, RECT target);
bool CheckCollision_AABB_X(RECT source, RECT target);
bool CheckCollision_AABB_Y(RECT source, RECT target);
bool Check_Same_Y_axis(RECT source, RECT target);

//void Wall(Player* _player, ObjectBox* _box);
//void 
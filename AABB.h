#pragma once


// 4���� ������(�簢���̶�)
// 4���� ���� ������ �ʿ��ϳ� 2���� ��� 
//RECT BoundingVolume;

//int m_CenterPosX;	// ���� ����
//int m_CenterPosy;
//
//int m_Width;		// ��
//int m_Height;		// ����


/// Collision Check Function (AABB)
bool CheckCollision_AABB(RECT source, RECT target);
bool CheckCollision_AABB_X(RECT source, RECT target);
bool CheckCollision_AABB_Y(RECT source, RECT target);
bool Check_Same_Y_axis(RECT source, RECT target);

//void Wall(Player* _player, ObjectBox* _box);
//void 
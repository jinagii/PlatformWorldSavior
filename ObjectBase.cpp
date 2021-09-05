#include "pch.h"
#include "AABB.h"
#include "ObjectBase.h"

ObjectBase::ObjectBase()
	: m_IsCollidedX(false), m_IsCollidedY(false)
{

}

ObjectBase::~ObjectBase()
{

}

// ���簢�� �ʱ�ȭ
void ObjectBase::Initialize(int size, int x, int y)
{
	// ��Ʈ�� �Ǵ� ���� ���ؼ� �ٿ�� �ڽ��� �Է¹޾ƾ���
	m_PosX = x;
	m_PosY = y;

	m_BoundingBox.left = 0;
	m_BoundingBox.top = 0;
	m_BoundingBox.right = size;
	m_BoundingBox.bottom = size;

	

	
}

// ���簢�� �ʱ�ȭ
void ObjectBase::RectInitialize(int x1, int y1, int x2, int y2)
{
	m_BoundingBox.left = x1;
	m_BoundingBox.top = y1;
	m_BoundingBox.right = x2;
	m_BoundingBox.bottom = y2;
}

// ���� ��ǥ�迴�� AABB ���� ���� ��ǥ��� �ٲ㼭 ����
RECT ObjectBase::GetWorldAABB()
{
	RECT _worldAABB;

	_worldAABB.left = m_BoundingBox.left + m_PosX;
	_worldAABB.right = m_BoundingBox.right + m_PosX;
	_worldAABB.top = m_BoundingBox.top + m_PosY;
	_worldAABB.bottom = m_BoundingBox.bottom + m_PosY;

	return _worldAABB;
}

void ObjectBase::IsCollidedX(bool val)
{
	m_IsCollidedX = val;
}


void ObjectBase::IsCollidedY(bool val)
{
	m_IsCollidedY = val;
}

// �ڽ��� �׵θ��� �׸�
void ObjectBase::DrawBoundingVolume()
{
	DrawLineToRectangle(g_backBuffer->GetMemDC(), m_PosX, m_PosY,
		m_PosX + TILESIZE, m_PosY + TILESIZE);

// 	DrawRectAsCenterPoint(g_backBuffer->GetMemDC(), m_PosX, m_PosY,
// 		m_BoundingBox.right - m_BoundingBox.left, m_BoundingBox.bottom - m_BoundingBox.top);
}
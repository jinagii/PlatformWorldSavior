#pragma once

/// Draw ���
/// 
/// �Ϲ����� ����(��, �簢��, ��) ���� �׸��� ����
/// 
/// 2020.11.16

//==============================================================================
/// �� �׸���
// [x1,y1] ~ [x2,y2] �� ���� �ߴ´�
void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);

/// �簢�� �׸���
// [left,top] ~ [right,bottom] ���� �簢�� �׸���
void DrawRect(HDC hdc, int left, int top, int right, int bottom);

// �簢�� �׸��� ���� 02
void DrawLineToRectangle(HDC hdc, int left, int top, int right, int bottom);

// ����׿� �� ����
void DrawRectangleForDebug(HDC hdc, int left, int top, int right, int bottom, COLORREF color);

RECT MakeRect(int left, int top, int right, int bottom);


// [x,y]�� �������� �ϴ� ���� ���� ���̸�ŭ �簢���� �׸���.
void DrawRectAsCenterPoint(HDC hdc, int x, int y, int width, int height);

/// Ÿ��
// [left,top] ~ [right, bottom] ���� Ÿ���� �׸�
void DrawEllipse(HDC hdc, int left, int top, int right, int bottom);

// [x,y]�� �������� �ϴ� ���� ���� ���̸�ŭ Ÿ���� �׸�
void DrawEllipseAsCenterPoint(HDC hdc, int x, int y, int width, int height);

/// ��
// [x,y]�� �������� �������� �̿��� ���� �׸�
void DrawCircle(HDC hdc, int x, int y, int radius);

//==============================================================================
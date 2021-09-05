#include "pch.h"
#include "DrawFunction.h"

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
	HPEN _newHpen;
	HPEN _oldHpen;

	// 디버그용 그리드 선 초록색으로 설정 
	_newHpen = CreatePen(PS_SOLID, 1, color);
	_oldHpen = (HPEN)::SelectObject(g_backBuffer->GetMemDC(), (HGDIOBJ)_newHpen);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	_newHpen = (HPEN)::SelectObject(g_backBuffer->GetMemDC(), _oldHpen);
	DeleteObject(_newHpen);
}

void DrawRect(HDC hdc, int left, int top, int right, int bottom)
{
	Rectangle(hdc, left, top, right, bottom);
}

void DrawRectAsCenterPoint(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc,
		x - (width / 2),
		y - (height / 2),
		x + (width / 2),
		y + (height / 2)
	);
}

void DrawEllipse(HDC hdc, int left, int top, int right, int bottom)
{
	Ellipse(hdc, left, top, right, bottom);
}

void DrawEllipseAsCenterPoint(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc,
		x - (width / 2),
		y - (height / 2),
		x + (width / 2),
		y + (height / 2)
	);
}

void DrawCircle(HDC hdc, int x, int y, int radius)
{
	Ellipse(hdc,
		x - radius,
		y - radius,
		x + radius,
		y + radius
	);
}

void DrawLineToRectangle(HDC hdc, int left, int top, int right, int bottom)
{
	HPEN newHpen;
	HPEN oldHpen;
	COLORREF green = RGB(0, 255, 0);

	// 디버그용 그리드 선 초록색으로 설정 
	newHpen = CreatePen(PS_SOLID, 2, green);
	oldHpen = (HPEN)::SelectObject(g_backBuffer->GetMemDC(), (HGDIOBJ)newHpen);

	DrawLine(g_backBuffer->GetMemDC(), left, top, right, top, green);
	DrawLine(g_backBuffer->GetMemDC(), right, top, right, bottom, green);
	DrawLine(g_backBuffer->GetMemDC(), right, bottom, left, bottom, green);
	DrawLine(g_backBuffer->GetMemDC(), left, bottom, left, top, green);

	newHpen = (HPEN)::SelectObject(g_backBuffer->GetMemDC(), oldHpen);
	DeleteObject(newHpen);
}

void DrawRectangleForDebug(HDC hdc, int left, int top, int right, int bottom, COLORREF color)
{
	HPEN newHpen;
	HPEN oldHpen;

	newHpen = CreatePen(PS_SOLID, 2, color);
	oldHpen = (HPEN)::SelectObject(g_backBuffer->GetMemDC(), (HGDIOBJ)newHpen);

	DrawLine(g_backBuffer->GetMemDC(), left, top, right, top, color);
	DrawLine(g_backBuffer->GetMemDC(), right, top, right, bottom, color);
	DrawLine(g_backBuffer->GetMemDC(), right, bottom, left, bottom, color);
	DrawLine(g_backBuffer->GetMemDC(), left, bottom, left, top, color);

	newHpen = (HPEN)::SelectObject(g_backBuffer->GetMemDC(), oldHpen);
	DeleteObject(newHpen);
}

RECT MakeRect(int left, int top, int right, int bottom)
{
	RECT rc = { left, top, right, bottom };

	return rc;
}

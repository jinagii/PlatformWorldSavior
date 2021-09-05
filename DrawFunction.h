#pragma once

/// Draw 헤더
/// 
/// 일반적인 도형(선, 사각형, 원) 등을 그리는 도구
/// 
/// 2020.11.16

//==============================================================================
/// 선 그리기
// [x1,y1] ~ [x2,y2] 로 선을 긋는다
void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);

/// 사각형 그리기
// [left,top] ~ [right,bottom] 까지 사각형 그리기
void DrawRect(HDC hdc, int left, int top, int right, int bottom);

// 사각형 그리기 버전 02
void DrawLineToRectangle(HDC hdc, int left, int top, int right, int bottom);

// 디버그용 색 지정
void DrawRectangleForDebug(HDC hdc, int left, int top, int right, int bottom, COLORREF color);

RECT MakeRect(int left, int top, int right, int bottom);


// [x,y]를 중점으로 하는 가로 세로 길이만큼 사각형을 그린다.
void DrawRectAsCenterPoint(HDC hdc, int x, int y, int width, int height);

/// 타원
// [left,top] ~ [right, bottom] 까지 타원을 그림
void DrawEllipse(HDC hdc, int left, int top, int right, int bottom);

// [x,y]를 중점으로 하는 가로 세로 길이만큼 타원을 그림
void DrawEllipseAsCenterPoint(HDC hdc, int x, int y, int width, int height);

/// 원
// [x,y]를 중점으로 반지름을 이용해 원을 그림
void DrawCircle(HDC hdc, int x, int y, int radius);

//==============================================================================
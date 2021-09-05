// PlatformerGuardians.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "MainGame.h"
#include "resource.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


//////////////////////////////////////////

// 전역 변수:
HINSTANCE   g_hInstance;        // 현재 인스턴스입니다.
HWND		g_hWnd;			    // 메인에서 받아올 윈도우의 핸들

BOOL        g_debugMode;		// 디버깅 모드 판별
POINT       g_ptMouse;		    // 마우스 좌표

MainGame    g_mg;               // 메인 게임
Image* g_backBuffer;       // 백버퍼

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"Platform World Savior";
    wcex.hIconSm = NULL;

    RegisterClassExW(&wcex);

    g_hWnd = CreateWindowW(wcex.lpszClassName, L"Platform World Savior", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        550, 50, WINSIZEX, WINSIZEY, nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd)
    {
        return FALSE;
    }

    /// 백버퍼 설정
    g_backBuffer = IMAGEMANAGER->AddImage("g_backBuffer", BACKDCSIZEX, BACKDCSIZEY);

    /// 메인게임 Init()
    g_mg.Init();

    ////////////////////////////////////////////////////////

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    MSG msg;        // 메시지 구조체

    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
            {
                break;
            }
        }

        /// 여기가 게임 루프
        else
        {
            // 프레임 체크
            if (TIMEMANAGER->FPSCheck() == false)
            {
                continue;
            }

            /// 메모리 누수 체크 할 때만 사용하자.(프레임 드랍 심함)
            //_CrtDumpMemoryLeaks();

            g_mg.Update();  // 메인게임 업데이트
            g_mg.Render();  // 메인게임 렌더

            //cout << setw(30) << "Get Elasped Time Sec = " << TIMEMANAGER->GetElaspedTimeSec() << "\n";
            //cout << setw(30) << "Get Target Elasped Time Sec = " << TIMEMANAGER->GetTargetElaspedTimeSec() << "\n\n";

        }
    }

    // 게임 끝난 후 릴리즈
    g_mg.Release();

    return (int)msg.wParam;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return g_mg.MainProc(hWnd, message, wParam, lParam);
}
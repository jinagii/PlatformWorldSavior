// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

/// 콘솔창 띄우기
//// 유니 코드 환경일 경우
#ifdef UNICODE	 
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

// 멀티바이트 환경일 경우
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include "targetver.h"

// 사운드
#pragma comment(lib,"winmm")

// Name Space


// Windows 헤더 파일
#include <Windows.h>


// C런타임 헤더 파일
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <Digitalv.h>
#include "Sound.h"

/////////////////////////////////////////////
// STL
#include <vector>
#include <map>


/////////////////////////////////////////////
// Draw 
#include "DrawFunction.h"



// Manager
#include "TimeManager.h"	
#include "ImageManager.h"	
#include "SceneManager.h"	
#include "KeyManager.h"	
#include "SoundManager.h"

// Map
#include "Map.h"

// Define
#define WINSIZEX	1416	// 화면에 보여질 스크린용 윈도우 사이즈 
#define WINSIZEY	1159
#define BACKDCSIZEX 2800	// 백버퍼용 사이즈
#define BACKDCSIZEY 2100




#define FLOOR_COMPENSATION 70	// 플레이어 바닥 위치 보정
#define MAPSIZE_X 70			// 맵 2차원 배열 X 
#define MAPSIZE_Y 32			// 맵 2차원 배열 Y

#define WORLDMAPSIZE_X 80		// 전체맵 2차원 배열 X
#define WORLDMAPSIZE_Y 80		// 전체맵 2차원 배열 Y

#define TILESIZE  70			// 타일 사이즈	

#define MOUSE_EMPTY 99			// 마우스 초기값


//Manager
#define TIMEMANAGER		TimeManager::GetSingleton()
#define IMAGEMANAGER	ImageManager::GetSingleton()
#define SCENEMANAGER	SceneManager::GetSingleton()
#define KEYMANAGER		KeyManager::GetSingleton()
#define SOUNDMANAGER	SoundManager::GetSingleton()


// 디폴트 경로 지정
#define RESOURCES_PATH "_Resources/"
#define IMAGE_PATH "_Resources/_Images/"
#define SOUND_PATH "_Resources/_Sounds/"


// 안전한 메모리 관리
#define SAFE_DELETE(p)		{ if(p) { delete p;			(p) = NULL; }}
#define SAFE_RELEASE(p)		{ if(p) { (p)->Release();	(p) = NULL; }}
#define SAFE_DELETE_ARRAY	{ if(p) { delete[](p);		(p) = NULL; }}


// 전역변수 사용
extern HINSTANCE	g_hInstance;		// 프로그램 인스턴스
extern HWND			g_hWnd;				// 윈도우 핸들
extern BOOL			g_debugMode;		// 디버그 모드 판별

extern POINT		g_ptMouse;

extern Image*		g_backBuffer;

extern int			g_stageNum;
extern int			g_clearLevel;
extern bool			g_editModeCameraReset;
extern int			g_introversion;
#endif //PCH_H

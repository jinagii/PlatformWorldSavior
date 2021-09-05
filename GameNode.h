#pragma once
#include "Image.h"

/// <summary>
/// 씬 상태 체크 enum 상수
/// </summary>
enum class Game_State
{
	Play = 0,	// 플레이 중 상태
	Edit,		// 맵 편집 상태
	Stop		// 중지 상태(플레이어의 상태에 따라 Clear or Dead)
};

class GameNode
{
protected:
	HDC  _hdc;					// 메인(스크린) DC
	bool _managerInit;			// 매니져 초기화 판별

	Game_State _gameState;		// 게임 스테이트

	// 리소스 로드용 패스(경로)변수
	string _path;

public:
	GameNode();
	virtual ~GameNode();

	virtual HRESULT Init(void);					//초기화 함수
	virtual HRESULT Init(bool managerInit);		//초기화 함수
	virtual void	Release(void);				//메모리 관련 해제
	virtual void	Update(void);				//업데이트(연산)
	virtual void	Render(void);				//그려주는 함수
	
	// 화면(스크린) 메인 DC 얻기
	HDC GetMainDC() { return _hdc; }			

	// 메시지 프로시져
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	const char* ConvertPath(string path, int type = 0);
};
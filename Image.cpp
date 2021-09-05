#include "pch.h"
#include "Image.h"

Image::Image()
	: _imageInfo(nullptr)
	, _filePath(nullptr)
	, _trans(false)
	, _transColor(RGB(0, 0, 0))
	, _animTimeCount(0.0f)
	, _animTimeRate(1.0 / 8.0)
{
}

Image::~Image()
{
}

// 빈 비트맵 이미지 초기화
HRESULT Image::Init(int width, int height)
{
	// 이미지 정보가 뭔가 있다면 해제한다
	if (_imageInfo) Release();


	// 전역 윈도우 핸들로 사용할 DC를 가져온다.
	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new ImageInfo();
	_imageInfo->_hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->_hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);	// 빈 비트맵 이미지 생성 후 핸들 연결
	_imageInfo->_hOldBitmap = (HBITMAP)SelectObject(_imageInfo->_hMemDC, _imageInfo->_hBitmap);
	_imageInfo->_width = width;	// 비트맵 가로 크기 세팅
	_imageInfo->_height = height;	// 비트맵 세로 크기 세팅

	_filePath = nullptr;
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	// 비트맵 생성 실패했다면
	if (!_imageInfo->_hBitmap)
	{
		Release();

		return E_FAIL;	// 실패했다고 알림
	}

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char* filePath, int width, int height, BOOL trans, COLORREF transColor)
{
	// 이미지 정보가 뭔가 있다면 해제한다.
	if (_imageInfo)
	{
		Release();
	}


	/// const char* 파일경로를 LPCWSTR로 변환하는 과정	
	int nLen = static_cast<int>(strlen(filePath) + 1);	// char 경로 길이
	wchar_t str[200] = L"";								// 임시 변수

	size_t cn;

	/// <summary>
	/// 멀티바이트 문자의 시퀀스를 와이드 문자의 시퀀스로 변환
	/// </summary>
	/// <param name="pcon">변환한 개수를 담을 메모리 주소</param>
	/// <param name="pwcs">변환한 유니코드 문자열을 저장할 버퍼</param>
	/// <param name="sizet">버퍼 크기</param>
	/// <param name="trans">문자열</param>
	/// <param name="transColor">변환할 최대 개수</param>
	/// <returns></returns>
	mbstowcs_s(&cn, str, 100, filePath, nLen);

	LPCWSTR convertedPath = str;					// LPCWSTR에 wc를 대입

	// 전역 윈도우 핸들로 사용할 DC를 가져온다.
	HDC hdc = GetDC(g_hWnd);
	_imageInfo = new ImageInfo;
	_imageInfo->_hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->_hBitmap = (HBITMAP)LoadImage(g_hInstance, convertedPath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->_hOldBitmap = (HBITMAP)SelectObject(_imageInfo->_hMemDC, _imageInfo->_hBitmap);
	_imageInfo->_width = width;
	_imageInfo->_height = height;

	// 파일 길이를 얻는다.
	int len = lstrlen(convertedPath);

	_filePath = new CHAR[len + 1];
	strcpy_s(_filePath, len + 1, filePath);

	/////////////////////////////////////////////////////////////////////

	_trans = trans;
	_transColor = transColor;

	// 비트맵이 생성되지 않았으면
	if (!_imageInfo->_hBitmap)
	{
		// 메모리 해제시키고
		Release();

		// 실패했다고 알림
		return E_FAIL;
	}

	// 가져온 DC를 해제
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char* filePath, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) Release();


	/// const char* 파일경로를 LPCWSTR로 변환하는 과정	
	int nLen = static_cast<int>(strlen(filePath) + 1);	// char 경로 길이
	wchar_t str[200] = L"";								// 임시 변수

	size_t cn;

	/// <summary>
	/// 멀티바이트 문자의 시퀀스를 와이드 문자의 시퀀스로 변환
	/// </summary>
	/// <param name="pcon">변환한 개수를 담을 메모리 주소</param>
	/// <param name="pwcs">변환한 유니코드 문자열을 저장할 버퍼</param>
	/// <param name="sizet">버퍼 크기</param>
	/// <param name="trans">문자열</param>
	/// <param name="transColor">변환할 최대 개수</param>
	/// <returns></returns>
	mbstowcs_s(&cn, str, 100, filePath, nLen);


	LPCWSTR convertedPath = str;					// LPCWSTR에 wc를 대입

	//DC영역을 사용하고싶을때는 가져온다
	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new ImageInfo;
	_imageInfo->_hMemDC = CreateCompatibleDC(hdc);		//빈 DC영역 생성
	_imageInfo->_hBitmap = (HBITMAP)LoadImage(g_hInstance, convertedPath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->_hOldBitmap = (HBITMAP)SelectObject(_imageInfo->_hMemDC, _imageInfo->_hBitmap);
	_imageInfo->_x = x;
	_imageInfo->_y = y;
	_imageInfo->_width = width;		//이미지 크기 값 대입 받는다
	_imageInfo->_height = height;


	//파일 길이를 알아온다
	int len = lstrlen(convertedPath);


	_filePath = new CHAR[len + 1];
	strcpy_s(_filePath, len + 1, filePath);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new ImageInfo;
	_blendImage->_hMemDC = CreateCompatibleDC(hdc);
	_blendImage->_hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->_hOldBitmap = (HBITMAP)SelectObject(_blendImage->_hMemDC, _blendImage->_hBitmap);
	_blendImage->_width = WINSIZEX;
	_blendImage->_height = WINSIZEY;


	//비트맵이 생성이 되지않았다면
	if (_imageInfo->_hBitmap == NULL)
	{
		//메모리 해제 시키고
		Release();
		return E_FAIL;	//실패했다고 알려라
	}

	//가져온 DC를 해제
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char* filePath, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) Release();


	/// const char* 파일경로를 LPCWSTR로 변환하는 과정	
	int nLen = static_cast<int>(strlen(filePath) + 1);	// char 경로 길이
	wchar_t str[200] = L"";								// 임시 변수

	size_t cn;

	/// <summary>
	/// 멀티바이트 문자의 시퀀스를 와이드 문자의 시퀀스로 변환
	/// </summary>
	/// <param name="pcon">변환한 개수를 담을 메모리 주소</param>
	/// <param name="pwcs">변환한 유니코드 문자열을 저장할 버퍼</param>
	/// <param name="sizet">버퍼 크기</param>
	/// <param name="trans">문자열</param>
	/// <param name="transColor">변환할 최대 개수</param>
	/// <returns></returns>
	mbstowcs_s(&cn, str, 100, filePath, nLen);

	LPCWSTR convertedPath = str;					// LPCWSTR에 wc를 대입


	//DC영역을 사용하고싶을때는 가져온다
	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new ImageInfo;
	_imageInfo->_hMemDC = CreateCompatibleDC(hdc);		//빈 DC영역 생성
	_imageInfo->_hBitmap = (HBITMAP)LoadImage(g_hInstance, convertedPath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->_hOldBitmap = (HBITMAP)SelectObject(_imageInfo->_hMemDC, _imageInfo->_hBitmap);
	_imageInfo->_x = x;
	_imageInfo->_y = y;
	_imageInfo->_width = width;		//이미지 크기 값 대입 받는다
	_imageInfo->_height = height;
	_imageInfo->_frameWidth = width / frameX;
	_imageInfo->_frameHeight = height / frameY;
	_imageInfo->_currentFrameX = 0;
	_imageInfo->_currentFrameY = 0;
	_imageInfo->_maxFrameX = frameX - 1;
	_imageInfo->_maxFrameY = frameY - 1;

	//파일 길이를 알아온다
	int len = lstrlen(convertedPath);


	_filePath = new CHAR[len + 1];
	strcpy_s(_filePath, len + 1, filePath);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new ImageInfo;
	_blendImage->_hMemDC = CreateCompatibleDC(hdc);
	_blendImage->_hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->_hOldBitmap = (HBITMAP)SelectObject(_blendImage->_hMemDC, _blendImage->_hBitmap);
	_blendImage->_width = WINSIZEX;
	_blendImage->_height = WINSIZEY;


	//비트맵이 생성이 되지않았다면
	if (_imageInfo->_hBitmap == NULL)
	{
		//메모리 해제 시키고
		Release();
		return E_FAIL;	//실패했다고 알려라
	}

	//가져온 DC를 해제
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char* filePath, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) Release();

	/// const char* 파일경로를 LPCWSTR로 변환하는 과정	
	int nLen = static_cast<int>(strlen(filePath) + 1);	// char 경로 길이
	wchar_t str[200] = L"";								// 임시 변수

	size_t cn;

	/// <summary>
	/// 멀티바이트 문자의 시퀀스를 와이드 문자의 시퀀스로 변환
	/// </summary>
	/// <param name="pcon">변환한 개수를 담을 메모리 주소</param>
	/// <param name="pwcs">변환한 유니코드 문자열을 저장할 버퍼</param>
	/// <param name="sizet">버퍼 크기</param>
	/// <param name="trans">문자열</param>
	/// <param name="transColor">변환할 최대 개수</param>
	/// <returns></returns>
	mbstowcs_s(&cn, str, 100, filePath, nLen);

	LPCWSTR convertedPath = str;					// LPCWSTR에 wc를 대입



	//DC영역을 사용하고싶을때는 가져온다
	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new ImageInfo;
	_imageInfo->_hMemDC = CreateCompatibleDC(hdc);		//빈 DC영역 생성
	_imageInfo->_hBitmap = (HBITMAP)LoadImage(g_hInstance, convertedPath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->_hOldBitmap = (HBITMAP)SelectObject(_imageInfo->_hMemDC, _imageInfo->_hBitmap);
	_imageInfo->_width = width;		//이미지 크기 값 대입 받는다
	_imageInfo->_height = height;
	_imageInfo->_frameWidth = width / frameX;
	_imageInfo->_frameHeight = height / frameY;
	_imageInfo->_currentFrameX = 0;
	_imageInfo->_currentFrameY = 0;
	_imageInfo->_maxFrameX = frameX - 1;
	_imageInfo->_maxFrameY = frameY - 1;

	//파일 길이를 알아온다
	int len = lstrlen(convertedPath);


	_filePath = new CHAR[len + 1];
	strcpy_s(_filePath, len + 1, filePath);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new ImageInfo;
	_blendImage->_hMemDC = CreateCompatibleDC(hdc);
	_blendImage->_hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->_hOldBitmap = (HBITMAP)SelectObject(_blendImage->_hMemDC, _blendImage->_hBitmap);
	_blendImage->_width = WINSIZEX;
	_blendImage->_height = WINSIZEY;


	//비트맵이 생성이 되지않았다면
	if (_imageInfo->_hBitmap == NULL)
	{
		//메모리 해제 시키고
		Release();
		return E_FAIL;	//실패했다고 알려라
	}

	//가져온 DC를 해제
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

void Image::Render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					// 복사할 영역의 DC
			_imageInfo->_x,			// 복사될 곳의 좌표 X
			_imageInfo->_y,			// 복사될 곳의 좌표 Y
			_imageInfo->_width,		// 복사될 가로 사이즈
			_imageInfo->_height,	// 복사될 세로 사이즈
			_imageInfo->_hMemDC,	// 복사해올 원본 DC
			0,						// 원본의 좌표 X
			0,						// 원본의 좌표 Y
			_imageInfo->_width,		// 복사해올 가로 사이즈
			_imageInfo->_height,	// 복사해올 세로 사이즈
			_transColor				// 어떤 색을 지울건가?
		);
	}
	else
	{
		// 백버퍼에 있는 것을 DC 영역으로 고속 복사
		BitBlt(
			hdc,					// 복사될(dest) DC
			_imageInfo->_x,			// 복사될 좌표 X
			_imageInfo->_y,			// 복사될 좌표 Y
			_imageInfo->_width,		// 가로 사이즈
			_imageInfo->_height,	// 세로 사이즈
			_imageInfo->_hMemDC,	// 원본(source) DC
			0,						// 원본의 시작 지점 X
			0,						// 원본의 시작 지점 Y
			SRCCOPY
		);
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			_imageInfo->_width,		//복사될 크기(가로)
			_imageInfo->_height,	//복사될 크기(세로)
			_imageInfo->_hMemDC,	//복사해올 DC
			0,						//복사해올 좌표 X
			0,						//복사해올 좌표 Y
			_imageInfo->_width,		//복사해올 크기
			_imageInfo->_height,	//복사해올 크기
			_transColor				//복사해올때 어떤 컬러를 빼고 가져올꺼냐
		);
	}
	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
		BitBlt(
			hdc,
			destX,
			destY,
			_imageInfo->_width,
			_imageInfo->_height,
			_imageInfo->_hMemDC,
			0,
			0,
			SRCCOPY);
	}
}

// 그릴 DC, dest그리기 시작할 좌표(x, y), source의 그리기 시작할 좌표(x, y), source의 사이즈(w * h)
void Image::Render(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					// 복사될 영역DC
			destX,					// 복사될 좌표 X
			destY,					// 복사될 좌표 Y
			sourceWidth,			// 복사될 가로크기
			sourceHeight,			// 복사될 세로크기
			_imageInfo->_hMemDC,
			sourceX,				// 원본 좌표 X
			sourceY,				// 원본 좌표 Y
			sourceWidth,			// 복사해올 가로크기
			sourceHeight,			// 복사해올 세로크기
			_transColor				// 지울 색
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			sourceWidth,
			sourceHeight,
			_imageInfo->_hMemDC,
			sourceX,
			sourceY,
			SRCCOPY
		);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY, bool loop)
{
	Animation();

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,													//복사될 영역의 DC
			destX,													//복사될 좌표 X
			destY,													//복사될 좌표 Y
			_imageInfo->_frameWidth,								//복사될 크기(가로)
			_imageInfo->_frameHeight,								//복사될 크기(세로)
			_imageInfo->_hMemDC,									//복사해올 DC
			_imageInfo->_currentFrameX * _imageInfo->_frameWidth,
			_imageInfo->_currentFrameY * _imageInfo->_frameHeight,	//복사해올 좌표X,Y
			_imageInfo->_frameWidth,								//복사해올 크기
			_imageInfo->_frameHeight,								//복사해올 크기
			_transColor
		);											//복사해올때 어떤 컬러를 빼고 가져올꺼냐
	}

	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
		BitBlt(
			hdc, 
			destX, 
			destY,
			_imageInfo->_frameWidth,
			_imageInfo->_frameHeight,
			_imageInfo->_hMemDC,
			_imageInfo->_currentFrameX * _imageInfo->_frameWidth,
			_imageInfo->_currentFrameY * _imageInfo->_frameHeight,
			SRCCOPY
		);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->_currentFrameX = currentFrameX;
	_imageInfo->_currentFrameY = currentFrameY;

	// 애니메이션 연산
	Animation();

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,										//복사될 영역의 DC
			destX,										//복사될 좌표 X
			destY,										//복사될 좌표 Y
			_imageInfo->_frameWidth,					//복사될 크기(가로)
			_imageInfo->_frameHeight,					//복사될 크기(세로)
			_imageInfo->_hMemDC,						//복사해올 DC
			currentFrameX * _imageInfo->_frameWidth,
			currentFrameY * _imageInfo->_frameHeight,	//복사해올 좌표X,Y
			_imageInfo->_frameWidth,					//복사해올 크기
			_imageInfo->_frameHeight,					//복사해올 크기
			_transColor									//복사해올때 어떤 컬러를 빼고 가져올꺼냐
		);						
	}
	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
		BitBlt(
			hdc, 
			destX, 
			destY,
			_imageInfo->_frameWidth,
			_imageInfo->_frameHeight,
			_imageInfo->_hMemDC,
			currentFrameX * _imageInfo->_frameWidth,
			currentFrameY * _imageInfo->_frameHeight,
			SRCCOPY
		);
	}
}

void Image::Animation()
{
	_animTimeCount += TIMEMANAGER->GetElaspedTimeSec();

	if (_animTimeCount > _animTimeRate)		
	{
		_animTimeCount = 0.0f;				// 카운트 초기화

		++_imageInfo->_currentFrameX;

		if (_imageInfo->_currentFrameX >= _imageInfo->_maxFrameX) 
			_imageInfo->_currentFrameX = 0;	//프레임 리셋.
	}


}

void Image::SetAnimRate(int rate)
{
	this->_animTimeRate = 1.0 / static_cast<float>(rate);
}

void Image::Release(void)
{
	// 이미지 정보가 있다면
	if (_imageInfo)
	{
		DeleteObject(_imageInfo->_hBitmap);
		DeleteDC(_imageInfo->_hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_filePath);

		_trans = false;
		_transColor = RGB(0, 0, 0);

	}
}

// 트랜스컬러를 다른 색으로 바꿔야 한다면
void Image::SetTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}


RECT Image::GetCollisionBox(void)
{
	// 충돌영역 RECT를 하나 만든다
	RECT rc;

	//프레임이 아닌 일반 이미지 일 경우
	if (_imageInfo->_maxFrameX <= 0 || _imageInfo->_maxFrameY <= 0)
	{
		rc = { int(_imageInfo->_x),
			int(_imageInfo->_y),
			int(_imageInfo->_x + _imageInfo->_width),
			int(_imageInfo->_y + _imageInfo->_height)
		};
	}
	else	// 프레임(스프라이트)이미지 일 경우
	{
		rc = { int(_imageInfo->_x),
			int(_imageInfo->_y),
			int(_imageInfo->_x + _imageInfo->_frameWidth),
			int(_imageInfo->_y + _imageInfo->_frameHeight)
		};
	}

	return rc;
	
}

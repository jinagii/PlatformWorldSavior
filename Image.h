#pragma once

/// <summary>
/// 이미지 클래스
/// 
/// 게임내에서 사용할 bmp(스프라이트)이미지 관련 클래스이다.
/// 
/// 2020.11.17 
/// </summary>

class Image
{
	struct ImageInfo
	{
		HDC _hMemDC;			// 메모리 DC
		HBITMAP _hBitmap;		// 비트맵 핸들
		HBITMAP _hOldBitmap;	// 올드 비트맵 핸들

		float _x;				// 이미지 X 좌표 (left)
		float _y;				// 이미지 Y 좌표 (top
		int _width;				// 가로 크기
		int _height;			// 세로 크기

		int _currentFrameX;		// 현재 프레임 X
		int _currentFrameY;		// 현재 프레임 Y
		int _maxFrameX;			// 최대 프레임 X
		int _maxFrameY;			// 최대 프레임 Y
		int _frameWidth;		// 프레임 가로 크기
		int _frameHeight;		// 프레임 세로 크기

		RECT _boundingBox;		// 충돌 체크용 박스(필요하다면..)

		ImageInfo()
		{
			_hMemDC = nullptr;
			_hBitmap = nullptr;
			_hOldBitmap = nullptr;
			_width = 0;
			_height = 0;
			_x = 0;
			_y = 0;
			_currentFrameX = 0;
			_currentFrameY = 0;
			_maxFrameX = 0;
			_maxFrameY = 0;
			_frameWidth = 0;
			_frameHeight = 0;
			_boundingBox = MakeRect(0, 0, 0, 0);
		}

	};

private:
	ImageInfo*		_imageInfo;		// 이미지 정보 구조체
	CHAR*			_filePath;		// 파일 경로(이름)
	BOOL			_trans;			// 트랜스 컬러 유무(특정 픽셀 값 제거)
	COLORREF		_transColor;	// 제거할 색깔

									//*****************************************************************
	BLENDFUNCTION	_blendFunc;		//알파블렌드에 관한 함수
	ImageInfo*		_blendImage;	//알파블렌드 먹일 이미지
									//*****************************************************************

	// 스프라이트 애니메이션 관련
	float _animTimeCount;
	float _animTimeRate;

// Constructor
public:
	Image();
	~Image();


	// Functions
public:
	//=======================
	//	Getter(), Setter()	=
	//=======================

	// DC
	HDC GetMemDC() { return _imageInfo->_hMemDC; }
	

	// Image
	float GetX() { return _imageInfo->_x; }
	void SetX(float x) { _imageInfo->_x = x; }

	float GetY() { return _imageInfo->_y; }
	void SetY(float y) { _imageInfo->_y = y; }

	int GetWidth() { return _imageInfo->_width; }
	int GetHeight() { return _imageInfo->_height; }

	// Frame
	int GetCurFrameX() { return _imageInfo->_currentFrameX; }
	void SetCurFrameX(int frameX)
	{
		(frameX < _imageInfo->_maxFrameX) ? _imageInfo->_currentFrameX = frameX : _imageInfo->_currentFrameX = _imageInfo->_maxFrameX;
	}

	int GetCurFrameY() { return _imageInfo->_currentFrameY; }
	void SetCurFrameY(int frameY)
	{
		(frameY < _imageInfo->_maxFrameY) ? _imageInfo->_currentFrameY = frameY : _imageInfo->_currentFrameY = _imageInfo->_maxFrameY;
	}

	// 이미지의 Max 프레임 수를 반환
	int GetMaxFrameX() { return _imageInfo->_maxFrameX; }
	int GetMaxFrameY() { return _imageInfo->_maxFrameY; }

	// 프레임의 사이즈 반환
	int GetFrameWidth() { return _imageInfo->_frameWidth; }
	int GetFrameHeight() { return _imageInfo->_frameHeight; }

	// 이미지를 [x,y]를 중점으로 이동
	void SetCentner(float x, float y)
	{
		_imageInfo->_x = x - (_imageInfo->_width / 2);
		_imageInfo->_y = y - (_imageInfo->_height / 2);
	}

	// 트랜스처리를 다른 색으로 바꿔야 할 때
	void SetTransColor(BOOL trans, COLORREF transColor);


	//=======================
	//   Initialize 초기화	=
	//=======================

	// 빈 비트맵 이미지 초기화
	HRESULT Init(int width, int height);

	// 파일로부터 이미지 초기화
	HRESULT Init(const char* filePath, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);

	// 파일로 부터 이미지 초기화
	HRESULT Init(const char* filePath, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);

	// 이미지 + 프레임 초기화
	HRESULT Init(const char* filePath, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	HRESULT Init(const char* filePath, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	
	//==================================================================================================================

	//=======================
	//		Render 렌더		=
	//=======================
	void Render(HDC hdc);

	//			뿌릴DC , 뿌릴곳X(Left), 뿌릴곳Y(top)
	void Render(HDC hdc, int destX, int destY);

	//			뿌릴DC , 뿌릴곳X(Left), 뿌릴곳Y(top), 소스 시작 좌표,		소스 사이즈
	void Render(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight);


	//프레임랜더
	void FrameRender(HDC hdc, int destX, int destY, bool loop = true);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void Animation();
	void SetAnimRate(int rate);

	//=======================
	//	  Release 릴리즈		=
	//=======================
	void Release(void);
	
	// 이미지 자체 충돌 박스
	RECT GetCollisionBox(void);
	

};
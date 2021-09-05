#pragma once

/// <summary>
/// �̹��� Ŭ����
/// 
/// ���ӳ����� ����� bmp(��������Ʈ)�̹��� ���� Ŭ�����̴�.
/// 
/// 2020.11.17 
/// </summary>

class Image
{
	struct ImageInfo
	{
		HDC _hMemDC;			// �޸� DC
		HBITMAP _hBitmap;		// ��Ʈ�� �ڵ�
		HBITMAP _hOldBitmap;	// �õ� ��Ʈ�� �ڵ�

		float _x;				// �̹��� X ��ǥ (left)
		float _y;				// �̹��� Y ��ǥ (top
		int _width;				// ���� ũ��
		int _height;			// ���� ũ��

		int _currentFrameX;		// ���� ������ X
		int _currentFrameY;		// ���� ������ Y
		int _maxFrameX;			// �ִ� ������ X
		int _maxFrameY;			// �ִ� ������ Y
		int _frameWidth;		// ������ ���� ũ��
		int _frameHeight;		// ������ ���� ũ��

		RECT _boundingBox;		// �浹 üũ�� �ڽ�(�ʿ��ϴٸ�..)

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
	ImageInfo*		_imageInfo;		// �̹��� ���� ����ü
	CHAR*			_filePath;		// ���� ���(�̸�)
	BOOL			_trans;			// Ʈ���� �÷� ����(Ư�� �ȼ� �� ����)
	COLORREF		_transColor;	// ������ ����

									//*****************************************************************
	BLENDFUNCTION	_blendFunc;		//���ĺ��忡 ���� �Լ�
	ImageInfo*		_blendImage;	//���ĺ��� ���� �̹���
									//*****************************************************************

	// ��������Ʈ �ִϸ��̼� ����
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

	// �̹����� Max ������ ���� ��ȯ
	int GetMaxFrameX() { return _imageInfo->_maxFrameX; }
	int GetMaxFrameY() { return _imageInfo->_maxFrameY; }

	// �������� ������ ��ȯ
	int GetFrameWidth() { return _imageInfo->_frameWidth; }
	int GetFrameHeight() { return _imageInfo->_frameHeight; }

	// �̹����� [x,y]�� �������� �̵�
	void SetCentner(float x, float y)
	{
		_imageInfo->_x = x - (_imageInfo->_width / 2);
		_imageInfo->_y = y - (_imageInfo->_height / 2);
	}

	// Ʈ����ó���� �ٸ� ������ �ٲ�� �� ��
	void SetTransColor(BOOL trans, COLORREF transColor);


	//=======================
	//   Initialize �ʱ�ȭ	=
	//=======================

	// �� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT Init(int width, int height);

	// ���Ϸκ��� �̹��� �ʱ�ȭ
	HRESULT Init(const char* filePath, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);

	// ���Ϸ� ���� �̹��� �ʱ�ȭ
	HRESULT Init(const char* filePath, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);

	// �̹��� + ������ �ʱ�ȭ
	HRESULT Init(const char* filePath, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	HRESULT Init(const char* filePath, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	
	//==================================================================================================================

	//=======================
	//		Render ����		=
	//=======================
	void Render(HDC hdc);

	//			�Ѹ�DC , �Ѹ���X(Left), �Ѹ���Y(top)
	void Render(HDC hdc, int destX, int destY);

	//			�Ѹ�DC , �Ѹ���X(Left), �Ѹ���Y(top), �ҽ� ���� ��ǥ,		�ҽ� ������
	void Render(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight);


	//�����ӷ���
	void FrameRender(HDC hdc, int destX, int destY, bool loop = true);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void Animation();
	void SetAnimRate(int rate);

	//=======================
	//	  Release ������		=
	//=======================
	void Release(void);
	
	// �̹��� ��ü �浹 �ڽ�
	RECT GetCollisionBox(void);
	

};
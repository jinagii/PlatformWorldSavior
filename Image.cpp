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

// �� ��Ʈ�� �̹��� �ʱ�ȭ
HRESULT Image::Init(int width, int height)
{
	// �̹��� ������ ���� �ִٸ� �����Ѵ�
	if (_imageInfo) Release();


	// ���� ������ �ڵ�� ����� DC�� �����´�.
	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new ImageInfo();
	_imageInfo->_hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->_hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);	// �� ��Ʈ�� �̹��� ���� �� �ڵ� ����
	_imageInfo->_hOldBitmap = (HBITMAP)SelectObject(_imageInfo->_hMemDC, _imageInfo->_hBitmap);
	_imageInfo->_width = width;	// ��Ʈ�� ���� ũ�� ����
	_imageInfo->_height = height;	// ��Ʈ�� ���� ũ�� ����

	_filePath = nullptr;
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	// ��Ʈ�� ���� �����ߴٸ�
	if (!_imageInfo->_hBitmap)
	{
		Release();

		return E_FAIL;	// �����ߴٰ� �˸�
	}

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char* filePath, int width, int height, BOOL trans, COLORREF transColor)
{
	// �̹��� ������ ���� �ִٸ� �����Ѵ�.
	if (_imageInfo)
	{
		Release();
	}


	/// const char* ���ϰ�θ� LPCWSTR�� ��ȯ�ϴ� ����	
	int nLen = static_cast<int>(strlen(filePath) + 1);	// char ��� ����
	wchar_t str[200] = L"";								// �ӽ� ����

	size_t cn;

	/// <summary>
	/// ��Ƽ����Ʈ ������ �������� ���̵� ������ �������� ��ȯ
	/// </summary>
	/// <param name="pcon">��ȯ�� ������ ���� �޸� �ּ�</param>
	/// <param name="pwcs">��ȯ�� �����ڵ� ���ڿ��� ������ ����</param>
	/// <param name="sizet">���� ũ��</param>
	/// <param name="trans">���ڿ�</param>
	/// <param name="transColor">��ȯ�� �ִ� ����</param>
	/// <returns></returns>
	mbstowcs_s(&cn, str, 100, filePath, nLen);

	LPCWSTR convertedPath = str;					// LPCWSTR�� wc�� ����

	// ���� ������ �ڵ�� ����� DC�� �����´�.
	HDC hdc = GetDC(g_hWnd);
	_imageInfo = new ImageInfo;
	_imageInfo->_hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->_hBitmap = (HBITMAP)LoadImage(g_hInstance, convertedPath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->_hOldBitmap = (HBITMAP)SelectObject(_imageInfo->_hMemDC, _imageInfo->_hBitmap);
	_imageInfo->_width = width;
	_imageInfo->_height = height;

	// ���� ���̸� ��´�.
	int len = lstrlen(convertedPath);

	_filePath = new CHAR[len + 1];
	strcpy_s(_filePath, len + 1, filePath);

	/////////////////////////////////////////////////////////////////////

	_trans = trans;
	_transColor = transColor;

	// ��Ʈ���� �������� �ʾ�����
	if (!_imageInfo->_hBitmap)
	{
		// �޸� ������Ű��
		Release();

		// �����ߴٰ� �˸�
		return E_FAIL;
	}

	// ������ DC�� ����
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char* filePath, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//�̹��� ������ �����ִٸ� ���������
	if (_imageInfo != NULL) Release();


	/// const char* ���ϰ�θ� LPCWSTR�� ��ȯ�ϴ� ����	
	int nLen = static_cast<int>(strlen(filePath) + 1);	// char ��� ����
	wchar_t str[200] = L"";								// �ӽ� ����

	size_t cn;

	/// <summary>
	/// ��Ƽ����Ʈ ������ �������� ���̵� ������ �������� ��ȯ
	/// </summary>
	/// <param name="pcon">��ȯ�� ������ ���� �޸� �ּ�</param>
	/// <param name="pwcs">��ȯ�� �����ڵ� ���ڿ��� ������ ����</param>
	/// <param name="sizet">���� ũ��</param>
	/// <param name="trans">���ڿ�</param>
	/// <param name="transColor">��ȯ�� �ִ� ����</param>
	/// <returns></returns>
	mbstowcs_s(&cn, str, 100, filePath, nLen);


	LPCWSTR convertedPath = str;					// LPCWSTR�� wc�� ����

	//DC������ ����ϰ�������� �����´�
	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new ImageInfo;
	_imageInfo->_hMemDC = CreateCompatibleDC(hdc);		//�� DC���� ����
	_imageInfo->_hBitmap = (HBITMAP)LoadImage(g_hInstance, convertedPath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->_hOldBitmap = (HBITMAP)SelectObject(_imageInfo->_hMemDC, _imageInfo->_hBitmap);
	_imageInfo->_x = x;
	_imageInfo->_y = y;
	_imageInfo->_width = width;		//�̹��� ũ�� �� ���� �޴´�
	_imageInfo->_height = height;


	//���� ���̸� �˾ƿ´�
	int len = lstrlen(convertedPath);


	_filePath = new CHAR[len + 1];
	strcpy_s(_filePath, len + 1, filePath);

	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new ImageInfo;
	_blendImage->_hMemDC = CreateCompatibleDC(hdc);
	_blendImage->_hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->_hOldBitmap = (HBITMAP)SelectObject(_blendImage->_hMemDC, _blendImage->_hBitmap);
	_blendImage->_width = WINSIZEX;
	_blendImage->_height = WINSIZEY;


	//��Ʈ���� ������ �����ʾҴٸ�
	if (_imageInfo->_hBitmap == NULL)
	{
		//�޸� ���� ��Ű��
		Release();
		return E_FAIL;	//�����ߴٰ� �˷���
	}

	//������ DC�� ����
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char* filePath, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�̹��� ������ �����ִٸ� ���������
	if (_imageInfo != NULL) Release();


	/// const char* ���ϰ�θ� LPCWSTR�� ��ȯ�ϴ� ����	
	int nLen = static_cast<int>(strlen(filePath) + 1);	// char ��� ����
	wchar_t str[200] = L"";								// �ӽ� ����

	size_t cn;

	/// <summary>
	/// ��Ƽ����Ʈ ������ �������� ���̵� ������ �������� ��ȯ
	/// </summary>
	/// <param name="pcon">��ȯ�� ������ ���� �޸� �ּ�</param>
	/// <param name="pwcs">��ȯ�� �����ڵ� ���ڿ��� ������ ����</param>
	/// <param name="sizet">���� ũ��</param>
	/// <param name="trans">���ڿ�</param>
	/// <param name="transColor">��ȯ�� �ִ� ����</param>
	/// <returns></returns>
	mbstowcs_s(&cn, str, 100, filePath, nLen);

	LPCWSTR convertedPath = str;					// LPCWSTR�� wc�� ����


	//DC������ ����ϰ�������� �����´�
	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new ImageInfo;
	_imageInfo->_hMemDC = CreateCompatibleDC(hdc);		//�� DC���� ����
	_imageInfo->_hBitmap = (HBITMAP)LoadImage(g_hInstance, convertedPath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->_hOldBitmap = (HBITMAP)SelectObject(_imageInfo->_hMemDC, _imageInfo->_hBitmap);
	_imageInfo->_x = x;
	_imageInfo->_y = y;
	_imageInfo->_width = width;		//�̹��� ũ�� �� ���� �޴´�
	_imageInfo->_height = height;
	_imageInfo->_frameWidth = width / frameX;
	_imageInfo->_frameHeight = height / frameY;
	_imageInfo->_currentFrameX = 0;
	_imageInfo->_currentFrameY = 0;
	_imageInfo->_maxFrameX = frameX - 1;
	_imageInfo->_maxFrameY = frameY - 1;

	//���� ���̸� �˾ƿ´�
	int len = lstrlen(convertedPath);


	_filePath = new CHAR[len + 1];
	strcpy_s(_filePath, len + 1, filePath);

	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new ImageInfo;
	_blendImage->_hMemDC = CreateCompatibleDC(hdc);
	_blendImage->_hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->_hOldBitmap = (HBITMAP)SelectObject(_blendImage->_hMemDC, _blendImage->_hBitmap);
	_blendImage->_width = WINSIZEX;
	_blendImage->_height = WINSIZEY;


	//��Ʈ���� ������ �����ʾҴٸ�
	if (_imageInfo->_hBitmap == NULL)
	{
		//�޸� ���� ��Ű��
		Release();
		return E_FAIL;	//�����ߴٰ� �˷���
	}

	//������ DC�� ����
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char* filePath, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�̹��� ������ �����ִٸ� ���������
	if (_imageInfo != NULL) Release();

	/// const char* ���ϰ�θ� LPCWSTR�� ��ȯ�ϴ� ����	
	int nLen = static_cast<int>(strlen(filePath) + 1);	// char ��� ����
	wchar_t str[200] = L"";								// �ӽ� ����

	size_t cn;

	/// <summary>
	/// ��Ƽ����Ʈ ������ �������� ���̵� ������ �������� ��ȯ
	/// </summary>
	/// <param name="pcon">��ȯ�� ������ ���� �޸� �ּ�</param>
	/// <param name="pwcs">��ȯ�� �����ڵ� ���ڿ��� ������ ����</param>
	/// <param name="sizet">���� ũ��</param>
	/// <param name="trans">���ڿ�</param>
	/// <param name="transColor">��ȯ�� �ִ� ����</param>
	/// <returns></returns>
	mbstowcs_s(&cn, str, 100, filePath, nLen);

	LPCWSTR convertedPath = str;					// LPCWSTR�� wc�� ����



	//DC������ ����ϰ�������� �����´�
	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new ImageInfo;
	_imageInfo->_hMemDC = CreateCompatibleDC(hdc);		//�� DC���� ����
	_imageInfo->_hBitmap = (HBITMAP)LoadImage(g_hInstance, convertedPath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->_hOldBitmap = (HBITMAP)SelectObject(_imageInfo->_hMemDC, _imageInfo->_hBitmap);
	_imageInfo->_width = width;		//�̹��� ũ�� �� ���� �޴´�
	_imageInfo->_height = height;
	_imageInfo->_frameWidth = width / frameX;
	_imageInfo->_frameHeight = height / frameY;
	_imageInfo->_currentFrameX = 0;
	_imageInfo->_currentFrameY = 0;
	_imageInfo->_maxFrameX = frameX - 1;
	_imageInfo->_maxFrameY = frameY - 1;

	//���� ���̸� �˾ƿ´�
	int len = lstrlen(convertedPath);


	_filePath = new CHAR[len + 1];
	strcpy_s(_filePath, len + 1, filePath);

	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new ImageInfo;
	_blendImage->_hMemDC = CreateCompatibleDC(hdc);
	_blendImage->_hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->_hOldBitmap = (HBITMAP)SelectObject(_blendImage->_hMemDC, _blendImage->_hBitmap);
	_blendImage->_width = WINSIZEX;
	_blendImage->_height = WINSIZEY;


	//��Ʈ���� ������ �����ʾҴٸ�
	if (_imageInfo->_hBitmap == NULL)
	{
		//�޸� ���� ��Ű��
		Release();
		return E_FAIL;	//�����ߴٰ� �˷���
	}

	//������ DC�� ����
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

void Image::Render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					// ������ ������ DC
			_imageInfo->_x,			// ����� ���� ��ǥ X
			_imageInfo->_y,			// ����� ���� ��ǥ Y
			_imageInfo->_width,		// ����� ���� ������
			_imageInfo->_height,	// ����� ���� ������
			_imageInfo->_hMemDC,	// �����ؿ� ���� DC
			0,						// ������ ��ǥ X
			0,						// ������ ��ǥ Y
			_imageInfo->_width,		// �����ؿ� ���� ������
			_imageInfo->_height,	// �����ؿ� ���� ������
			_transColor				// � ���� ����ǰ�?
		);
	}
	else
	{
		// ����ۿ� �ִ� ���� DC �������� ��� ����
		BitBlt(
			hdc,					// �����(dest) DC
			_imageInfo->_x,			// ����� ��ǥ X
			_imageInfo->_y,			// ����� ��ǥ Y
			_imageInfo->_width,		// ���� ������
			_imageInfo->_height,	// ���� ������
			_imageInfo->_hMemDC,	// ����(source) DC
			0,						// ������ ���� ���� X
			0,						// ������ ���� ���� Y
			SRCCOPY
		);
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ������ DC
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			_imageInfo->_width,		//����� ũ��(����)
			_imageInfo->_height,	//����� ũ��(����)
			_imageInfo->_hMemDC,	//�����ؿ� DC
			0,						//�����ؿ� ��ǥ X
			0,						//�����ؿ� ��ǥ Y
			_imageInfo->_width,		//�����ؿ� ũ��
			_imageInfo->_height,	//�����ؿ� ũ��
			_transColor				//�����ؿö� � �÷��� ���� �����ò���
		);
	}
	else
	{
		//����ۿ� �ִ� ���� DC�������� ��Ӻ������ִ� �Լ�
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

// �׸� DC, dest�׸��� ������ ��ǥ(x, y), source�� �׸��� ������ ��ǥ(x, y), source�� ������(w * h)
void Image::Render(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					// ����� ����DC
			destX,					// ����� ��ǥ X
			destY,					// ����� ��ǥ Y
			sourceWidth,			// ����� ����ũ��
			sourceHeight,			// ����� ����ũ��
			_imageInfo->_hMemDC,
			sourceX,				// ���� ��ǥ X
			sourceY,				// ���� ��ǥ Y
			sourceWidth,			// �����ؿ� ����ũ��
			sourceHeight,			// �����ؿ� ����ũ��
			_transColor				// ���� ��
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
			hdc,													//����� ������ DC
			destX,													//����� ��ǥ X
			destY,													//����� ��ǥ Y
			_imageInfo->_frameWidth,								//����� ũ��(����)
			_imageInfo->_frameHeight,								//����� ũ��(����)
			_imageInfo->_hMemDC,									//�����ؿ� DC
			_imageInfo->_currentFrameX * _imageInfo->_frameWidth,
			_imageInfo->_currentFrameY * _imageInfo->_frameHeight,	//�����ؿ� ��ǥX,Y
			_imageInfo->_frameWidth,								//�����ؿ� ũ��
			_imageInfo->_frameHeight,								//�����ؿ� ũ��
			_transColor
		);											//�����ؿö� � �÷��� ���� �����ò���
	}

	else
	{
		//����ۿ� �ִ� ���� DC�������� ��Ӻ������ִ� �Լ�
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

	// �ִϸ��̼� ����
	Animation();

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,										//����� ������ DC
			destX,										//����� ��ǥ X
			destY,										//����� ��ǥ Y
			_imageInfo->_frameWidth,					//����� ũ��(����)
			_imageInfo->_frameHeight,					//����� ũ��(����)
			_imageInfo->_hMemDC,						//�����ؿ� DC
			currentFrameX * _imageInfo->_frameWidth,
			currentFrameY * _imageInfo->_frameHeight,	//�����ؿ� ��ǥX,Y
			_imageInfo->_frameWidth,					//�����ؿ� ũ��
			_imageInfo->_frameHeight,					//�����ؿ� ũ��
			_transColor									//�����ؿö� � �÷��� ���� �����ò���
		);						
	}
	else
	{
		//����ۿ� �ִ� ���� DC�������� ��Ӻ������ִ� �Լ�
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
		_animTimeCount = 0.0f;				// ī��Ʈ �ʱ�ȭ

		++_imageInfo->_currentFrameX;

		if (_imageInfo->_currentFrameX >= _imageInfo->_maxFrameX) 
			_imageInfo->_currentFrameX = 0;	//������ ����.
	}


}

void Image::SetAnimRate(int rate)
{
	this->_animTimeRate = 1.0 / static_cast<float>(rate);
}

void Image::Release(void)
{
	// �̹��� ������ �ִٸ�
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

// Ʈ�����÷��� �ٸ� ������ �ٲ�� �Ѵٸ�
void Image::SetTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}


RECT Image::GetCollisionBox(void)
{
	// �浹���� RECT�� �ϳ� �����
	RECT rc;

	//�������� �ƴ� �Ϲ� �̹��� �� ���
	if (_imageInfo->_maxFrameX <= 0 || _imageInfo->_maxFrameY <= 0)
	{
		rc = { int(_imageInfo->_x),
			int(_imageInfo->_y),
			int(_imageInfo->_x + _imageInfo->_width),
			int(_imageInfo->_y + _imageInfo->_height)
		};
	}
	else	// ������(��������Ʈ)�̹��� �� ���
	{
		rc = { int(_imageInfo->_x),
			int(_imageInfo->_y),
			int(_imageInfo->_x + _imageInfo->_frameWidth),
			int(_imageInfo->_y + _imageInfo->_frameHeight)
		};
	}

	return rc;
	
}

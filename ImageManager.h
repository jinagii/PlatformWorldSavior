#pragma once

#include "SingletonBase.h"
#include "Image.h"

/// <summary>
/// �̹����� �߰��ϰ� �����ϴ� �̹��� �Ŵ��� Ŭ����
/// 
/// 2020.11.17
/// </summary>

class ImageManager : public SingletonBase<ImageManager>
{
	// Constructor
public:
	ImageManager();
	~ImageManager();


	// �̹����� ������ �� ���� ������
private:
	typedef std::map<std::string, Image*>				MapImageList;
	typedef std::map<std::string, Image*>::iterator		MapImageIter;

private:
	MapImageList _mImageList;	// �̹��� ����Ʈ

// Functions
public:
	HRESULT Init();		// �ʱ�ȭ
	void Release();		// ������



	//=========================================================
	//	����Ʈ�� �̹��� �߰�
	//=========================================================
	Image* AddImage(std::string strKey, int width, int height);
	Image* AddImage(std::string strKey, const char* filePath, int width, int height, bool trans, COLORREF transColor);

	Image* AddImage(std::string strKey, const char* filePath, float x, float y, int width, int height, bool trans, COLORREF transColor);

	Image* AddFrameImage(std::string strKey, const char* filePath, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	Image* AddFrameImage(std::string strKey, const char* filePath, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);


	// Ű ������ �̹��� ã��
	Image* FindImage(std::string strKey);

	// Ű ������ �̹��� ����
	BOOL DeleteImage(std::string strKey);

	// ��� �̹��� ����
	BOOL DeleteAll(void);

	// ����
	void Render(std::string strKey, HDC hdc);
	void Render(std::string strKey, HDC hdc, int destX, int destY);
	void Render(std::string strKey, HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight);

	//������ ����
	void FrameRender(std::string strKey, HDC hdc, int destX, int destY);
	void FrameRender(std::string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
};
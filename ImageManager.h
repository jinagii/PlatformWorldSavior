#pragma once

#include "SingletonBase.h"
#include "Image.h"

/// <summary>
/// 이미지를 추가하고 관리하는 이미지 매니져 클래스
/// 
/// 2020.11.17
/// </summary>

class ImageManager : public SingletonBase<ImageManager>
{
	// Constructor
public:
	ImageManager();
	~ImageManager();


	// 이미지를 저장할 맵 구조 재정의
private:
	typedef std::map<std::string, Image*>				MapImageList;
	typedef std::map<std::string, Image*>::iterator		MapImageIter;

private:
	MapImageList _mImageList;	// 이미지 리스트

// Functions
public:
	HRESULT Init();		// 초기화
	void Release();		// 릴리즈



	//=========================================================
	//	리스트에 이미지 추가
	//=========================================================
	Image* AddImage(std::string strKey, int width, int height);
	Image* AddImage(std::string strKey, const char* filePath, int width, int height, bool trans, COLORREF transColor);

	Image* AddImage(std::string strKey, const char* filePath, float x, float y, int width, int height, bool trans, COLORREF transColor);

	Image* AddFrameImage(std::string strKey, const char* filePath, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	Image* AddFrameImage(std::string strKey, const char* filePath, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);


	// 키 값으로 이미지 찾기
	Image* FindImage(std::string strKey);

	// 키 값으로 이미지 제거
	BOOL DeleteImage(std::string strKey);

	// 모든 이미지 제거
	BOOL DeleteAll(void);

	// 렌더
	void Render(std::string strKey, HDC hdc);
	void Render(std::string strKey, HDC hdc, int destX, int destY);
	void Render(std::string strKey, HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight);

	//프레임 렌더
	void FrameRender(std::string strKey, HDC hdc, int destX, int destY);
	void FrameRender(std::string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
};
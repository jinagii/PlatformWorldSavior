#include "pch.h"
#include "ImageManager.h"

ImageManager::ImageManager()
{

}

ImageManager::~ImageManager()
{
}

HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
	DeleteAll();
}

Image* ImageManager::AddImage(std::string strKey, int width, int height)
{
	// 먼저 해당하는 이미지가 있는지 찾음
	Image* img = FindImage(strKey);

	// 이미지가 있으면 그냥 그 이미지 리턴
	if (img) return img;

	// 이미지가 없다면 새로 만듬
	img = new Image;

	// 이미지 초기화가 실패하면
	if (FAILED(img->Init(width, height)))
	{
		// 다시 안전하게 제거하고
		SAFE_DELETE(img);

		// 널 포인터 반환
		return nullptr;
	}

	// 정상적으로 만들어 졌다면 추가해준다.
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddImage(std::string strKey, const char* filePath, int width, int height, bool trans, COLORREF transColor)
{
	// 먼저 해당하는 이미지가 있는지 찾음
	Image* img = FindImage(strKey);

	// 이미지가 있으면 그냥 그 이미지 리턴
	if (img) return img;

	// 이미지가 없다면 새로 만듬
	img = new Image;

	// 이미지 초기화가 실패하면
	if (FAILED(img->Init(filePath, width, height, trans, transColor)))
	{
		// 다시 안전하게 제거하고
		SAFE_DELETE(img);

		// 널 포인터 반환
		return nullptr;
	}

	// 정상적으로 만들어 졌다면 추가해준다.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddImage(std::string strKey, const char* filePath, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	// 먼저 해당하는 이미지가 있는지 찾음
	Image* img = FindImage(strKey);

	// 이미지가 있으면 그냥 그 이미지 리턴
	if (img) return img;

	// 이미지가 없다면 새로 만듬
	img = new Image;

	// 이미지 초기화가 실패하면
	if (FAILED(img->Init(filePath, x, y, width, height, trans, transColor)))
	{
		// 다시 안전하게 제거하고
		SAFE_DELETE(img);

		// 널 포인터 반환
		return nullptr;
	}

	// 정상적으로 만들어 졌다면 추가해준다.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddFrameImage(std::string strKey, const char* filePath, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	// 먼저 해당하는 이미지가 있는지 찾음
	Image* img = FindImage(strKey);

	// 이미지가 있으면 그냥 그 이미지 리턴
	if (img) return img;

	// 이미지가 없다면 새로 만듬
	img = new Image;

	// 이미지 초기화가 실패하면
	if (FAILED(img->Init(filePath, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		// 다시 안전하게 제거하고
		SAFE_DELETE(img);

		// 널 포인터 반환
		return nullptr;
	}

	// 정상적으로 만들어 졌다면 추가해준다.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddFrameImage(std::string strKey, const char* filePath, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	// 먼저 해당하는 이미지가 있는지 찾음
	Image* img = FindImage(strKey);

	// 이미지가 있으면 그냥 그 이미지 리턴
	if (img) return img;

	// 이미지가 없다면 새로 만듬
	img = new Image;

	// 이미지 초기화가 실패하면
	if (FAILED(img->Init(filePath, width, height, frameX, frameY, trans, transColor)))
	{
		// 다시 안전하게 제거하고
		SAFE_DELETE(img);

		// 널 포인터 반환
		return nullptr;
	}

	// 정상적으로 만들어 졌다면 추가해준다.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::FindImage(std::string strKey)
{
	MapImageIter key = _mImageList.find(strKey);

	// 찾았다면(존재하면)
	if (key != _mImageList.end())
	{
		return key->second;
	}

	// 실패하면(없으면)
	return nullptr;
}

BOOL ImageManager::DeleteImage(std::string strKey)
{
	MapImageIter key = _mImageList.find(strKey);

	//지울 이미지를 발견
	if (key != _mImageList.end())
	{
		// 찾은 이미지의 릴리즈 실행
		key->second->Release();

		// 이미지 메모리 해제
		SAFE_DELETE(key->second);

		// 리스트에서 제거
		_mImageList.erase(key);

		return true;
	}

	return false;
}

BOOL ImageManager::DeleteAll(void)
{
	MapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		//이미지 정보가 있다!
		if (iter->second != NULL)
		{
			// 이미지 메모리 해제
			SAFE_DELETE(iter->second);

			// 리스트에서 제거
			iter = _mImageList.erase(iter);
		}

		// 다음으로
		else ++iter;
	}

	_mImageList.clear();

	return true;
}

void ImageManager::Render(std::string strKey, HDC hdc)
{
	Image* img = FindImage(strKey);

	if (img) img->Render(hdc);
}

void ImageManager::Render(std::string strKey, HDC hdc, int destX, int destY)
{
	Image* img = FindImage(strKey);

	if (img) img->Render(hdc, destX, destY);
}

void ImageManager::Render(std::string strKey, HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight)
{
	Image* img = FindImage(strKey);

	if (img) img->Render(hdc, destX, destY, sourceX, sourceY, sourceWidth, sourceHeight);
}

void ImageManager::FrameRender(std::string strKey, HDC hdc, int destX, int destY)
{
	Image* img = FindImage(strKey);
	if (img)img->FrameRender(hdc, destX, destY);
}

void ImageManager::FrameRender(std::string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	Image* img = FindImage(strKey);
	if (img)img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

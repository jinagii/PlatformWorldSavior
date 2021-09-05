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
	// ���� �ش��ϴ� �̹����� �ִ��� ã��
	Image* img = FindImage(strKey);

	// �̹����� ������ �׳� �� �̹��� ����
	if (img) return img;

	// �̹����� ���ٸ� ���� ����
	img = new Image;

	// �̹��� �ʱ�ȭ�� �����ϸ�
	if (FAILED(img->Init(width, height)))
	{
		// �ٽ� �����ϰ� �����ϰ�
		SAFE_DELETE(img);

		// �� ������ ��ȯ
		return nullptr;
	}

	// ���������� ����� ���ٸ� �߰����ش�.
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddImage(std::string strKey, const char* filePath, int width, int height, bool trans, COLORREF transColor)
{
	// ���� �ش��ϴ� �̹����� �ִ��� ã��
	Image* img = FindImage(strKey);

	// �̹����� ������ �׳� �� �̹��� ����
	if (img) return img;

	// �̹����� ���ٸ� ���� ����
	img = new Image;

	// �̹��� �ʱ�ȭ�� �����ϸ�
	if (FAILED(img->Init(filePath, width, height, trans, transColor)))
	{
		// �ٽ� �����ϰ� �����ϰ�
		SAFE_DELETE(img);

		// �� ������ ��ȯ
		return nullptr;
	}

	// ���������� ����� ���ٸ� �߰����ش�.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddImage(std::string strKey, const char* filePath, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	// ���� �ش��ϴ� �̹����� �ִ��� ã��
	Image* img = FindImage(strKey);

	// �̹����� ������ �׳� �� �̹��� ����
	if (img) return img;

	// �̹����� ���ٸ� ���� ����
	img = new Image;

	// �̹��� �ʱ�ȭ�� �����ϸ�
	if (FAILED(img->Init(filePath, x, y, width, height, trans, transColor)))
	{
		// �ٽ� �����ϰ� �����ϰ�
		SAFE_DELETE(img);

		// �� ������ ��ȯ
		return nullptr;
	}

	// ���������� ����� ���ٸ� �߰����ش�.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddFrameImage(std::string strKey, const char* filePath, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	// ���� �ش��ϴ� �̹����� �ִ��� ã��
	Image* img = FindImage(strKey);

	// �̹����� ������ �׳� �� �̹��� ����
	if (img) return img;

	// �̹����� ���ٸ� ���� ����
	img = new Image;

	// �̹��� �ʱ�ȭ�� �����ϸ�
	if (FAILED(img->Init(filePath, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		// �ٽ� �����ϰ� �����ϰ�
		SAFE_DELETE(img);

		// �� ������ ��ȯ
		return nullptr;
	}

	// ���������� ����� ���ٸ� �߰����ش�.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddFrameImage(std::string strKey, const char* filePath, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	// ���� �ش��ϴ� �̹����� �ִ��� ã��
	Image* img = FindImage(strKey);

	// �̹����� ������ �׳� �� �̹��� ����
	if (img) return img;

	// �̹����� ���ٸ� ���� ����
	img = new Image;

	// �̹��� �ʱ�ȭ�� �����ϸ�
	if (FAILED(img->Init(filePath, width, height, frameX, frameY, trans, transColor)))
	{
		// �ٽ� �����ϰ� �����ϰ�
		SAFE_DELETE(img);

		// �� ������ ��ȯ
		return nullptr;
	}

	// ���������� ����� ���ٸ� �߰����ش�.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::FindImage(std::string strKey)
{
	MapImageIter key = _mImageList.find(strKey);

	// ã�Ҵٸ�(�����ϸ�)
	if (key != _mImageList.end())
	{
		return key->second;
	}

	// �����ϸ�(������)
	return nullptr;
}

BOOL ImageManager::DeleteImage(std::string strKey)
{
	MapImageIter key = _mImageList.find(strKey);

	//���� �̹����� �߰�
	if (key != _mImageList.end())
	{
		// ã�� �̹����� ������ ����
		key->second->Release();

		// �̹��� �޸� ����
		SAFE_DELETE(key->second);

		// ����Ʈ���� ����
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
		//�̹��� ������ �ִ�!
		if (iter->second != NULL)
		{
			// �̹��� �޸� ����
			SAFE_DELETE(iter->second);

			// ����Ʈ���� ����
			iter = _mImageList.erase(iter);
		}

		// ��������
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

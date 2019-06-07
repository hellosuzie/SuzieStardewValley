#include "stdafx.h"
#include "GameImage.h"
#include "SCore.h"
#include "ReadStream.h"

GameImage::GameImage() 
	: m_ImageDC(nullptr), m_hBitMap(nullptr), m_hOldBitMap(nullptr)
	, m_TransColor(0), m_Alpha(false)
{
	//인포 초기화
	memset(&m_ImageInfo, 0, sizeof(m_ImageInfo));
}


GameImage::~GameImage()
{
	DeleteObject(m_hBitMap);
	DeleteDC(m_ImageDC);
}

bool GameImage::ImageLoad(const WCHAR* _Path)
{
	Tassert(nullptr == SINST);
	m_hBitMap = (HBITMAP)LoadImageW(SINST, _Path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == m_hBitMap)
	{
		Tassert(true);
		return false;
	}

	m_ImageDC = CreateCompatibleDC(SHDC);
	Tassert(nullptr == m_ImageDC);

	m_hOldBitMap = (HBITMAP)SelectObject(m_ImageDC, m_hBitMap);
	GetObject(m_hBitMap, sizeof(BITMAP), &m_ImageInfo);
	AlphaHeaderCheck(_Path);
	return true;
}

bool GameImage::CreateImage(FSIZE _Size)
{
	Tassert(nullptr == SINST);

	m_ImageDC = CreateCompatibleDC(SHDC);
	Tassert(nullptr == m_ImageDC);

	//내가 지정한 사이즈만큼의 빈 이미지 생성
	m_hBitMap = CreateCompatibleBitmap(SHDC, _Size.IX(), _Size.IY());
	Tassert(nullptr == m_hBitMap);

	m_hOldBitMap = (HBITMAP)SelectObject(m_ImageDC, m_hBitMap);
	GetObject(m_hBitMap, sizeof(BITMAP), &m_ImageInfo);
	return true;
}

void GameImage::AlphaHeaderCheck(const WCHAR * _ImagePath)
{
	ReadStream ImageInfo = ReadStream(_ImagePath);

	BITMAPFILEHEADER TempHeader;
	ImageInfo >> TempHeader;
	ImageInfo >> m_InfoHeader;
}

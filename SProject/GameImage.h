#pragma once

class GameImage
{
private:
	HDC m_ImageDC;
	HBITMAP m_hBitMap;
	HBITMAP m_hOldBitMap;
	BITMAP m_ImageInfo;

	UINT m_TransColor;
	bool m_Alpha;

	BITMAPINFOHEADER m_InfoHeader;

public:
	GameImage();
	~GameImage();

public:
	inline bool AlphaCheck()
	{
		//24보다 크면 true 작으면 false
		return m_InfoHeader.biBitCount > 24;
	}

	inline HDC ImageDC()
	{
		return m_ImageDC;
	}
	inline int Width()
	{
		return m_ImageInfo.bmWidth;
	}
	inline int Height()
	{
		return m_ImageInfo.bmHeight;
	}
	inline FSIZE ImageSize()
	{
		return FSIZE({ m_ImageInfo.bmWidth ,m_ImageInfo.bmHeight });
	}
	inline void TransColor(UINT _TransColor)
	{
		m_TransColor = _TransColor;
	}
	inline UINT TransColor()
	{
		return m_TransColor;
	}

public:
	bool ImageLoad(const WCHAR* _Path);
	bool CreateImage(FSIZE _Size);
	void AlphaHeaderCheck(const WCHAR* _ImagePath);

	//struct APICOLOR
	//{
	//	union
	//	{
	//		UINT Color;
	//		struct
	//		{
	//			BYTE R;
	//			BYTE G;
	//			BYTE B;
	//			BYTE A;
	//		};
	//	};
	//};

	//void Setpixel(IPOS _Pos, UINT _Color) 
	//{
	//	APICOLOR GColor;
	//	APICOLOR TColor;
	//	TColor.Color = _Color;
	//	TColor.A = 255;
	//	GColor.Color = GetPixel(m_ImageDC, _Pos.X, _Pos.Y);
	//	//SetPixel(m_ImageDC, _Pos.X, _Pos.Y, TColor.Color);
	//}

};



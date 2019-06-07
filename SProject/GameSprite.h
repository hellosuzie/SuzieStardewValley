#pragma once
#include "GameImage.h"

class GameSprite
{
private:
	GameImage* m_Image;
	FRECT m_Rect;

public:
	GameSprite(GameImage* _Image, FPOS _Pos, FSIZE _Size);
	~GameSprite();

public:
	inline GameImage* GetImage()
	{
		return m_Image;
	}
	inline FPOS Pos()
	{
		return m_Rect.Pos;
	}
	inline FPOS Size()
	{
		return m_Rect.Size;
	}
	UINT TransColor()
	{
		return m_Image->TransColor();
	}

public:
	HDC ImageDC()
	{
		return  m_Image->ImageDC();
	}
};


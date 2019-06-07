#include "stdafx.h"
#include "GameSprite.h"


GameSprite::GameSprite(GameImage* _Image, FPOS _Pos, FSIZE _Size) 
	: m_Image(_Image), m_Rect( _Pos, _Size )
{
}


GameSprite::~GameSprite()
{
}

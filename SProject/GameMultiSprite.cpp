#include "stdafx.h"
#include "GameMultiSprite.h"


GameMultiSprite::GameMultiSprite(size_t _Num)
{
	m_MultiVec.reserve(_Num);
}


GameMultiSprite::~GameMultiSprite()
{
	for (size_t i = 0; i < m_MultiVec.size(); ++i)
	{
		delete m_MultiVec[i];
		m_MultiVec[i] = nullptr;
	}
	m_MultiVec.clear();
}

void GameMultiSprite::PushMultiSprite(GameSprite* _Sprite)
{
	m_MultiVec.push_back(_Sprite);
}

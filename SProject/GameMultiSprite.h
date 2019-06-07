#pragma once
#include "GameSprite.h"
#include <vector>


class GameMultiSprite
{
private:
	std::vector<GameSprite*> m_MultiVec;
	 

public:
	GameMultiSprite(size_t _Num);
	~GameMultiSprite();

public:
	inline GameSprite* GetSprite(size_t _Index)
	{
		return m_MultiVec[_Index];
	}

public:
	void PushMultiSprite(GameSprite* _Sprite);

};


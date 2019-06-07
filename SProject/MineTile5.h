#pragma once
#include "ActorBase.h"
#include <vector>

class TileActorRender;
class MineTile5 :
	public ActorBase
{
private:
	IPOS m_PlayerStartIndex;
	TileActorRender* m_MineTileMap;
	size_t m_Size;
	bool m_TileCheck;

public:
	std::vector<IPOS> m_RockPosVec;

public:
	MineTile5();
	~MineTile5();

public:
	TileActorRender* MineTileMap()
	{
		return m_MineTileMap;
	}
	IPOS PlayerStartIndex()
	{
		return m_PlayerStartIndex;
	}

public:
	void Init() override;
	void Update() override;
};


#pragma once
#include "ActorBase.h"
#include <vector>

class TileActorRender;
class Town2Tile :
	public ActorBase
{
private:
	IPOS m_PlayerStartIndex;
	TileActorRender* m_Town2TileMap;
	size_t m_Size;
	bool m_TileCheck;

public:
	std::vector<IPOS> m_RockPosVec;
	std::vector<IPOS> m_TreePosVec;

public:
	Town2Tile();
	~Town2Tile();

public:
	TileActorRender* Town2TileMap()
	{
		return m_Town2TileMap;
	}
	IPOS PlayerStartIndex()
	{
		return m_PlayerStartIndex;
	}

public:
	void Init() override;
	void Update() override;
};


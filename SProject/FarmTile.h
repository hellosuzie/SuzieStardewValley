#pragma once
#include "ActorBase.h"
#include "TileActorRender.h"
#include <vector>

class TileActorRender;
class FarmTile :
	public ActorBase
{
private:
	IPOS m_PlayerStartIndex;
	TileActorRender* m_FarmTileMap;
	size_t m_Size;
	bool m_TileCheck;

public:
	std::vector<IPOS> m_RockPosVec;
	std::vector<IPOS> m_TreePosVec;

public:
	FarmTile();
	~FarmTile();

public:
	TileActorRender* FarmTileMap()
	{
		return m_FarmTileMap;
	}
	IPOS PlayerStartIndex()
	{
		return m_PlayerStartIndex;
	}

public:
	void Init() override;
	void Update() override;
};


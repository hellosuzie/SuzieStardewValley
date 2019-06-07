#pragma once
#include "ActorBase.h"

class TileActorRender;
class TownTile :
	public ActorBase
{
private:
	IPOS m_PlayerStartIndex;
	TileActorRender* m_TownTileMap;
	size_t m_Size;
	bool m_TileCheck;

public:
	TownTile();
	~TownTile();

public:
	TileActorRender* TownTileMap()
	{
		return m_TownTileMap;
	}
	IPOS PlayerStartIndex()
	{
		return m_PlayerStartIndex;
	}

public:
	void Init() override;
	void Update() override;

};


#pragma once
#include "ActorBase.h"
#include <vector>

class TileActorRender;
class BarnTile :
	public ActorBase
{
private:
	IPOS m_PlayerStartIndex;
	TileActorRender* m_BarnTileMap;
	size_t m_Size;
	bool m_TileCheck;

public:
	BarnTile();
	~BarnTile();

public:
	TileActorRender* BarnTileMap()
	{
		return m_BarnTileMap;
	}
	IPOS PlayerStartIndex()
	{
		return m_PlayerStartIndex;
	}

public:
	void Init() override;
	void Update() override;
};


#pragma once
#include "ActorBase.h"
#include <vector>

class TileActorRender;
class RobinTile :
	public ActorBase
{
private:
	IPOS m_PlayerStartIndex;
	TileActorRender* m_RobinTileMap;
	size_t m_Size;
	bool m_TileCheck;

public:
	RobinTile();
	~RobinTile();

public:
	TileActorRender* RobinTileMap()
	{
		return m_RobinTileMap;
	}
	IPOS PlayerStartIndex()
	{
		return m_PlayerStartIndex;
	}

public:
	void Init() override;
	void Update() override;
};


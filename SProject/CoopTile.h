#pragma once
#include "ActorBase.h"
#include <vector>

class TileActorRender;
class CoopTile :
	public ActorBase
{
private:
	IPOS m_PlayerStartIndex;
	TileActorRender* m_CoopTileMap;
	size_t m_Size;
	bool m_TileCheck;

public:
	CoopTile();
	~CoopTile();

public:
	TileActorRender* CoopTileMap()
	{
		return m_CoopTileMap;
	}
	IPOS PlayerStartIndex()
	{
		return m_PlayerStartIndex;
	}

public:
	void Init() override;
	void Update() override;
};


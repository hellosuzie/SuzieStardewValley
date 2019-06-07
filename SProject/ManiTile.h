#pragma once
#include "ActorBase.h"
#include <vector>

class TileActorRender;
class ManiTile :
	public ActorBase
{
private:
	IPOS m_PlayerStartIndex;
	TileActorRender* m_ManiTileMap;
	size_t m_Size;
	bool m_TileCheck;

public:
	ManiTile();
	~ManiTile();

public:
	TileActorRender* FarmManiMap()
	{
		return m_ManiTileMap;
	}
	IPOS PlayerStartIndex()
	{
		return m_PlayerStartIndex;
	}

public:
	void Init() override;
	void Update() override;
};


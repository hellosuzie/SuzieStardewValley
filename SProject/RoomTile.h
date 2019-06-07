#pragma once
#include "ActorBase.h"

class TileActorRender;
class RoomTile :
	public ActorBase
{
private:
	IPOS m_PlayerStartIndex;
	TileActorRender* m_RoomTileMap;
	size_t m_Size;
	bool m_TileCheck;

public:
	RoomTile();
	~RoomTile();

public:
	TileActorRender* RoomTileMap()
	{
		return m_RoomTileMap;
	}
	IPOS PlayerStartIndex()
	{
		return m_PlayerStartIndex;
	}

public:
	void Init() override;
	void Update() override;
};


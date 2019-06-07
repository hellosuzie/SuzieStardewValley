#pragma once
#include "ActorBase.h"

class TileActorRender;
class StoreTile :
	public ActorBase
{
private:
	IPOS m_PlayerStartIndex;
	TileActorRender* m_StoreTileMap;
	size_t m_Size;
	bool m_TileCheck;

public:
	StoreTile();
	~StoreTile();

public:
	TileActorRender* StoreTileMap()
	{
		return m_StoreTileMap;
	}
	IPOS PlayerStartIndex()
	{
		return m_PlayerStartIndex;
	}

public:
	void Init() override;
	void Update() override;
};


#include "stdafx.h"
#include "Town2Tile.h"
#include "TileActorRender.h"
#include "ReadStream.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"

Town2Tile::Town2Tile() : m_TileCheck(false)
{
}


Town2Tile::~Town2Tile()
{
}

void Town2Tile::Init()
{
	m_Town2TileMap = MakeRender<TileActorRender>(1);
	m_Town2TileMap->SetTileSprite(L"TileColor.bmp", { 64, 64 });

	ReadStream NewRead = ReadStream(FILEPATH("MapData", "Town2.TileData"));

	NewRead >> m_Size;
	TileActorRender::TileData TempTileData;

	for (size_t i = 0; i < m_Size; ++i)
	{
		NewRead >> TempTileData;
		m_Town2TileMap->SetTile(TempTileData.m_Pos, TempTileData.m_SpriteIndex);
		if (2 == TempTileData.m_SpriteIndex)
		{
			m_PlayerStartIndex.X = TempTileData.m_Pos.X;
			m_PlayerStartIndex.Y = TempTileData.m_Pos.Y;
		}
	}
	for (size_t i = 0; i < m_Size; ++i)
	{
		m_Town2TileMap->Off();
	}
}

void Town2Tile::Update()
{
	if (true == ENTER.DownCondition(L"CountDebug"))
	{
		for (size_t i = 0; i < m_Size; ++i)
		{
			m_Town2TileMap->Off();
		}
		if (true == m_TileCheck)
		{
			for (size_t i = 0; i < m_Size; ++i)
			{
				m_Town2TileMap->On();
			}
			m_TileCheck = false;
			return;
		}
		m_TileCheck = true;
	}
}

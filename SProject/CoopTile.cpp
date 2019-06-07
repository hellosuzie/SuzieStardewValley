#include "stdafx.h"
#include "CoopTile.h"
#include "TileActorRender.h"
#include "ReadStream.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"

CoopTile::CoopTile() : m_TileCheck(false)
{
}


CoopTile::~CoopTile()
{
}

void CoopTile::Init()
{
	m_CoopTileMap = MakeRender<TileActorRender>(1);
	m_CoopTileMap->SetTileSprite(L"TileColor.bmp", { 64, 64 });

	ReadStream NewRead = ReadStream(FILEPATH("MapData", "Coop.TileData"));

	NewRead >> m_Size;
	TileActorRender::TileData TempTileData;

	for (size_t i = 0; i < m_Size; ++i)
	{
		NewRead >> TempTileData;
		m_CoopTileMap->SetTile(TempTileData.m_Pos, TempTileData.m_SpriteIndex);
		if (2 == TempTileData.m_SpriteIndex)
		{
			m_PlayerStartIndex.X = TempTileData.m_Pos.X;
			m_PlayerStartIndex.Y = TempTileData.m_Pos.Y;
		}
	}
	for (size_t i = 0; i < m_Size; ++i)
	{
		m_CoopTileMap->Off();
	}
}

void CoopTile::Update()
{
	if (true == ENTER.DownCondition(L"CountDebug"))
	{
		for (size_t i = 0; i < m_Size; ++i)
		{
			m_CoopTileMap->Off();
		}
		if (true == m_TileCheck)
		{
			for (size_t i = 0; i < m_Size; ++i)
			{
				m_CoopTileMap->On();
			}
			m_TileCheck = false;
			return;
		}
		m_TileCheck = true;
	}
}

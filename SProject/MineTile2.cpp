#include "stdafx.h"
#include "MineTile2.h"
#include "TileActorRender.h"
#include "ReadStream.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"

MineTile2::MineTile2() : m_TileCheck(false)
{
}


MineTile2::~MineTile2()
{
}

void MineTile2::Init()
{
	m_MineTileMap = MakeRender<TileActorRender>(1);
	m_MineTileMap->SetTileSprite(L"TileColor.bmp", { 64, 64 });

	ReadStream NewRead = ReadStream(FILEPATH("MapData", "Mine2.TileData"));

	NewRead >> m_Size;
	TileActorRender::TileData TempTileData;

	for (size_t i = 0; i < m_Size; ++i)
	{
		NewRead >> TempTileData;
		m_MineTileMap->SetTile(TempTileData.m_Pos, TempTileData.m_SpriteIndex);
		if (2 == TempTileData.m_SpriteIndex)
		{
			m_PlayerStartIndex.X = TempTileData.m_Pos.X;
			m_PlayerStartIndex.Y = TempTileData.m_Pos.Y;
		}
		if (3 == TempTileData.m_SpriteIndex)
		{
			m_RockPosVec.push_back(TempTileData.m_Pos);
		}
	}
	for (size_t i = 0; i < m_Size; ++i)
	{
		m_MineTileMap->Off();
	}
}

void MineTile2::Update()
{
	if (true == ENTER.DownCondition(L"CountDebug"))
	{
		for (size_t i = 0; i < m_Size; ++i)
		{
			m_MineTileMap->Off();
		}
		if (true == m_TileCheck)
		{
			for (size_t i = 0; i < m_Size; ++i)
			{
				m_MineTileMap->On();
			}
			m_TileCheck = false;
			return;
		}
		m_TileCheck = true;
	}
}

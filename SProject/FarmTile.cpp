#include "stdafx.h"
#include "FarmTile.h"
#include "TileActorRender.h"
#include "ReadStream.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"

FarmTile::FarmTile() : m_TileCheck(false)
{
}


FarmTile::~FarmTile()
{
}

void FarmTile::Init()
{
	m_FarmTileMap = MakeRender<TileActorRender>(1);
	m_FarmTileMap->SetTileSprite(L"TileColor.bmp", { 64, 64 });

	ReadStream NewRead = ReadStream(FILEPATH("MapData", "Farm.TileData"));

	NewRead >> m_Size;
	TileActorRender::TileData TempTileData;

	for (size_t i = 0; i < m_Size; ++i)
	{
		NewRead >> TempTileData;
		m_FarmTileMap->SetTile(TempTileData.m_Pos, TempTileData.m_SpriteIndex);

		if (2 == TempTileData.m_SpriteIndex)
		{
			m_PlayerStartIndex.X = TempTileData.m_Pos.X;
			m_PlayerStartIndex.Y = TempTileData.m_Pos.Y;
		}
		if (3 == TempTileData.m_SpriteIndex)
		{
			m_RockPosVec.push_back(TempTileData.m_Pos);
		}
		if (1 == TempTileData.m_SpriteIndex)
		{
			m_TreePosVec.push_back(TempTileData.m_Pos);
		}
	}
	for (size_t i = 0; i < m_Size; ++i)
	{
		m_FarmTileMap->Off();
	}
}

void FarmTile::Update()
{
	if (true == ENTER.DownCondition(L"CountDebug"))
	{
		for (size_t i = 0; i < m_Size; ++i)
		{
			m_FarmTileMap->Off();
		}
		if (true == m_TileCheck)
		{
			for (size_t i = 0; i < m_Size; ++i)
			{
				m_FarmTileMap->On();
			}
			m_TileCheck = false;
			return;
		}
		m_TileCheck = true;
	}
}


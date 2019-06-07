#include "stdafx.h"
#include "TileActorRender.h"
#include "ResourceMgr.h"
#include "GameMultiSprite.h"
#include "ActorBase.h"

TileActorRender::TileActorRender()
{
}


TileActorRender::~TileActorRender()
{

}

void TileActorRender::SetTileSprite(const WCHAR * _SpriteName, FPOS _TileSize)
{
	m_TileSprite = RES.FindMultiSprite(_SpriteName);
	if (nullptr == m_TileSprite)
	{
		Tassert(true);
		return;
	}
	m_Size = _TileSize;
}

size_t TileActorRender::SetTile(IPOS _Index, size_t _SpriteNum)
{
	std::map<__int64, size_t>::iterator FindIter = m_TileDataMap.find(_Index);
	//찾는 위치에 타일이 있다면 새로운 인덱스번째 타일로 바꿔주기
	if (FindIter != m_TileDataMap.end())
	{
		FindIter->second = _SpriteNum;
		return FindIter->second;
	}
	m_TileDataMap.insert(std::map<__int64, size_t>::value_type(_Index, _SpriteNum));
	return _SpriteNum;
}

size_t TileActorRender::WorldPosSetTile(FPOS _Index, int _SpriteNum)
{
	m_TilePosIndex = { (int)(_Index.X / m_Size.X),(int)( _Index.Y / m_Size.Y) };
	return SetTile(m_TilePosIndex, _SpriteNum);
}

size_t TileActorRender::FindSpriteIndex(IPOS _Index)
{
	std::map<__int64, size_t>::iterator FindIter = m_TileDataMap.find(_Index);
	if (FindIter != m_TileDataMap.end())
	{
		return FindIter->second;
	}
	return -1;
}

void TileActorRender::EraseTile(IPOS _Index)
{
	std::map<__int64, size_t>::iterator FindIter = m_TileDataMap.find(_Index);
	if (m_TileDataMap.end() == FindIter)
	{
		return;
	}

	m_TileDataMap.erase(FindIter);
	return;
}

std::vector<TileActorRender::TileData> TileActorRender::GetAllTileData()
{
	std::vector<TileActorRender::TileData> ReturnVec;
	m_StartIeter = m_TileDataMap.begin();
	m_EndIeter = m_TileDataMap.end();

	for (; m_StartIeter != m_EndIeter; ++m_StartIeter)
	{
		TileData TempTileData;
		TempTileData.m_Pos = m_StartIeter->first;
		TempTileData.m_SpriteIndex = m_StartIeter->second;
		ReturnVec.push_back(TempTileData);
	}
	return ReturnVec;
}

void TileActorRender::Clear()
{
	m_TileDataMap.clear();
}

void TileActorRender::Render()
{
	if (nullptr == m_TileSprite)
	{
		Tassert(true);
		return;
	}

	//타일까는 시작위치는 무조건 0, 0에서 시작한다.
	//부모의 피봇 안더해줬으니까
	IPOS TempTilePos;

	std::map<__int64, size_t>::iterator StartIter = m_TileDataMap.begin();
	std::map<__int64, size_t>::iterator EndIter = m_TileDataMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		TempTilePos = StartIter->first;
		TempTilePos.X = (int)(TempTilePos.X * m_Size.X);
		TempTilePos.Y = (int)(TempTilePos.Y * m_Size.Y);

		if (true == CameraMode())
		{
			TempTilePos -= Actor()->Parent()->MainCamera()->CameraPos();
		}

		GameSprite* TempTileSptrite = m_TileSprite->GetSprite(StartIter->second);

		TransparentBlt(BHDC
			, TempTilePos.X
			, TempTilePos.Y
			, (int)(m_Size.X)	
			, (int)(m_Size.Y)
			, TempTileSptrite->ImageDC()
			, TempTileSptrite->Pos().IX()
			, TempTileSptrite->Pos().IY()
			, TempTileSptrite->Size().IX()
			, TempTileSptrite->Size().IY()
			, TempTileSptrite->TransColor());
	}
}

#pragma once
#include "ActorRender.h"
#include <vector>

class GameMultiSprite;
class TileActorRender : public ActorRender
{
public:
	class TileData
	{
	public:
		IPOS m_Pos;
		size_t m_SpriteIndex;

	public:
		//Ȥ�� �𸣴ϱ� ���Կ����� ���������ֱ�
		TileData& operator = (const TileData& _Other)
		{
			m_Pos = _Other.m_Pos;
			m_SpriteIndex = _Other.m_SpriteIndex;
			return *this;
		}
	};

private:
	std::map<__int64, size_t> m_TileDataMap;
	std::map<__int64, size_t>::iterator m_StartIeter;
	std::map<__int64, size_t>::iterator m_EndIeter;

	GameMultiSprite* m_TileSprite;

private:
	IPOS m_TilePosIndex;

public:
	TileActorRender();
	~TileActorRender();

public:
	IPOS TilePosIndex()
	{
		return m_TilePosIndex;
	}

public:
	void SetTileSprite(const WCHAR* _SpriteName, FPOS _TileSize);
	size_t SetTile(IPOS _Index, size_t _SpriteNum);
	//�������� �޾Ƽ� �ε����� ����� �ű⿡ ����ִ� �Լ�.
	size_t WorldPosSetTile(FPOS _Index, int _SpriteNum);

	size_t FindSpriteIndex(IPOS _Index);
	void EraseTile(IPOS _Index);

public:
	std::vector<TileData> GetAllTileData();
	void Clear();

private:
	void Render() override;
};


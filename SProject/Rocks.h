#pragma once
#include "ActorBase.h"

class AniActorRender;
class Rocks :
	public ActorBase
{
public:
	enum RockState
	{
		Rockone,
		Rocktwo,
		Emerald,
		Aquamarine,
		Ruby,
		Topaz,
		Diamond,
		Stonemax
	};

private:
	AniActorRender* m_RockAni;
	RockState m_CurRockState;

public:
	std::wstring ArrCropName[Stonemax];

public:
	Rocks();
	~Rocks();

public:
	AniActorRender* RockAniRender()
	{
		return m_RockAni;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

private:
	void MakeRockAni();
};


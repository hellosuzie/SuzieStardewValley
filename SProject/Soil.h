#pragma once
#include "ActorBase.h"

class AniActorRender;
class Soil :
	public ActorBase
{
private:
	AniActorRender* m_SoilAni;

public:
	Soil();
	~Soil();

public:
	AniActorRender* SoilAni()
	{
		return m_SoilAni;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

private:
	void MakeSoilAni();
};


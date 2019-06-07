#pragma once
#include "ActorBase.h"

class AniActorRender;
class Crops :
	public ActorBase
{
private:
	AniActorRender* m_CropsAni;

public:
	Crops();
	~Crops();

public:
	AniActorRender* CropsAni()
	{
		return m_CropsAni;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

private:
	void MakeCropAnimation();
};


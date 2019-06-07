#pragma once
#include "ActorBase.h"

class AniActorRender;
class WaterEffect :
	public ActorBase
{
private:
	AniActorRender* m_WaterEffectRender;

public:
	WaterEffect();
	~WaterEffect();

public:
	AniActorRender* WaterEffectRender()
	{
		return m_WaterEffectRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

};


#pragma once
#include "ActorBase.h"

class AniActorRender;
class RockEffect :
	public ActorBase
{
private:
	AniActorRender* m_RockEffectRender;
	float m_AlphaTime;

public:
	RockEffect();
	~RockEffect();

public:
	AniActorRender* RockEffectRender()
	{
		return m_RockEffectRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


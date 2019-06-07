#pragma once
#include "ActorBase.h"

class AniActorRender;
class RockBoomEffect :
	public ActorBase
{
private:
	AniActorRender* m_RockBoomEffectRender;

public:
	RockBoomEffect();
	~RockBoomEffect();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


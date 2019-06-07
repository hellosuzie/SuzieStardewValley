#pragma once
#include "ActorBase.h"

class AniActorRender;
class RainbowEffect :
	public ActorBase
{
private:
	AniActorRender* m_RainbowEffectRender;

public:
	RainbowEffect();
	~RainbowEffect();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


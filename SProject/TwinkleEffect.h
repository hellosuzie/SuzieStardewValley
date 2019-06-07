#pragma once
#include "ActorBase.h"

class AniActorRender;
class TwinkleEffect :
	public ActorBase
{
private:
	AniActorRender* m_TwinkleEffectRender;

public:
	TwinkleEffect();
	~TwinkleEffect();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


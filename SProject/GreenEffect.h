#pragma once
#include "ActorBase.h"

class AniActorRender;
class GreenEffect :
	public ActorBase
{
private:
	AniActorRender* m_GreenEffectRender;

public:
	GreenEffect();
	~GreenEffect();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


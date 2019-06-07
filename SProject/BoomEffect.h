#pragma once
#include "ActorBase.h"

class AniActorRender;
class BoomEffect :
	public ActorBase
{
private:
	AniActorRender* m_BoomEffectRender;

public:
	BoomEffect();
	~BoomEffect();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


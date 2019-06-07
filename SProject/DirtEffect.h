#pragma once
#include "ActorBase.h"

class AniActorRender;
class DirtEffect :
	public ActorBase
{
private:
	AniActorRender* m_DirtEffectRender;

public:
	DirtEffect();
	~DirtEffect();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


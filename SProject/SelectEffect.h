#pragma once
#include "ActorBase.h"

class AniActorRender;
class SelectEffect :
	public ActorBase
{
private:
	AniActorRender* m_SelectEffectRender;

public:
	SelectEffect();
	~SelectEffect();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


#pragma once
#include "ActorBase.h"

class AniActorRender;
class BubbleEffect :
	public ActorBase
{
private:
	AniActorRender* m_BubbleEffectRender;

public:
	BubbleEffect();
	~BubbleEffect();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


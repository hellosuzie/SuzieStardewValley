#pragma once
#include "ActorBase.h"
#include "TimeHelper.h"

class SingleActorRender;
class Fade :
	public ActorBase
{
private:
	SingleActorRender* m_FadeRedner;
	float m_AlphaTime;

	TimeHelper m_DTimer;

public:
	Fade();
	~Fade();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


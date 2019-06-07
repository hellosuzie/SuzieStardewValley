#pragma once
#include "ActorBase.h"
#include "TimeHelper.h"

class SingleActorRender;
class Final :
	public ActorBase
{
private:
	SingleActorRender* m_FinalRedner;
	float m_AlphaTime;

	TimeHelper m_DTimer;

public:
	Final();
	~Final();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


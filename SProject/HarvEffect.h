#pragma once
#include "ActorBase.h"

class SingleActorRender;
class HarvEffect :
	public ActorBase
{
private:
	SingleActorRender* m_HarvRender;
	float Time;

public:
	HarvEffect();
	~HarvEffect();

public:
	SingleActorRender* HarvRender()
	{
		return m_HarvRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


#pragma once
#include "ActorBase.h"
#include "TimeHelper.h"

class SingleActorRender;
class Brighten :
	public ActorBase
{
private:
	SingleActorRender* m_BrightRedner;
	float m_AlphaTime;

	TimeHelper m_DTimer;

public:
	Brighten();
	~Brighten();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


#pragma once
#include "ActorBase.h"

class SingleActorRender;
class Clock :
	public ActorBase
{
public:
	static SingleActorRender* m_ClockRender;

public:
	Clock();
	~Clock();

public:
	SingleActorRender* ClockRender()
	{
		return m_ClockRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


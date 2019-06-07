#pragma once
#include "ActorBase.h"

class SingleActorRender;
class FullAlarm :
	public ActorBase
{
private:
	SingleActorRender* m_AlarmRender;
	float m_Time;

public:
	FullAlarm();
	~FullAlarm();

public:
	SingleActorRender* AlarmRender()
	{
		return m_AlarmRender;
	}

public:
	void Init();
	void PrevUpdate();
	void Update();
	void LaterUpdate();
};


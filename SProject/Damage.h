#pragma once
#include "ActorBase.h"

class SingleActorRender;
class Damage :
	public ActorBase
{
private:
	SingleActorRender* m_PlayerDamageRender;
	float m_Time;

public:
	Damage();
	~Damage();

public:
	SingleActorRender* PlayerDamageRender()
	{
		return m_PlayerDamageRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


#pragma once
#include "ActorBase.h"

class SingleActorRender;
class MonsterDamage :
	public ActorBase
{
private:
	SingleActorRender* m_MonsterDamageRender;
	float m_Time;

public:
	MonsterDamage();
	~MonsterDamage();

public:
	SingleActorRender* MonsterDamageRender()
	{
		return m_MonsterDamageRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


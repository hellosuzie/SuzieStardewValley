#pragma once
#include "ActorBase.h"

class SingleActorRender;
class Town2Back :	public ActorBase
{
private:
	SingleActorRender* m_Town2Back;

public:
	Town2Back();
	~Town2Back();

public:
	SingleActorRender* GetTown2Back()
	{
		return m_Town2Back;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


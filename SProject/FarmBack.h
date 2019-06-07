#pragma once
#include "ActorBase.h"

class SingleActorRender;
class FarmBack :	public ActorBase
{
public:
	static SingleActorRender* m_FarmBack;

public:
	FarmBack();
	~FarmBack();

public:
	SingleActorRender* GetFarmBack()
	{
		return m_FarmBack;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


#pragma once
#include "ActorBase.h"

class SingleActorRender;
class CoopBack :	public ActorBase
{
private:
	SingleActorRender* m_CoopBack;

public:
	CoopBack();
	~CoopBack();

public:
	SingleActorRender* GetCoopBack()
	{
		return m_CoopBack;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


#pragma once
#include "ActorBase.h"

class SingleActorRender;
class BarnBack :	public ActorBase
{
private:
	SingleActorRender* m_BarnBack;

public:
	BarnBack();
	~BarnBack();

public:
	SingleActorRender* GetBarnBack()
	{
		return m_BarnBack;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


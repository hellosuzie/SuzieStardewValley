#pragma once
#include "ActorBase.h"

class SingleActorRender;
class RobinBack :	public ActorBase
{
private:
	SingleActorRender* m_RobinBack;

public:
	RobinBack();
	~RobinBack();

public:
	SingleActorRender* GetRobinBack()
	{
		return m_RobinBack;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


#pragma once
#include "ActorBase.h"

class SingleActorRender;
class CoopRender :
	public ActorBase
{
private:
	SingleActorRender* m_CoopRender;

public:
	CoopRender();
	~CoopRender();

public:
	void Init() override;
};


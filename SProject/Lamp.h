#pragma once
#include "ActorBase.h"

class SingleActorRender;
class Lamp :
	public ActorBase
{
private:
	SingleActorRender* m_LampRender;

public:
	Lamp();
	~Lamp();

public:
	void Init() override;
};


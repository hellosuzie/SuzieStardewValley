#pragma once
#include "ActorBase.h"

class SingleActorRender;
class BarnRender :
	public ActorBase
{
private:
	SingleActorRender* m_BarnRender;

public:
	BarnRender();
	~BarnRender();

public:
	void Init() override;
};


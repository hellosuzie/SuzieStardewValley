#pragma once
#include "ActorBase.h"

class SingleActorRender;
class SecondCloud :
	public ActorBase
{
private:
	SingleActorRender* m_CloudTwo;

public:
	SecondCloud();
	~SecondCloud();

public:
	void Init() override;
	void Update() override;

};


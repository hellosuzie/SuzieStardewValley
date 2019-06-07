#pragma once
#include "ActorBase.h"

class SingleActorRender;
class Sleeping :
	public ActorBase
{
private:
	SingleActorRender* m_SleepBack;
	SingleActorRender* m_Yes;
	SingleActorRender* m_No;

public:
	Sleeping();
	~Sleeping();

public:
	void Init() override;

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


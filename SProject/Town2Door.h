#pragma once
#include "ActorBase.h"
class Town2Door :
	public ActorBase
{
public:
	Town2Door();
	~Town2Door();

public:
	void Init() override;

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


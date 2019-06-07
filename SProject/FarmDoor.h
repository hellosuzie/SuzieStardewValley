#pragma once
#include "ActorBase.h"
class FarmDoor :
	public ActorBase
{
public:
	FarmDoor();
	~FarmDoor();

public:
	void Init() override;

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


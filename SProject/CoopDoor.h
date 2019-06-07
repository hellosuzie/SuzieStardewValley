#pragma once
#include "ActorBase.h"
class CoopDoor :
	public ActorBase
{
public:
	CoopDoor();
	~CoopDoor();

public:
	void Init() override;

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


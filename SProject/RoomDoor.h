#pragma once
#include "ActorBase.h"
class RoomDoor :
	public ActorBase
{
public:
	RoomDoor();
	~RoomDoor();

public:
	void Init() override;

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


#pragma once
#include "ActorBase.h"
class TownDoor :
	public ActorBase
{
public:
	static bool UpDownCheck;

public:
	TownDoor();
	~TownDoor();

public:
	void Init() override;

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


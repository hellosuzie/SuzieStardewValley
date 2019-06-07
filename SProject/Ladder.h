#pragma once
#include "ActorBase.h"

class SingleActorRender;
class Ladder :
	public ActorBase
{
private:
	SingleActorRender* m_LadderRender;

public:
	int m_Count;

public:
	Ladder();
	~Ladder();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


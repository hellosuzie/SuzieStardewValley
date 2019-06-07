#pragma once
#include "ActorBase.h"

class Sleeping;
class SingleActorRender;
class RoomBed :	public ActorBase
{
public:
	static Sleeping* m_Sl;

private:
	SingleActorRender* m_RoomBedTop;
	SingleActorRender* m_RoomBedBot;

public:
	RoomBed();
	~RoomBed();

public:
	void Init() override;
	void OtherCollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void OtherCollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void OtherCollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


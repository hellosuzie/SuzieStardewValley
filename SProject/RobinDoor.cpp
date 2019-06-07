#include "stdafx.h"
#include "RobinDoor.h"
#include "ActorCollision.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "Fade.h"

RobinDoor::RobinDoor()
{
}


RobinDoor::~RobinDoor()
{
}

void RobinDoor::Init()
{
	ActorCollision* m_RobinToTown2 = MakeCollision(L"Door", { 100, 30 }, 1);
	m_RobinToTown2->Actor()->Pos({ 730, 850 });
}

void RobinDoor::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void RobinDoor::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		CORE.ChangeState(ALLSTATE::TOWN2);
		Fade* F = Parent()->MakeActor<Fade>();
	}
}

void RobinDoor::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

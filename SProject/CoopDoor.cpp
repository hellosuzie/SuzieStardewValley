#include "stdafx.h"
#include "CoopDoor.h"
#include "ActorCollision.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "Fade.h"

CoopDoor::CoopDoor()
{
}


CoopDoor::~CoopDoor()
{
}

void CoopDoor::Init()
{
	ActorCollision* m_CoopToFarm = MakeCollision(L"Door", { 100, 30 }, 1);
	m_CoopToFarm->Actor()->Pos({ 355, 850 });
}

void CoopDoor::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void CoopDoor::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		CORE.ChangeState(ALLSTATE::FARM);
		Fade* F = Parent()->MakeActor<Fade>();
	}
}

void CoopDoor::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

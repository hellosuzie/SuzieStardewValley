#include "stdafx.h"
#include "MineDoor.h"
#include "EnterMgr.h"
#include "SCore.h"
#include "ActorCollision.h"
#include "Fade.h"

MineDoor::MineDoor()
{
}


MineDoor::~MineDoor()
{
}


void MineDoor::Init()
{
	ActorCollision* MineToTown = MakeCollision(L"Door", { 64, 30 }, 1);
	MineToTown->Pivot({ 290, 250 });
}

void MineDoor::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void MineDoor::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		CORE.ChangeState(ALLSTATE::TOWN);
		Fade* F = Parent()->MakeActor<Fade>();
	}
}

void MineDoor::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}
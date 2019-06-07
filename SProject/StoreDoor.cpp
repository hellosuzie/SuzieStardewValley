#include "stdafx.h"
#include "StoreDoor.h"
#include "EnterMgr.h"
#include "SCore.h"
#include "ActorCollision.h"
#include "Fade.h"

StoreDoor::StoreDoor()
{
}


StoreDoor::~StoreDoor()
{
}


void StoreDoor::Init()
{
	ActorCollision* StoreToTown = MakeCollision(L"Door", { 125, 30 }, 1);
	StoreToTown->Pivot({ 280, 1120 });
}

void StoreDoor::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void StoreDoor::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		CORE.ChangeState(ALLSTATE::TOWN);
		Fade* F = Parent()->MakeActor<Fade>();
	}
}

void StoreDoor::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

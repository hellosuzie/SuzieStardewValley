#include "stdafx.h"
#include "FarmDoor.h"
#include "ActorCollision.h"
#include "EnterMgr.h"
#include "SCore.h"
#include "Fade.h"

FarmDoor::FarmDoor()
{
}


FarmDoor::~FarmDoor()
{
}

void FarmDoor::Init()
{
	ActorCollision* FarmToRoom = MakeCollision(L"Door", { 64, 30 }, 1);
	FarmToRoom->Pivot({ 1700, 970 });
	ActorCollision* FarmToTown = MakeCollision(L"Door", { 30, 120 }, 2);
	FarmToTown->Pivot({ 2160, 1200});
	ActorCollision* FarmToCoop = MakeCollision(L"Door", { 120, 30 }, 3);
	FarmToCoop->Pivot({ 896, 1000 });
	ActorCollision* FarmToBarn = MakeCollision(L"Door", { 120, 30 }, 4);
	FarmToBarn->Pivot({ 400, 1000 });
}

void FarmDoor::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void FarmDoor::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (1 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::ROOM);
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
	if (2 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::TOWN);
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
	if (3 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::COOP);
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
	if (4 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::BARN);
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
}

void FarmDoor::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

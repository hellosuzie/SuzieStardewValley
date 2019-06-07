#include "stdafx.h"
#include "TownDoor.h"
#include "EnterMgr.h"
#include "SCore.h"
#include "ActorCollision.h"
#include "Fade.h"

bool TownDoor::UpDownCheck = true;

TownDoor::TownDoor()
{
}


TownDoor::~TownDoor()
{
}


void TownDoor::Init()
{
	ActorCollision* TownToMine = MakeCollision(L"Door", { 64, 30 }, 1);
	TownToMine->Pivot({ 480, 267 });
	ActorCollision* TownToFarm = MakeCollision(L"Door", { 100, 160 }, 2);
	TownToFarm->Pivot({ 20, 800 });
	ActorCollision* TownToStore = MakeCollision(L"Door", { 120, 30 }, 3);
	TownToStore->Pivot({ 1840, 755 });
	ActorCollision* TownToTown2 = MakeCollision(L"Door", { 80, 100 }, 4);
	TownToTown2->Pivot({ 2520, 800 });
	ActorCollision* TownToTown2Down = MakeCollision(L"Door", { 100, 80 }, 5);
	TownToTown2Down->Pivot({ 2520, 1600 });
	ActorCollision* TownToMani = MakeCollision(L"Door", { 100, 80 }, 6);
	TownToMani->Pivot({ 2100, 1500 });
}

void TownDoor::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void TownDoor::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (1 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::MINE);
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
	if (2 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::FARM);
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
	if (3 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::STORE);
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
	if (4 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::TOWN2);
			UpDownCheck = true;
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}	
	if (5 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::TOWN2);
			UpDownCheck = false;
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
	if (6 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::MANI);
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
}

void TownDoor::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}
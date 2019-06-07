#include "stdafx.h"
#include "Town2Door.h"
#include "ActorCollision.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "Fade.h"
#include "TownDoor.h"

Town2Door::Town2Door()
{
}


Town2Door::~Town2Door()
{
}

void Town2Door::Init()
{
	ActorCollision* m_Town2ToTownDown = MakeCollision(L"Door", { 100, 50 }, 0);
	m_Town2ToTownDown->Pivot({ 20, 1600 });
	ActorCollision* m_Town2ToTown = MakeCollision(L"Door", { 100, 50 }, 1);
	m_Town2ToTown->Pivot({ 20, 860 });
	ActorCollision* m_Town2ToRobin = MakeCollision(L"Door", { 100, 50 }, 2);
	m_Town2ToRobin->Pivot({ 1050, 810 });
}

void Town2Door::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void Town2Door::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (0 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::TOWN);
			TownDoor::UpDownCheck = false;
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
	if (1 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::TOWN);
			TownDoor::UpDownCheck = true;
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
	if (2 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::ROBIN);
			Fade* F = Parent()->MakeActor<Fade>();
		}
	}
}

void Town2Door::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

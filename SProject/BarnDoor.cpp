#include "stdafx.h"
#include "BarnDoor.h"
#include "ActorCollision.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "Fade.h"

BarnDoor::BarnDoor()
{
}


BarnDoor::~BarnDoor()
{
}

void BarnDoor::Init()
{
	ActorCollision* m_BarnToFarm = MakeCollision(L"Door", { 100, 30 }, 1);
	m_BarnToFarm->Actor()->Pos({ 355, 850 });
}

void BarnDoor::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void BarnDoor::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		CORE.ChangeState(ALLSTATE::FARM);
		Fade* F = Parent()->MakeActor<Fade>();
	}
}

void BarnDoor::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

#include "stdafx.h"
#include "ManiDoor.h"
#include "ActorCollision.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "Fade.h"

ManiDoor::ManiDoor()
{
}


ManiDoor::~ManiDoor()
{
}

void ManiDoor::Init()
{
	ActorCollision* m_ManiToTown = MakeCollision(L"Door", { 100, 30 }, 1);
	m_ManiToTown->Actor()->Pos({ 740, 850 });
}

void ManiDoor::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void ManiDoor::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		CORE.ChangeState(ALLSTATE::TOWN);
		Fade* F = Parent()->MakeActor<Fade>();
	}
}

void ManiDoor::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

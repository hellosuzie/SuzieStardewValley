#include "stdafx.h"
#include "RoomDoor.h"
#include "ActorCollision.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "Fade.h"

RoomDoor::RoomDoor()
{
}


RoomDoor::~RoomDoor()
{
}

void RoomDoor::Init()
{
	ActorCollision* m_RoomToFarm = MakeCollision(L"Door", { 100, 30 }, 1);
	m_RoomToFarm->Actor()->Pos({ 355, 850 });
}

void RoomDoor::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void RoomDoor::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		CORE.ChangeState(ALLSTATE::FARM);
		Fade* F = Parent()->MakeActor<Fade>();
	}
}

void RoomDoor::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

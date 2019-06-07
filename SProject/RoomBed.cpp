#include "stdafx.h"
#include "RoomBed.h"
#include "SingleActorRender.h"
#include "ActorCollision.h"
#include "EnterMgr.h"
#include "Sleeping.h"

Sleeping* RoomBed::m_Sl = nullptr;

RoomBed::RoomBed()
{
	Pos({ 800, 600 });
}


RoomBed::~RoomBed()
{
}

void RoomBed::Init()
{
	m_RoomBedTop = MakeRender<SingleActorRender>(10);
	m_RoomBedTop->SetSprite(L"BedTop.bmp");
	m_RoomBedTop->Size({ 192, 128 });

	m_RoomBedBot = MakeRender<SingleActorRender>(11);
	m_RoomBedBot->SetSprite(L"BedBot.bmp");
	m_RoomBedBot->Size({ 192, 192 });
	m_RoomBedBot->Pivot({ 0, 100 });

	ActorCollision* BedTopColl = MakeCollision(L"RoomActor", { 192, 128 });
}

void RoomBed::OtherCollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void RoomBed::OtherCollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		m_Sl = Parent()->MakeActor<Sleeping>();
	}
}

void RoomBed::OtherCollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

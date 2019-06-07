#include "stdafx.h"
#include "Sleeping.h"
#include "SingleActorRender.h"
#include "ActorCollision.h"
#include "EnterMgr.h"
#include "RoomBed.h"

Sleeping::Sleeping()
{
	Pos({ WINSIZEXH, WINSIZEYH });
}


Sleeping::~Sleeping()
{
}

void Sleeping::Init()
{
	m_SleepBack = MakeRender<SingleActorRender>(28);
	m_SleepBack->SetSprite(L"SleepBack.bmp");
	m_SleepBack->Size({ 700, 250 });
	m_SleepBack->Pivot({ 0, 180 });
	m_SleepBack->CameraMode(false);

	m_Yes = MakeRender<SingleActorRender>(29);
	m_Yes->SetSprite(L"Sleep.bmp", 0);
	m_Yes->Size({ 613, 50 });
	m_Yes->Pivot({ 0, 162 });
	m_Yes->CameraMode(false);

	ActorCollision* YesColl = MakeCollision(L"Sleep", { 600, 40 }, 0);
	YesColl->Pivot({ 0, 162 });

	m_No = MakeRender<SingleActorRender>(29);
	m_No->SetSprite(L"Sleep.bmp", 1);
	m_No->Size({ 613, 50 });
	m_No->Pivot({ 0, 217 });
	m_No->CameraMode(false);

	ActorCollision* NoColl = MakeCollision(L"Sleep", { 600, 40 }, 1);
	NoColl->Pivot({ 0, 217 });

}

void Sleeping::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
	if (0 == _This->CollNum())
	{
		m_Yes->SetSprite(L"SleepSelect.bmp", 0);
	}
	if (1 == _This->CollNum())
	{
		m_No->SetSprite(L"SleepSelect.bmp", 1);
	}
}

void Sleeping::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (0 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			CORE.ChangeState(ALLSTATE::END);
		}
	}
	if (1 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			RoomBed::m_Sl->Off();
		}
	}
}

void Sleeping::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
	if (0 == _This->CollNum())
	{
		m_Yes->SetSprite(L"Sleep.bmp", 0);
	}
	if (1 == _This->CollNum())
	{
		m_No->SetSprite(L"Sleep.bmp", 1);
	}
}

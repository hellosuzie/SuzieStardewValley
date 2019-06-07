#include "stdafx.h"
#include "Marlon.h"
#include "SingleActorRender.h"
#include "ActorCollision.h"
#include "EnterMgr.h"
#include "TownStoreMenu.h"
#include "Player.h"
#include "SecondNumberActor.h"	

bool Marlon::m_StoreOpen = false;

Marlon::Marlon()
{
	Pos({ 600, 280 });
}


Marlon::~Marlon()
{
}

void Marlon::Init()
{
	m_Marlon = MakeRender<SingleActorRender>(3);
	m_Marlon->Size({ 64, 128 });
	m_Marlon->SetSprite(L"Marlon.bmp");

	MakeCollision(L"StoreMan", { 64, 200 });
}

void Marlon::PrevUpdate()
{
}

void Marlon::Update()
{
}

void Marlon::LaterUpdate()
{
}

void Marlon::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void Marlon::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		if (false == m_StoreOpen)
		{
			m_TownStoreMenu = Parent()->MakeActor<TownStoreMenu>();
			m_TownStoreMenu->CameraMode(false);
			Player::CurPlayer->OpenMainInven();
			Player::CurPlayer->m_NActor2->Pos({ 645, 134 });
			Player::CurPlayer->m_NActor2->On();
			m_StoreOpen = true;
			return;
		}
		if (true == m_StoreOpen)
		{
			Player::CurPlayer->CloseMainInven();
			m_TownStoreMenu->Off();
			Player::CurPlayer->m_NActor2->Off();
			m_StoreOpen = false;
		}
	}
}

void Marlon::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

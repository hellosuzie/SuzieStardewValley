#include "stdafx.h"
#include "Mani.h"
#include "SingleActorRender.h"
#include "ActorCollision.h"
#include "EnterMgr.h"
#include "AnimalStoreMenu.h"
#include "Player.h"
#include "MainInButton.h"
#include "ItemMgr.h"
#include "NumberActor.h"
#include "SecondNumberActor.h"

bool Mani::m_StoreOpen = false;

Mani::Mani()
{
	Pos({ 480, 460 });
}


Mani::~Mani()
{
}

void Mani::Init()
{
	MakeCollision(L"StoreMan", { 64, 200 });
}

void Mani::PrevUpdate()
{
}

void Mani::Update()
{
}

void Mani::LaterUpdate()
{
}

void Mani::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void Mani::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		if (false == m_StoreOpen)
		{
			m_AStoreMenu = Parent()->MakeActor<AnimalStoreMenu>();
			m_AStoreMenu->CameraMode(false);
			m_StoreOpen = true;
			Player::CurPlayer->m_NActor2->On();
			Player::CurPlayer->m_NActor2->Pos({ 553, 130 });
			return;
		}
		if (true == m_StoreOpen)
		{
			m_AStoreMenu->Off();
			m_StoreOpen = false;
			Player::CurPlayer->m_NActor2->Off();
		}
	}
}

void Mani::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

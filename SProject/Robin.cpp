#include "stdafx.h"
#include "Robin.h"
#include "SingleActorRender.h"
#include "ActorCollision.h"
#include "EnterMgr.h"
#include "CoopStoreMenu.h"
#include "Player.h"
#include "MainInButton.h"
#include "ItemMgr.h"
#include "NumberActor.h"
#include "SecondNumberActor.h"

bool Robin::m_StoreOpen = false;

Robin::Robin()
{
	Pos({ 678, 460 });
}


Robin::~Robin()
{
}

void Robin::Init()
{
	MakeCollision(L"StoreMan", { 64, 200 });
}

void Robin::PrevUpdate()
{
}

void Robin::Update()
{
}

void Robin::LaterUpdate()
{
}

void Robin::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void Robin::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		if (false == m_StoreOpen)
		{
			m_CStoreMenu = Parent()->MakeActor<CoopStoreMenu>();
			m_CStoreMenu->CameraMode(false);
			m_StoreOpen = true;
			Player::CurPlayer->m_NActor2->On();
			Player::CurPlayer->m_NActor2->Pos({ 665, 218 });
			return;
		}
		if (true == m_StoreOpen)
		{
			m_CStoreMenu->Off();
			m_StoreOpen = false;
			Player::CurPlayer->m_NActor2->Off();
		}
	}
}

void Robin::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

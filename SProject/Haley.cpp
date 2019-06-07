#include "stdafx.h"
#include "Haley.h"
#include "SingleActorRender.h"
#include "ActorCollision.h"
#include "EnterMgr.h"
#include "StoreMenu.h"
#include "Player.h"
#include "MainInButton.h"
#include "ItemMgr.h"
#include "NumberActor.h"
#include "SecondNumberActor.h"
#include "ResourceMgr.h"
#include "SoundPlayer.h"

bool Haley::m_StoreOpen = false;

Haley::Haley()
{
	Pos({ 480, 260 });
}


Haley::~Haley()
{
}

void Haley::Init()
{
	HaleySp = GETSOUND;

	m_Haley = MakeRender<SingleActorRender>(3);
	m_Haley->Size({ 64, 128 });
	m_Haley->SetSprite(L"Haley.bmp");

	MakeCollision(L"StoreMan", { 64, 200 });
}

void Haley::PrevUpdate()
{
}

void Haley::Update()
{
	if (nullptr != m_StoreMenu && true == m_StoreOpen)
	{
		if (true == ENTER.DownCondition(L"Action"))
		{
			SellItem(MainInButton::m_InvenCount);
		}
	}
}

void Haley::LaterUpdate()
{
}

void Haley::SellItem(size_t _InvenCount)
{
	ItemMgr::ItemInfo* TestItem = Player::CurPlayer->ReturnItemInfo(_InvenCount);
	if (nullptr == TestItem)
	{
		return;
	}
	if (true == Player::CurPlayer->IncreasePlayerMoney(TestItem->m_Price))
	{
		HaleySp->NewSoundPlay(L"Money.wav");
		Player::CurPlayer->RemoveItem(_InvenCount);
	}
}

void Haley::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void Haley::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (true == ENTER.DownCondition(L"Enter"))
	{
		if (false == m_StoreOpen)
		{
			m_StoreMenu = Parent()->MakeActor<StoreMenu>();
			m_StoreMenu->CameraMode(false);
			Player::CurPlayer->OpenMainInven();
			m_StoreOpen = true;
			Player::CurPlayer->m_NActor2->Pos({ 645, 134 });
			Player::CurPlayer->m_NActor2->On();
			return;
		}
		if (true == m_StoreOpen)
		{
			Player::CurPlayer->CloseMainInven();
			m_StoreMenu->Off();
			m_StoreOpen = false;
			Player::CurPlayer->m_NActor2->Off();
		}
	}
}

void Haley::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

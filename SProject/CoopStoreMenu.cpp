#include "stdafx.h"
#include "CoopStoreMenu.h"
#include "SingleActorRender.h"
#include "SCore.h"
#include "ActorCollision.h"
#include "EnterMgr.h"
#include "Player.h"
#include "ItemMgr.h"
#include "Mani.h"
#include "SecondNumberActor.h"
#include "FarmBack.h"
#include "FarmState.h"
#include "CoopRender.h"
#include "BarnRender.h"
#include "SoundPlayer.h"
#include "ResourceMgr.h"

int CoopStoreMenu::StoreNum = 0;
bool CoopStoreMenu::CoopCheck = false;
bool CoopStoreMenu::BarnCheck = false;
bool CoopStoreMenu::PageCheck = false;

CoopStoreMenu::CoopStoreMenu()
{
	Pos({ WINSIZEXH, WINSIZEYH });
	StoreNum = 0;
}

CoopStoreMenu::~CoopStoreMenu()
{
}

void CoopStoreMenu::Init()
{
	CoopStoreSp = GETSOUND;

	m_StoreFadeRender = MakeRender<SingleActorRender>(19);
	m_StoreFadeRender->SetSprite(L"StateChange.bmp");
	m_StoreFadeRender->SetAlpha(220);
	m_StoreFadeRender->Size({ WINSIZEX, WINSIZEY });
	m_StoreFadeRender->CameraMode(false);

	m_CoopStoreMenuRender = MakeRender<SingleActorRender>(26);
	m_CoopStoreMenuRender->SetSprite(L"CoopStoreMenu.bmp");
	m_CoopStoreMenuRender->Size({ 740, 437 });
	m_CoopStoreMenuRender->CameraMode(false);
	m_CoopStoreMenuRender->Pivot({ 22, -10 });

	//OK, Cancle
	m_OkRender = MakeRender<SingleActorRender>(26);
	m_OkRender->SetSprite(L"Ok.bmp", 0);
	m_OkRender->Size({ 45, 45 });
	m_OkRender->Pivot({ 335, -250 });
	m_OkRender->CameraMode(false);

	m_OkColl = MakeCollision(L"StoreButton", { 45, 45 }, 7);
	m_OkColl->Pivot({ 336, -243 });

	m_CancleRender = MakeRender<SingleActorRender>(26);
	m_CancleRender->SetSprite(L"Ok.bmp", 1);
	m_CancleRender->Size({ 45, 45 });
	m_CancleRender->Pivot({ 380, -250 });
	m_CancleRender->CameraMode(false);

	m_CancleColl = MakeCollision(L"StoreButton", { 45, 45 }, 8);
	m_CancleColl->Pivot({ 381, -243 });

	m_BulidRender = MakeRender<SingleActorRender>(26);
	m_BulidRender->SetSprite(L"SelectBuild.bmp", 0);
	m_BulidRender->Size({ 45, 45 });
	m_BulidRender->Pivot({ -WINSIZEXH + 771, -WINSIZEYH + 523 });
	m_BulidRender->CameraMode(false);

	m_BulidColl = MakeCollision(L"StoreButton", { 45, 45 }, 0);
	m_BulidColl->Pivot({ -WINSIZEXH + 771, -WINSIZEYH + 523 });

	m_HorizenArrow = MakeRender<SingleActorRender>(26);
	m_HorizenArrow->SetSprite(L"HorizenArrow.bmp", 0);
	m_HorizenArrow->Size({ 44, 40 });
	m_HorizenArrow->Pivot({ 375, 165 });
	m_HorizenArrow->CameraMode(false);

	m_HorizenArrowColl = MakeCollision(L"StoreButton", { 44, 40 }, 1);
	m_HorizenArrowColl->Pivot({ 376, 167 });

}

void CoopStoreMenu::PrevUpdate()
{
}

void CoopStoreMenu::Update()
{
}

void CoopStoreMenu::LaterUpdate()
{
}

void CoopStoreMenu::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
	if (7 == _This->CollNum())
	{
		m_OkRender->SetSprite(L"SelectOk.bmp", 0);
	}
	if (8 == _This->CollNum())
	{
		m_CancleRender->SetSprite(L"SelectOk.bmp", 1);
	}
	if (0 == _This->CollNum())
	{
		m_BulidRender->SetSprite(L"SelectBuild.bmp", 1);
	}	
	if (1 == _This->CollNum())
	{
		m_HorizenArrow->SetSprite(L"HorizenArrow.bmp", 1);
	}
}

void CoopStoreMenu::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (7 == _This->CollNum() || 8 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			Player::CurPlayer->CloseMainInven();
			this->Off();
			Mani::m_StoreOpen = false;
			Player::CurPlayer->m_NActor2->Off();
		}
	}
	if (0 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			if (false == CoopStoreMenu::PageCheck)
			{
				if (true == Player::CurPlayer->ReducePlayerMoney(4000))
				{
					CoopStoreSp->NewSoundPlay(L"Build.wav");

					FarmState::CRender->On();
					CoopStoreMenu::CoopCheck = true;
				}
			}
			else
			{
				if (true == Player::CurPlayer->ReducePlayerMoney(6000))
				{
					CoopStoreSp->NewSoundPlay(L"Build.wav");
					CoopStoreMenu::BarnCheck = true;
					FarmState::BRender->On();
				}
			}
		}
	}
	if (1 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			m_CoopStoreMenuRender->SetSprite(L"BarnStoreMenu.bmp");
			CoopStoreMenu::PageCheck = true;
		}
	}
}

void CoopStoreMenu::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
	if (7 == _This->CollNum())
	{
		m_OkRender->SetSprite(L"Ok.bmp", 0);
	}
	if (8 == _This->CollNum())
	{
		m_CancleRender->SetSprite(L"Ok.bmp", 1);
	}
	if (0 == _This->CollNum())
	{
		m_BulidRender->SetSprite(L"SelectBuild.bmp", 0);
	}
	if (1 == _This->CollNum())
	{
		m_HorizenArrow->SetSprite(L"HorizenArrow.bmp", 0);
	}
}

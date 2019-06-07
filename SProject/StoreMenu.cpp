#include "stdafx.h"
#include "StoreMenu.h"
#include "SingleActorRender.h"
#include "SCore.h"
#include "ActorCollision.h"
#include "EnterMgr.h"
#include "Player.h"
#include "ItemMgr.h"
#include "Haley.h"
#include "SecondNumberActor.h"

//인벤토리 다 차면 돈 안줄어들게 하기
//돈 0이 되면 못사게 하기

int StoreMenu::StoreNum = 0;

StoreMenu::StoreMenu() : OneTemp(0), TwoTemp(1), ThreeTemp(2), FourTemp(3)
{
	Pos({ WINSIZEXH, WINSIZEYH });
	StoreNum = 0;
}

StoreMenu::~StoreMenu()
{
}

void StoreMenu::Init()
{
	m_StoreFadeRender = MakeRender<SingleActorRender>(19);
	m_StoreFadeRender->SetSprite(L"StateChange.bmp");
	m_StoreFadeRender->SetAlpha(220);
	m_StoreFadeRender->Size({ WINSIZEX, WINSIZEY });
	m_StoreFadeRender->CameraMode(false);

	m_StoreMenuRender = MakeRender<SingleActorRender>(26);
	m_StoreMenuRender->SetSprite(L"StoreMenu.bmp");
	m_StoreMenuRender->Size({ 862, 352 });
	m_StoreMenuRender->CameraMode(false);
	m_StoreMenuRender->Pivot({ 22, -100 });

	//1
	m_FisrtRender = MakeRender<SingleActorRender>(26);
	m_FisrtRender->SetSprite(L"SeedStore.bmp", 0);
	m_FisrtRender->Size({ 768, 60 });
	m_FisrtRender->Pivot({ -5, -169 });
	m_FisrtRender->CameraMode(false);

	m_FirstColl = MakeCollision(L"StoreButton", { 768, 60 }, 0);
	m_FirstColl->Pivot({ -6, -150 });

	//2
	m_SecondRender = MakeRender<SingleActorRender>(26);
	m_SecondRender->SetSprite(L"SeedStore.bmp", 1);
	m_SecondRender->Size({ 768, 60 });
	m_SecondRender->Pivot({ -5, -103 });
	m_SecondRender->CameraMode(false);

	m_SecondColl = MakeCollision(L"StoreButton", { 768, 60 }, 1);
	m_SecondColl->Pivot({ -6, -84 });

	//3
	m_ThirdRender = MakeRender<SingleActorRender>(26);
	m_ThirdRender->SetSprite(L"SeedStore.bmp", 2);
	m_ThirdRender->Size({ 768, 60 });
	m_ThirdRender->Pivot({ -5, -37 });
	m_ThirdRender->CameraMode(false);

	m_ThirdColl = MakeCollision(L"StoreButton", { 768, 60 }, 2);
	m_ThirdColl->Pivot({ -6, -18 });

	//4
	m_FourthRender = MakeRender<SingleActorRender>(26);
	m_FourthRender->SetSprite(L"SeedStore.bmp", 3);
	m_FourthRender->Size({ 768, 60 });
	m_FourthRender->Pivot({ -5, 29 });
	m_FourthRender->CameraMode(false);

	m_FourthColl = MakeCollision(L"StoreButton", { 768, 60 }, 3);
	m_FourthColl->Pivot({ -6, 48 });

	////화살표
	m_UpArrowRender = MakeRender<SingleActorRender>(26);
	m_UpArrowRender->SetSprite(L"Arrow.bmp", 0);
	m_UpArrowRender->Size({ 40, 44 });
	m_UpArrowRender->Pivot({ 430, -115 });
	m_UpArrowRender->CameraMode(false);

	m_UpArrowColl = MakeCollision(L"StoreButton", { 40, 44 }, 4);
	m_UpArrowColl->Pivot({ 431, -107 });

	m_DownArrowRender = MakeRender<SingleActorRender>(26);
	m_DownArrowRender->SetSprite(L"Arrow.bmp", 1);
	m_DownArrowRender->Size({ 40, 44 });
	m_DownArrowRender->Pivot({ 430, -30 });
	m_DownArrowRender->CameraMode(false);

	m_DownArrowColl = MakeCollision(L"StoreButton", { 40, 44 }, 5);
	m_DownArrowColl->Pivot({ 431, -23 });

	//OK, Cancle
	m_OkRender = MakeRender<SingleActorRender>(26);
	m_OkRender->SetSprite(L"Ok.bmp", 0);
	m_OkRender->Size({ 45, 45 });
	m_OkRender->Pivot({ 335, -250 });
	m_OkRender->CameraMode(false);

	m_OkColl = MakeCollision(L"StoreButton", { 45, 45 }, 6);
	m_OkColl->Pivot({ 336, -243 });

	m_CancleRender = MakeRender<SingleActorRender>(26);
	m_CancleRender->SetSprite(L"Ok.bmp", 1);
	m_CancleRender->Size({ 45, 45 });
	m_CancleRender->Pivot({ 380, -250 });
	m_CancleRender->CameraMode(false);

	m_CancleColl = MakeCollision(L"StoreButton", { 45, 45 }, 7);
	m_CancleColl->Pivot({ 381, -243 });

}

void StoreMenu::PrevUpdate()
{
}

void StoreMenu::Update()
{
}

void StoreMenu::LaterUpdate()
{
}

void StoreMenu::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
	if (0 == _This->CollNum())
	{
		m_FisrtRender->SetSprite(L"SelectSeedStore.bmp", OneTemp);
	}
	if (1 == _This->CollNum())
	{
		m_SecondRender->SetSprite(L"SelectSeedStore.bmp", TwoTemp);
	}
	if (2 == _This->CollNum())
	{
		m_ThirdRender->SetSprite(L"SelectSeedStore.bmp", ThreeTemp);
	}
	if (3 == _This->CollNum())
	{
		m_FourthRender->SetSprite(L"SelectSeedStore.bmp", FourTemp);
	}
	if (4 == _This->CollNum())
	{
		m_UpArrowRender->SetSprite(L"SelectArrow.bmp", 0);
	}
	if (5 == _This->CollNum())
	{
		m_DownArrowRender->SetSprite(L"SelectArrow.bmp", 1);
	}
	if (6 == _This->CollNum())
	{
		m_OkRender->SetSprite(L"SelectOk.bmp", 0);
	}
	if (7 == _This->CollNum())
	{
		m_CancleRender->SetSprite(L"SelectOk.bmp", 1);
	}
}

void StoreMenu::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (5 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			if (7 > StoreNum)
			{
				m_FisrtRender->SetSprite(L"SeedStore.bmp", StoreNum * 4);
				m_SecondRender->SetSprite(L"SeedStore.bmp", (StoreNum * 4) + 1);
				m_ThirdRender->SetSprite(L"SeedStore.bmp", (StoreNum * 4) + 2);
				m_FourthRender->SetSprite(L"SeedStore.bmp", (StoreNum * 4) + 3);

				OneTemp = StoreNum * 4;
				TwoTemp = (StoreNum * 4) + 1;
				ThreeTemp = (StoreNum * 4) + 2;
				FourTemp = (StoreNum * 4) + 3;

				++StoreNum;
			}
			if (7 == StoreNum)
			{
				StoreNum = 0;
			}
		}
	}

	if (0 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			ItemMgr::ItemInfo* TestItem0 = ITEM.GetItem(0, OneTemp);
			if (true == Player::CurPlayer->ReducePlayerMoney(TestItem0->m_Price))
			{
				Player::CurPlayer->PutItem(TestItem0);
			}
		}
	}
	if (1 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			ItemMgr::ItemInfo* TestItem1 = ITEM.GetItem(0, TwoTemp);
			if (true == Player::CurPlayer->ReducePlayerMoney(TestItem1->m_Price))
			{
				Player::CurPlayer->PutItem(TestItem1);
			}
		}
	}
	if (2 == _This->CollNum()) 
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			if (26 == OneTemp + 2)
			{
				return;
			}
			else
			{
				ItemMgr::ItemInfo* TestItem2 = ITEM.GetItem(0, ThreeTemp);
				if (true == Player::CurPlayer->ReducePlayerMoney(TestItem2->m_Price))
				{
					Player::CurPlayer->PutItem(TestItem2);
				}
			}
		}
	}
	if (3 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			if (27 == OneTemp + 3)
			{
				return;
			}
			else
			{
				ItemMgr::ItemInfo* TestItem3 = ITEM.GetItem(0, FourTemp);
				if (true == Player::CurPlayer->ReducePlayerMoney(TestItem3->m_Price))
				{
					Player::CurPlayer->PutItem(TestItem3);
				}
			}
		}
	}
	if (6 == _This->CollNum() || 7 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			Player::CurPlayer->CloseMainInven();
			this->Off();
			Haley::m_StoreOpen = false;
			Player::CurPlayer->m_NActor2->Off();
		}
	}
}


void StoreMenu::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
	if (0 == _This->CollNum())
	{
		m_FisrtRender->SetSprite(L"SeedStore.bmp", OneTemp);
	}
	if (1 == _This->CollNum())
	{
		m_SecondRender->SetSprite(L"SeedStore.bmp", TwoTemp);
	}
	if (2 == _This->CollNum())
	{
		m_ThirdRender->SetSprite(L"SeedStore.bmp", ThreeTemp);
	}
	if (3 == _This->CollNum())
	{
		m_FourthRender->SetSprite(L"SeedStore.bmp", FourTemp);
	}
	if (4 == _This->CollNum())
	{
		m_UpArrowRender->SetSprite(L"Arrow.bmp", 0);
	}
	if (5 == _This->CollNum())
	{
		m_DownArrowRender->SetSprite(L"Arrow.bmp", 1);
	}
	if (6 == _This->CollNum())
	{
		m_OkRender->SetSprite(L"Ok.bmp", 0);
	}
	if (7 == _This->CollNum())
	{
		m_CancleRender->SetSprite(L"Ok.bmp", 1);
	}
}

#include "stdafx.h"
#include "AnimalStoreMenu.h"
#include "SingleActorRender.h"
#include "SCore.h"
#include "ActorCollision.h"
#include "EnterMgr.h"
#include "Player.h"
#include "ItemMgr.h"
#include "Mani.h"
#include "SecondNumberActor.h"
#include "CoopStoreMenu.h"
#include "Animal.h"
#include "CoopState.h"
#include "BarnState.h"
#include "CoopTile.h"
#include "BarnTile.h"
#include "SoundPlayer.h"
#include "ResourceMgr.h"	
#include "SelectEffect.h"

//인벤토리 다 차면 돈 안줄어들게 하기
//돈 0이 되면 못사게 하기

int AnimalStoreMenu::StoreNum = 0;
bool AnimalStoreMenu::AnimalExCheck = false;
bool AnimalStoreMenu::BAnimalExCheck = false;

AnimalStoreMenu::AnimalStoreMenu()
{
	Pos({ WINSIZEXH, WINSIZEYH });
	StoreNum = 0;
}

AnimalStoreMenu::~AnimalStoreMenu()
{
}

void AnimalStoreMenu::Init()
{
	AnimalStoreSp = GETSOUND;

	m_StoreFadeRender = MakeRender<SingleActorRender>(19);
	m_StoreFadeRender->SetSprite(L"StateChange.bmp");
	m_StoreFadeRender->SetAlpha(220);
	m_StoreFadeRender->Size({ WINSIZEX, WINSIZEY });
	m_StoreFadeRender->CameraMode(false);

	m_AnimalStoreMenuRender = MakeRender<SingleActorRender>(26);
	m_AnimalStoreMenuRender->SetSprite(L"AnimalStoreMenu.bmp");
	m_AnimalStoreMenuRender->Size({ 704, 352 });
	m_AnimalStoreMenuRender->CameraMode(false);
	m_AnimalStoreMenuRender->Pivot({ 22, -100 });

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

	m_0Render = MakeRender<SingleActorRender>(26);
	m_0Render->SetSprite(L"AnimalSelect.bmp", 7);
	m_0Render->Size({ 128, 74 });
	m_0Render->Pivot({ -WINSIZEXH + 389, -WINSIZEYH + 243 });
	m_0Render->CameraMode(false);

	m_1Render = MakeRender<SingleActorRender>(26);
	m_1Render->SetSprite(L"AnimalSelect.bmp", 7);
	m_1Render->Size({ 128, 74 });
	m_1Render->Pivot({ -WINSIZEXH + 538, -WINSIZEYH + 243 });
	m_1Render->CameraMode(false);

	m_2Render = MakeRender<SingleActorRender>(26);
	m_2Render->SetSprite(L"AnimalSelect.bmp", 7);
	m_2Render->Size({ 128, 74 });
	m_2Render->Pivot({ -WINSIZEXH + 684, -WINSIZEYH + 243 });
	m_2Render->CameraMode(false);

	m_3Render = MakeRender<SingleActorRender>(26);
	m_3Render->SetSprite(L"AnimalSelect.bmp", 7);
	m_3Render->Size({ 128, 74 });
	m_3Render->Pivot({ -WINSIZEXH + 389, -WINSIZEYH + 317 });
	m_3Render->CameraMode(false);

	m_4Render = MakeRender<SingleActorRender>(26);
	m_4Render->SetSprite(L"AnimalSelect.bmp", 7);
	m_4Render->Size({ 128, 74 });
	m_4Render->Pivot({ -WINSIZEXH + 538, -WINSIZEYH + 317 });
	m_4Render->CameraMode(false);

	m_5Render = MakeRender<SingleActorRender>(26);
	m_5Render->SetSprite(L"AnimalSelect.bmp", 7);
	m_5Render->Size({ 128, 74 });
	m_5Render->Pivot({ -WINSIZEXH + 680, -WINSIZEYH + 316 });
	m_5Render->CameraMode(false);

	m_6Render = MakeRender<SingleActorRender>(26);
	m_6Render->SetSprite(L"AnimalSelect.bmp", 7);
	m_6Render->Size({ 128, 74 });
	m_6Render->Pivot({ -WINSIZEXH + 389, -WINSIZEYH + 391 });
	m_6Render->CameraMode(false);

	m_0Coll = MakeCollision(L"StoreButton", { 100, 70 }, 0);
	m_0Coll->Pivot({ -WINSIZEXH + 389, -WINSIZEYH + 243 });
	m_1Coll = MakeCollision(L"StoreButton", { 100, 70 }, 1);
	m_1Coll->Pivot({ -WINSIZEXH + 538, -WINSIZEYH + 243 });
	m_2Coll = MakeCollision(L"StoreButton", { 100, 70 }, 2);
	m_2Coll->Pivot({ -WINSIZEXH + 684, -WINSIZEYH + 243 });
	m_3Coll = MakeCollision(L"StoreButton", { 100, 70 }, 3);
	m_3Coll->Pivot({ -WINSIZEXH + 389, -WINSIZEYH + 317 });
	m_4Coll = MakeCollision(L"StoreButton", { 100, 70 }, 4);
	m_4Coll->Pivot({ -WINSIZEXH + 538, -WINSIZEYH + 317 });
	m_5Coll = MakeCollision(L"StoreButton", { 100, 70 }, 5);
	m_5Coll->Pivot({ -WINSIZEXH + 680, -WINSIZEYH + 316 });
	m_6Coll = MakeCollision(L"StoreButton", { 100, 70 }, 6);
	m_6Coll->Pivot({ -WINSIZEXH + 389, -WINSIZEYH + 391 });

	m_NameRender = MakeRender<SingleActorRender>(26);
	m_NameRender->SetSprite(L"AnimalStoreMenuNum.bmp", 1);
	m_NameRender->Size({ 320, 160 });
	m_NameRender->Pivot({ -WINSIZEXH + 530, -WINSIZEYH + 555 });
	m_NameRender->CameraMode(false);
}

void AnimalStoreMenu::PrevUpdate()
{
}

void AnimalStoreMenu::Update()
{


}

void AnimalStoreMenu::LaterUpdate()
{
}

void AnimalStoreMenu::CollStart(ActorCollision * _This, ActorCollision * _Other)
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
		m_0Render->SetSprite(L"AnimalSelect.bmp", 0);
		m_NameRender->SetSprite(L"AnimalStoreMenuNum.bmp", 0);
	}
	if (1 == _This->CollNum())
	{
		m_1Render->SetSprite(L"AnimalSelect.bmp", 1);
		m_NameRender->SetSprite(L"AnimalStoreMenuNum.bmp", 1);
	}
	if (2 == _This->CollNum())
	{
		m_2Render->SetSprite(L"AnimalSelect.bmp", 2);
		m_NameRender->SetSprite(L"AnimalStoreMenuNum.bmp", 2);
	}
	if (3 == _This->CollNum())
	{
		m_3Render->SetSprite(L"AnimalSelect.bmp", 3);
		m_NameRender->SetSprite(L"AnimalStoreMenuNum.bmp", 3);
	}
	if (4 == _This->CollNum())
	{
		m_4Render->SetSprite(L"AnimalSelect.bmp", 4);
		m_NameRender->SetSprite(L"AnimalStoreMenuNum.bmp", 4);
	}
	if (5 == _This->CollNum())
	{
		m_5Render->SetSprite(L"AnimalSelect.bmp", 5);
		m_NameRender->SetSprite(L"AnimalStoreMenuNum.bmp", 5);
	}
	if (6 == _This->CollNum())
	{
		m_6Render->SetSprite(L"AnimalSelect.bmp", 6);
		m_NameRender->SetSprite(L"AnimalStoreMenuNum.bmp", 6);
	}
}

void AnimalStoreMenu::CollStay(ActorCollision * _This, ActorCollision * _Other)
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

	int TempX = rand() % 12 + 1;
	if (3 >= TempX)
	{
		TempX += 2;
	}
	int TempY = rand() % 12 + 1;
	if (6 >= TempY)
	{
		TempY += 5;
	}

	FPOS TempPos = Player::IndexWorldPos({ TempX, TempY });

	if (0 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			if (true == CoopStoreMenu::CoopCheck)
			{
				if (true == Player::CurPlayer->ReducePlayerMoney(800))
				{
					AnimalStoreSp->NewSoundPlay(L"Animal.wav");

					CoopState* TempState = (CoopState*)CORE.FindState(14);
					Animal* TempAnimal = TempState->MakeActor<Animal>(3);
					TempAnimal->SetAnimalTile(TempState->GetCoopTile()->CoopTileMap());

					Animal::TempCoopTile = TempState->GetCoopTile()->CoopTileMap();
					TempAnimal->Pos(TempPos);

					AnimalStoreMenu::AnimalExCheck = true;
				}
			}
		}
	}	
	if (1 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			if (true == CoopStoreMenu::BarnCheck)
			{
				if (true == Player::CurPlayer->ReducePlayerMoney(1500))
				{
					AnimalStoreSp->NewSoundPlay(L"Animal.wav");

					BarnState* TempState = (BarnState*)CORE.FindState(15);
					Animal* TempAnimal = TempState->MakeActor<Animal>(6);
					TempAnimal->SetAnimalTile(TempState->GetBarnTile()->BarnTileMap());
					TempAnimal->Pos(TempPos);

					//Animal::TempCoopTile = TempState->GetBarnTile()->BarnTileMap();
					//TempAnimal->Pos(TempPos);

					AnimalStoreMenu::BAnimalExCheck = true;
				}
			}
		}
	}
	if (2 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			if (true == CoopStoreMenu::BarnCheck)
			{
				if (true == Player::CurPlayer->ReducePlayerMoney(4000))
				{
					AnimalStoreSp->NewSoundPlay(L"Animal.wav");

					BarnState* TempState = (BarnState*)CORE.FindState(15);
					Animal* TempAnimal = TempState->MakeActor<Animal>(7);
					TempAnimal->SetAnimalTile(TempState->GetBarnTile()->BarnTileMap());
					TempAnimal->Pos(TempPos);

					//Animal::TempCoopTile = TempState->GetBarnTile()->BarnTileMap();
					//TempAnimal->Pos(TempPos);

					AnimalStoreMenu::BAnimalExCheck = true;
				}
			}
		}
	}
	if (3 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			if (true == CoopStoreMenu::CoopCheck)
			{
				if (true == Player::CurPlayer->ReducePlayerMoney(4000))
				{
					AnimalStoreSp->NewSoundPlay(L"Animal.wav");

					CoopState* TempState = (CoopState*)CORE.FindState(14);
					Animal* TempAnimal = TempState->MakeActor<Animal>(2);
					TempAnimal->SetAnimalTile(TempState->GetCoopTile()->CoopTileMap());
					TempAnimal->Pos(TempPos);

					AnimalStoreMenu::AnimalExCheck = true;
				}
			}
		}
	}
	if (4 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			if (true == CoopStoreMenu::BarnCheck)
			{
				if (true == Player::CurPlayer->ReducePlayerMoney(8000))
				{
					AnimalStoreSp->NewSoundPlay(L"Animal.wav");

					BarnState* TempState = (BarnState*)CORE.FindState(15);
					Animal* TempAnimal = TempState->MakeActor<Animal>(8);
					TempAnimal->SetAnimalTile(TempState->GetBarnTile()->BarnTileMap());
					TempAnimal->Pos(TempPos);

					//Animal::TempCoopTile = TempState->GetBarnTile()->BarnTileMap();
					//TempAnimal->Pos(TempPos);

					AnimalStoreMenu::BAnimalExCheck = true;
				}
			}
		}
	}
	if (5 == _This->CollNum())
	{
		if (true == ENTER.DownCondition(L"MouseLeft"))
		{
			if (true == CoopStoreMenu::CoopCheck)
			{
				if (true == Player::CurPlayer->ReducePlayerMoney(8000))
				{
					AnimalStoreSp->NewSoundPlay(L"Animal.wav");

					CoopState* TempState = (CoopState*)CORE.FindState(14);
					Animal* TempAnimal = TempState->MakeActor<Animal>(1);
					TempAnimal->SetAnimalTile(TempState->GetCoopTile()->CoopTileMap());
					TempAnimal->Pos(TempPos);

					AnimalStoreMenu::AnimalExCheck = true;
				}
			}
		}
	}

}

void AnimalStoreMenu::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
	if (0 == _This->CollNum())
	{
		m_0Render->SetSprite(L"AnimalSelect.bmp", 7);
	}
	if (1 == _This->CollNum())
	{
		m_1Render->SetSprite(L"AnimalSelect.bmp", 7);
	}
	if (2 == _This->CollNum())
	{
		m_2Render->SetSprite(L"AnimalSelect.bmp", 7);
	}
	if (3 == _This->CollNum())
	{
		m_3Render->SetSprite(L"AnimalSelect.bmp", 7);
	}
	if (4 == _This->CollNum())
	{
		m_4Render->SetSprite(L"AnimalSelect.bmp", 7);
	}
	if (5 == _This->CollNum())
	{
		m_5Render->SetSprite(L"AnimalSelect.bmp", 7);
	}
	if (6 == _This->CollNum())
	{
		m_6Render->SetSprite(L"AnimalSelect.bmp", 7);
	}
	if (7 == _This->CollNum())
	{
		m_OkRender->SetSprite(L"Ok.bmp", 0);
	}
	if (8 == _This->CollNum())
	{
		m_CancleRender->SetSprite(L"Ok.bmp", 1);
	}
}

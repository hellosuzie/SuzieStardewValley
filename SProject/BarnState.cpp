#include "stdafx.h"
#include "BarnState.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"
#include "BarnBack.h"
#include "TimeMgr.h"
#include "Player.h"
#include "SingleActorRender.h"
#include "AniActorRender.h"
#include "GameSprite.h"
#include "BarnDoor.h"
#include "BarnTile.h"
#include "Fade.h"
#include "MouseBaby.h"
#include "MainInButton.h"
#include "QuickInButton.h"
#include "HarvEffect.h"
#include "HandItem.h"
#include "Animal.h"
#include "SoundPlayer.h"
#include "AnimalStoreMenu.h"

FPOS BarnState::MineStartPos = FPOS::Zero;

void BarnState::ChangeBegin()
{
	BarnSp->NewSoundPlay(L"open_store_door.wav");
	if (true == AnimalStoreMenu::BAnimalExCheck)
	{
		BarnSp0->NewSoundPlay(L"Goet2.wav");
		BarnSp1->NewSoundPlay(L"Cow2.wav");
	}

	Player::CurPlayer = OVERPLAYER;
	OVERPLAYER->Pos(StartPlayerPos);

	FPOS BackStartPos = m_BarnBack->GetBarnBack()->Sprite()->Pos();
	FRECT SetBackRect = { BackStartPos, m_BarnBack->GetBarnBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_BarnTile->BarnTileMap());
}

void BarnState::ChangeEnd()
{
	SCore::CurState = ALLSTATE::BARN;
	BarnSp->NewSoundPlay(L"open_door.wav");
}

BarnState::BarnState()
{
}


BarnState::~BarnState()
{
}

void BarnState::StateInit()
{
	BarnSp = GETSOUND;
	BarnSp0 = GETSOUND;
	BarnSp1 = GETSOUND;

	Fade* F = MakeActor<Fade>();

	m_BarnBack = MakeActor<BarnBack>();
	m_BarnTile = MakeActor<BarnTile>();
	BarnDoor* Door = MakeActor<BarnDoor>();
	MakeActor<MouseBaby>();

	YsortOn(10);

	StartPlayerPos = Player::IndexWorldPos(m_BarnTile->PlayerStartIndex());
	OVERPLAYER->Pos(StartPlayerPos);

	Link(L"Door", L"Player");
	Link(L"Inventory", L"Mouse");
	Link(L"Animal", L"Player");
	Link(L"Milk", L"Player");

	FPOS BackStartPos = m_BarnBack->GetBarnBack()->Sprite()->Pos();
	FPOS BackEndPos = m_BarnBack->GetBarnBack()->Sprite()->Pos() + m_BarnBack->GetBarnBack()->Sprite()->Size();

	MainCamera()->Target(OVERPLAYER);
	MainCamera()->SetRange(true);
	MainCamera()->StartPos(BackStartPos);
	MainCamera()->EndPos(BackEndPos);

	//플레이어 배경밖으로 이동 막기
	FRECT SetBackRect = { BackStartPos, m_BarnBack->GetBarnBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_BarnTile->BarnTileMap());
}

void BarnState::StateUpdate()
{
	if (true == ENTER.DownCondition(L"CollDebug"))
	{
		if (true == DebugRender())
		{
			DebugRender(false);
		}
		else
		{
			DebugRender(true);
		}
	}
	if (true == ENTER.DownCondition(L"CountDebug"))
	{
		if (true == SCore::DebugRenderCheck())
		{
			SCore::DebugRenderOff();
		}
		else
		{
			SCore::DebugRenderOn();
		}
	}
	if (true == ENTER.DownCondition(L"TitleState"))
	{
		CORE.ChangeState(ALLSTATE::TITLE);
	}
	if (true == ENTER.DownCondition(L"RoomState"))
	{
		CORE.ChangeState(ALLSTATE::ROOM);
	}
	if (true == ENTER.DownCondition(L"FarmState"))
	{
		CORE.ChangeState(ALLSTATE::FARM);
	}
	if (true == ENTER.DownCondition(L"TownState"))
	{
		CORE.ChangeState(ALLSTATE::TOWN);
	}
	if (true == ENTER.DownCondition(L"StoreState"))
	{
		CORE.ChangeState(ALLSTATE::STORE);
	}

	m_RectPos = OVERPLAYER->RectPos();
	PlayerAction();
}


void BarnState::PlayerAction()
{
	if (true == ENTER.DownCondition(L"Action"))
	{
		switch (OVERPLAYER->PlayerState())
		{
		case Player::PICK:
			break;
		case Player::EAT:
			EatWork(QuickInButton::m_QCount);
			break;
		default:
			break;
		}
		switch (OVERPLAYER->PlayerItem())
		{
		case Player::PICKAXE:
			break;
		case Player::SICKLE:
			break;
		case Player::RUSTYSWORD:
			break;
		case Player::RAPIER:
			break;
		case Player::PIRATESWORD:
			break;
		case Player::GALAXYSWORD:
			break;
		case Player::CLAYMORE:
			break;
		default:
			break;
		}
	}
}

void BarnState::PlayerDirCheck(IPOS _Pos)
{
	IPOS DirCheckPos = Player::WorldPlayerIndex(OVERPLAYER->Pos());
	if (_Pos.Y < DirCheckPos.Y)
	{
		OVERPLAYER->PlayerDir(L"Up");
	}
	else if (_Pos.Y > DirCheckPos.Y)
	{
		OVERPLAYER->PlayerDir(L"Down");
	}
	if (_Pos.Y == DirCheckPos.Y && _Pos.X < DirCheckPos.X)
	{
		OVERPLAYER->PlayerDir(L"Left");
	}
	else if (_Pos.Y == DirCheckPos.Y && _Pos.X > DirCheckPos.X)
	{
		OVERPLAYER->PlayerDir(L"Right");
	}
}

void BarnState::EatWork(int _InvenNum)
{
	if (nullptr != OVERPLAYER->MainHandItem()->PlayerHandItem())
	{
		if (true == OVERPLAYER->MainHandItem()->PlayerHandItem()->m_Eat)
		{
			int Plus = OVERPLAYER->MainHandItem()->PlayerHandItem()->m_EatCount;
			if (true == OVERPLAYER->IncreasePlayerEnergy(Plus))
			{
				OVERPLAYER->MainHandItem()->HandRender()->Off();
				OVERPLAYER->MainHandItem()->PlayerHandItem(nullptr);

				OVERPLAYER->RemoveItem(_InvenNum);
			}
			else
			{
				OVERPLAYER->PlayerEnergy(100);
			}
		}
	}
}


void BarnState::DebugUpdate()
{
	//WCHAR OutText[100]{};
	//swprintf_s(OutText, L"BarnState");
	//TextOutW(BHDC, 5, 0, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"FPS %d", FPSTIME);
	//TextOutW(BHDC, 5, 20, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"AllActor %d", AllActorCount());
	//TextOutW(BHDC, 5, 40, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Mouse X : %d, Y : %d ", MOUSEI.X, MOUSEI.Y);
	//TextOutW(BHDC, 5, 60, OutText, lstrlenW(OutText));
	////swprintf_s(OutText, L"MonsterState %d ", m_MainMonster->MonsterState());
	////TextOutW(BHDC, 5, 80, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"PlayerState %d ", OVERPLAYER->PlayerState());
	//TextOutW(BHDC, 5, 100, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"PlayerItem %d ", OVERPLAYER->PlayerItem());
	//TextOutW(BHDC, 5, 120, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"PlayerHp %d ", OVERPLAYER->PlayerEnergy());
	//TextOutW(BHDC, 5, 140, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Player Index X : %d, Y : %d ", Player::WorldPlayerIndex(OVERPLAYER->Pos()).X, Player::WorldPlayerIndex(OVERPLAYER->Pos()).Y);
	//TextOutW(BHDC, 5, 160, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Rect Index X : %d, Y : %d ", OVERPLAYER->RectPos().X, OVERPLAYER->RectPos().Y);
	//TextOutW(BHDC, 5, 180, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"ChickenCount %d", Animal::ChickenCount);
	//TextOutW(BHDC, 5, 200, OutText, lstrlenW(OutText));
}

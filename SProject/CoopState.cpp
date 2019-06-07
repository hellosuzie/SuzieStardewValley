#include "stdafx.h"
#include "CoopState.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"
#include "CoopBack.h"
#include "TimeMgr.h"
#include "Player.h"
#include "SingleActorRender.h"
#include "AniActorRender.h"
#include "GameSprite.h"
#include "CoopDoor.h"
#include "CoopTile.h"
#include "Fade.h"
#include "MouseBaby.h"
#include "MainInButton.h"
#include "QuickInButton.h"
#include "HarvEffect.h"
#include "HandItem.h"
#include "Animal.h"
#include "SoundPlayer.h"
#include "AnimalStoreMenu.h"

FPOS CoopState::MineStartPos = FPOS::Zero;

void CoopState::ChangeBegin()
{
	CoopSp->NewSoundPlay(L"open_store_door.wav");
	if (true == AnimalStoreMenu::AnimalExCheck)
	{
		CoopSp0->NewSoundPlay(L"Duck.wav");
		CoopSp1->NewSoundPlay(L"Chicken.wav");
	}

	Player::CurPlayer = OVERPLAYER;
	OVERPLAYER->Pos(StartPlayerPos);

	FPOS BackStartPos = m_CoopBack->GetCoopBack()->Sprite()->Pos();
	FRECT SetBackRect = { BackStartPos, m_CoopBack->GetCoopBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_CoopTile->CoopTileMap());
}

void CoopState::ChangeEnd()
{
	SCore::CurState = ALLSTATE::COOP;
	CoopSp->NewSoundPlay(L"open_door.wav");
}

CoopState::CoopState()
{
}


CoopState::~CoopState()
{
}

void CoopState::StateInit()
{
	CoopSp = GETSOUND;
	CoopSp0 = GETSOUND;
	CoopSp1 = GETSOUND;

	Fade* F = MakeActor<Fade>();

	m_CoopBack = MakeActor<CoopBack>();
	m_CoopTile = MakeActor<CoopTile>();
	CoopDoor* Door = MakeActor<CoopDoor>();
	MakeActor<MouseBaby>();

	YsortOn(10);

	StartPlayerPos = Player::IndexWorldPos(m_CoopTile->PlayerStartIndex());
	OVERPLAYER->Pos(StartPlayerPos);

	Link(L"Door", L"Player");
	Link(L"Inventory", L"Mouse");
	Link(L"Animal", L"Player");
	Link(L"Egg", L"Player");

	FPOS BackStartPos = m_CoopBack->GetCoopBack()->Sprite()->Pos();
	FPOS BackEndPos = m_CoopBack->GetCoopBack()->Sprite()->Pos() + m_CoopBack->GetCoopBack()->Sprite()->Size();

	MainCamera()->Target(OVERPLAYER);
	MainCamera()->SetRange(true);
	MainCamera()->StartPos(BackStartPos);
	MainCamera()->EndPos(BackEndPos);

	//플레이어 배경밖으로 이동 막기
	FRECT SetBackRect = { BackStartPos, m_CoopBack->GetCoopBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_CoopTile->CoopTileMap());
}

void CoopState::StateUpdate()
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


void CoopState::PlayerAction()
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

void CoopState::PlayerDirCheck(IPOS _Pos)
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

void CoopState::EatWork(int _InvenNum)
{
	if (nullptr != OVERPLAYER->MainHandItem()->PlayerHandItem())
	{
		if (true == OVERPLAYER->MainHandItem()->PlayerHandItem()->m_Eat)
		{
			int Plus = OVERPLAYER->MainHandItem()->PlayerHandItem()->m_EatCount;
			if (true == OVERPLAYER->IncreasePlayerEnergy(Plus))
			{
				//OVERPLAYER->IncreasePlayerEnergy(Plus);
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


void CoopState::DebugUpdate()
{
	//WCHAR OutText[100]{};
	//swprintf_s(OutText, L"CoopState");
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

#include "stdafx.h"
#include "TownState.h"
#include "EnterMgr.h"
#include "ResourceMgr.h"
#include "TownBack.h"
#include "TimeMgr.h"
#include "Player.h"
#include "SingleActorRender.h"
#include "GameSprite.h"
#include "TownDoor.h"
#include "TownTile.h"
#include "Fade.h"
#include "Marlon.h"
#include "MouseBaby.h"
#include "NumberActor.h"
#include "SecondNumberActor.h"
#include "SoundPlayer.h"

void TownState::ChangeBegin()
{
	TownSp->NewSoundPlay(L"Town2.wav");

	Player::CurPlayer = OVERPLAYER;

	FPOS BackStartPos = m_TownBack->GetTonwBack()->Sprite()->Pos();
	FRECT SetBackRect = { BackStartPos, m_TownBack->GetTonwBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_TownTile->TownTileMap());

	if (ALLSTATE::FARM == SCore::CurState)
	{
		OVERPLAYER->Pos(StartPlayerPos);
	}
	else if(ALLSTATE::MINE == SCore::CurState)
	{
		OVERPLAYER->Pos(FPOS{ 480, 267 });
	}
	else if (ALLSTATE::STORE == SCore::CurState)
	{
		OVERPLAYER->Pos(FPOS{ 1840, 755 });
	}
	else if (ALLSTATE::MANI == SCore::CurState)
	{
		OVERPLAYER->Pos(FPOS{ 2100, 1500 });
	}
	else
	{
		if (true == TownDoor::UpDownCheck)
		{
			OVERPLAYER->Pos(FPOS{ 2520, 800 });
		}
		else
		{
			OVERPLAYER->Pos(FPOS{ 2520, 1600 });
		}
	}
}

void TownState::ChangeEnd()
{
	SCore::CurState = ALLSTATE::TOWN;
	TownSp->Stop();
}

TownState::TownState()
{
}


TownState::~TownState()
{
}

void TownState::StateInit()
{
	TownSp = GETSOUND;

	Fade* F = MakeActor<Fade>();

	MakeActor<MouseBaby>();
	MakeActor<Marlon>();
	m_TownBack = MakeActor<TownBack>();
	m_TownTile = MakeActor<TownTile>();
	TownDoor* Door = MakeActor<TownDoor>();

	StartPlayerPos = Player::IndexWorldPos(m_TownTile->PlayerStartIndex());
	OVERPLAYER->Pos(StartPlayerPos);

	Link(L"Door", L"Player");
	Link(L"StoreMan", L"Player");
	Link(L"StoreButton", L"Mouse");
	Link(L"Inventory", L"Mouse");

	FPOS BackStartPos = m_TownBack->GetTonwBack()->Sprite()->Pos();
	FPOS BackEndPos = m_TownBack->GetTonwBack()->Sprite()->Pos() + m_TownBack->GetTonwBack()->Sprite()->Size();

	MainCamera()->Target(OVERPLAYER);
	MainCamera()->SetRange(true);
	MainCamera()->StartPos(BackStartPos);
	MainCamera()->EndPos(BackEndPos);

	//플레이어 배경밖으로 이동 막기
	FRECT SetBackRect = { BackStartPos, m_TownBack->GetTonwBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_TownTile->TownTileMap());
}

void TownState::StateUpdate()
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
	if (true == ENTER.DownCondition(L"MineState"))
	{
		CORE.ChangeState(ALLSTATE::MINE);
	}
	if (true == ENTER.DownCondition(L"StoreState"))
	{
		CORE.ChangeState(ALLSTATE::STORE);
	}

	OVERPLAYER->m_NActor->Value(OVERPLAYER->PlayerMoney());
	OVERPLAYER->m_NActor2->Value(OVERPLAYER->PlayerMoney());
}

void TownState::DebugUpdate()
{
	//WCHAR OutText[100]{};
	//swprintf_s(OutText, L"TownState");
	//TextOutW(BHDC, 5, 0, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"FPS %d", FPSTIME);
	//TextOutW(BHDC, 5, 20, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"AllActor %d", AllActorCount());
	//TextOutW(BHDC, 5, 40, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Mouse X : %d, Y : %d ", MOUSEI.X, MOUSEI.Y);
	//TextOutW(BHDC, 5, 60, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Player X : %f, Y : %f ", OVERPLAYER->Pos().X, OVERPLAYER->Pos().Y);
	//TextOutW(BHDC, 5, 80, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Rect Index X : %d, Y : %d ", OVERPLAYER->RectPos().X, OVERPLAYER->RectPos().Y);
	//TextOutW(BHDC, 5, 100, OutText, lstrlenW(OutText));
}

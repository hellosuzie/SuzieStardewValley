#include "stdafx.h"
#include "ManiState.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"
#include "TimeMgr.h"
#include "SingleActorRender.h"
#include "GameSprite.h"

#include "Player.h"
#include "ManiBack.h"
#include "ManiDoor.h"
#include "ManiTile.h"
#include "Fade.h"
#include "MouseBaby.h"
#include "MainInButton.h"
#include "NumberActor.h"
#include "SecondNumberActor.h"	
#include "Mani.h"
#include "SoundPlayer.h"

void ManiState::ChangeBegin()
{
	ManiSp->NewSoundPlay(L"store.wav");
	ManiSp0->NewSoundPlay(L"open_store_door.wav");
	Player::CurPlayer = OVERPLAYER;
	OVERPLAYER->Pos(StartPlayerPos);

	FPOS BackStartPos = m_ManiBack->GetManiBack()->Sprite()->Pos();
	FRECT SetBackRect = { BackStartPos, m_ManiBack->GetManiBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_ManiTile->FarmManiMap());
}

void ManiState::ChangeEnd()
{
	ManiSp0->NewSoundPlay(L"open_door.wav");
	SCore::CurState = ALLSTATE::MANI;
	ManiSp->Stop();
}

ManiState::ManiState()
{
}


ManiState::~ManiState()
{
}

void ManiState::StateInit()
{
	ManiSp = GETSOUND;
	ManiSp0 = GETSOUND;

	Fade* F = MakeActor<Fade>();

	MakeActor<MouseBaby>();
	m_ManiBack = MakeActor<ManiBack>();
	m_ManiTile = MakeActor<ManiTile>();
	ManiDoor* Door = MakeActor<ManiDoor>();
	Mani* StoreMan = MakeActor<Mani>();

	StartPlayerPos = Player::IndexWorldPos(m_ManiTile->PlayerStartIndex());
	
	Link(L"Door", L"Player");
	Link(L"StoreMan", L"Player");
	Link(L"StoreButton", L"Mouse");
	Link(L"Inventory", L"Mouse");

	FPOS BackStartPos = m_ManiBack->GetManiBack()->Sprite()->Pos();
	FPOS BackEndPos = m_ManiBack->GetManiBack()->Sprite()->Pos() + m_ManiBack->GetManiBack()->Sprite()->Size();

	MainCamera()->Target(OVERPLAYER);
	MainCamera()->SetRange(true);
	MainCamera()->StartPos(BackStartPos);
	MainCamera()->EndPos(BackEndPos);

	//플레이어 배경밖으로 이동 막기
	FRECT SetBackRect = { BackStartPos, m_ManiBack->GetManiBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_ManiTile->FarmManiMap());
}

void ManiState::StateUpdate()
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
	if (true == ENTER.DownCondition(L"MineState"))
	{
		CORE.ChangeState(ALLSTATE::MINE);
	}

	OVERPLAYER->m_NActor->Value(OVERPLAYER->PlayerMoney());
	OVERPLAYER->m_NActor2->Value(OVERPLAYER->PlayerMoney());
}


void ManiState::DebugUpdate()
{
	//WCHAR OutText[100]{};
	//swprintf_s(OutText, L"ManiState");
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
	//swprintf_s(OutText, L"Money %d ", OVERPLAYER->PlayerMoney());
	//TextOutW(BHDC, 5, 120, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"InvenCount %d ", MainInButton::m_InvenCount);
	//TextOutW(BHDC, 5, 140, OutText, lstrlenW(OutText));
}

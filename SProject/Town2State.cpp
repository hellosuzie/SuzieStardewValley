#include "stdafx.h"
#include "Town2State.h"
#include "EnterMgr.h"
#include "ResourceMgr.h"
#include "Town2Back.h"
#include "TimeMgr.h"
#include "Player.h"
#include "SingleActorRender.h"
#include "GameSprite.h"
#include "Town2Door.h"
#include "Town2Tile.h"
#include "Fade.h"
#include "Marlon.h"
#include "MouseBaby.h"
#include "NumberActor.h"
#include "SecondNumberActor.h"
#include "Fountain.h"
#include "Lamp.h"
#include "TownDoor.h"
#include "SoundPlayer.h"

void Town2State::ChangeBegin()
{
	Town2Sp->NewSoundPlay(L"Town2.wav");
	Player::CurPlayer = OVERPLAYER;

	FPOS BackStartPos = m_Town2Back->GetTown2Back()->Sprite()->Pos();
	FRECT SetBackRect = { BackStartPos, m_Town2Back->GetTown2Back()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_Town2Tile->Town2TileMap());

	if (ALLSTATE::TOWN == SCore::CurState)
	{
		if (true == TownDoor::UpDownCheck)
		{
			OVERPLAYER->Pos(StartPlayerPos);
		}
		else
		{
			OVERPLAYER->Pos(FPOS{ 20, 1600 });
		}
	}
	else if(ALLSTATE::ROBIN == SCore::CurState)
	{
		OVERPLAYER->Pos(FPOS{ 1050, 810 });
	}
}

void Town2State::ChangeEnd()
{
	Town2Sp->Stop();
	SCore::CurState = ALLSTATE::TOWN2;
}

Town2State::Town2State()
{
}


Town2State::~Town2State()
{
}

void Town2State::StateInit()
{
	Town2Sp = GETSOUND;

	Fade* F = MakeActor<Fade>();

	MakeActor<MouseBaby>();
	m_Town2Back = MakeActor<Town2Back>();
	m_Town2Tile = MakeActor<Town2Tile>();
	Town2Door* Door = MakeActor<Town2Door>();
	Fountain* Water = MakeActor<Fountain>();
	Lamp* PP = MakeActor<Lamp>();
	PP->Pos({286, 1025});

	StartPlayerPos = Player::IndexWorldPos(m_Town2Tile->PlayerStartIndex());
	OVERPLAYER->Pos(StartPlayerPos);

	Link(L"Door", L"Player");
	Link(L"StoreMan", L"Player");
	Link(L"StoreButton", L"Mouse");
	Link(L"Inventory", L"Mouse");
	Link(L"Fountain", L"Player");

	FPOS BackStartPos = m_Town2Back->GetTown2Back()->Sprite()->Pos();
	FPOS BackEndPos = m_Town2Back->GetTown2Back()->Sprite()->Pos() + m_Town2Back->GetTown2Back()->Sprite()->Size();

	MainCamera()->Target(OVERPLAYER);
	MainCamera()->SetRange(true);
	MainCamera()->StartPos(BackStartPos);
	MainCamera()->EndPos(BackEndPos);

	//플레이어 배경밖으로 이동 막기
	FRECT SetBackRect = { BackStartPos, m_Town2Back->GetTown2Back()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_Town2Tile->Town2TileMap());
}

void Town2State::StateUpdate()
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

void Town2State::DebugUpdate()
{
	//WCHAR OutText[100]{};
	//swprintf_s(OutText, L"Town2State");
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

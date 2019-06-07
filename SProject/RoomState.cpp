#include "stdafx.h"
#include "RoomState.h"
#include "Player.h"
#include "RoomBack.h"
#include "RoomBed.h"
#include "RoomDoor.h"
#include "RoomTile.h"

#include "SCore.h"
#include "TimeMgr.h"
#include "EnterMgr.h"
#include "ResourceMgr.h"
#include "SingleActorRender.h"
#include "GameSprite.h"
#include "MathMgr.h"
#include "EnterMgr.h"
#include "Fade.h"
#include "MouseBaby.h"
#include "AniActorRender.h"
#include "SoundPlayer.h"

RoomState::RoomState()
{
}

RoomState::~RoomState()
{
}

void RoomState::ChangeBegin()
{
	RoomSp0->NewSoundPlay(L"Room.wav");
	RoomSp->NewSoundPlay(L"open_door.wav");
	Player::CurPlayer = OVERPLAYER;
	FPOS BackStartPos = m_RoomBack->GetRoomBack()->Sprite()->Pos();
	FRECT SetBackRect = { BackStartPos, m_RoomBack->GetRoomBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_RoomTile->RoomTileMap());

	if (ALLSTATE::FARM == SCore::CurState)
	{
		OVERPLAYER->Pos(FPOS{ 355, 850 });
	}
	else
	{
		OVERPLAYER->Pos(StartPlayerPos);
	}

}

void RoomState::ChangeEnd()
{
	RoomSp0->Stop();
	RoomSp->NewSoundPlay(L"open_door.wav");
	SCore::CurState = ALLSTATE::ROOM;
}

void RoomState::StateInit()
{
	RoomSp = GETSOUND;
	RoomSp0 = GETSOUND;
	
	Fade* F = MakeActor<Fade>();
	MakeActor<MouseBaby>();

	m_RoomTile = MakeActor<RoomTile>();
	m_RoomBack = MakeActor<RoomBack>();
	RoomBed* Bed = MakeActor<RoomBed>();
	RoomDoor* Door = MakeActor<RoomDoor>();
	OVERPLAYER = MakeActor<Player>();

	OVERPLAYER->StateOverOn(
		ALLSTATE::FARM
		, ALLSTATE::TOWN
		, ALLSTATE::STORE
		, ALLSTATE::MINE
		, ALLSTATE::MINE1
		, ALLSTATE::MINE2
		, ALLSTATE::MINE3
		, ALLSTATE::MINE4
		, ALLSTATE::MINE5 
		, ALLSTATE::TOWN2
		, ALLSTATE::COOP
		, ALLSTATE::BARN
		, ALLSTATE::MANI
		, ALLSTATE::ROBIN);

	StartPlayerPos = Player::IndexWorldPos(m_RoomTile->PlayerStartIndex());
	OVERPLAYER->Pos(StartPlayerPos);

	YsortOn(10);
	Link(L"Player", L"RoomActor");
	Link(L"Door", L"Player");
	Link(L"Inventory", L"Mouse");
	Link(L"Sleep", L"Mouse");

	//카메라 배경밖으로 이동 막기
	FPOS BackStartPos = m_RoomBack->GetRoomBack()->Sprite()->Pos();
	FPOS BackEndPos = m_RoomBack->GetRoomBack()->Sprite()->Pos() + m_RoomBack->GetRoomBack()->Sprite()->Size();

	MainCamera()->Target(OVERPLAYER);
	MainCamera()->SetRange(true);
	MainCamera()->StartPos(BackStartPos);
	MainCamera()->EndPos(BackEndPos);

	//플레이어 배경밖으로 이동 막기
	FRECT SetBackRect = { BackStartPos, m_RoomBack->GetRoomBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_RoomTile->RoomTileMap());
}

void RoomState::StateUpdate()
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
	if (true == ENTER.DownCondition(L"StoreState"))
	{
		CORE.ChangeState(ALLSTATE::STORE);
	}
	if (true == ENTER.DownCondition(L"EditState"))
	{
		CORE.ChangeState(ALLSTATE::EDIT);
	}
	if (true == ENTER.DownCondition(L"Town2State"))
	{
		CORE.ChangeState(ALLSTATE::TOWN2);
	}
	if (true == ENTER.DownCondition(L"ManiState"))
	{
		CORE.ChangeState(ALLSTATE::MANI);
	}
	if (true == ENTER.DownCondition(L"RobinState"))
	{
		CORE.ChangeState(ALLSTATE::ROBIN);
	}
	if (true == ENTER.DownCondition(L"CoopState"))
	{
		CORE.ChangeState(ALLSTATE::COOP);
	}
}

void RoomState::DebugUpdate()
{
	//WCHAR OutText[100]{};
	//swprintf_s(OutText, L"RoomState");
	//TextOutW(BHDC, 5, 0, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"FPS %d", FPSTIME);
	//TextOutW(BHDC, 5, 20, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"AllActor %d", AllActorCount());
	//TextOutW(BHDC, 5, 40, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Mouse X : %d, Y : %d ", MOUSEI.X, MOUSEI.Y);
	//TextOutW(BHDC, 5, 60, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Player X : %f, Y : %f ", OVERPLAYER->Pos().X, OVERPLAYER->Pos().Y);
	//TextOutW(BHDC, 5, 80, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Camera X : %f, Y : %f ", MainCamera()->CameraPos().X, MainCamera()->CameraPos().Y);
	//TextOutW(BHDC, 5, 100, OutText, lstrlenW(OutText));

	//int Test = MathMgr::PointToPointDig(OVERPLAYER->Pos(), MOUSEF);
	//swprintf_s(OutText, L"PlayerToMouse %d", Test);
	//TextOutW(BHDC, 5, 120, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"PlayerState %d ", OVERPLAYER->PlayerState());
	//TextOutW(BHDC, 5, 140, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"PlayerItem %d ", OVERPLAYER->PlayerItem());
	//TextOutW(BHDC, 5, 160, OutText, lstrlenW(OutText));

	//swprintf_s(OutText, L"World Index X : %d, Y : %d ", Player::WorldPlayerIndex(OVERPLAYER->Pos()).X, Player::WorldPlayerIndex(OVERPLAYER->Pos()).Y);
	//TextOutW(BHDC, 5, 180, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Rect Index X : %d, Y : %d ", OVERPLAYER->RectPos().X, OVERPLAYER->RectPos().Y);
	//TextOutW(BHDC, 5, 200, OutText, lstrlenW(OutText));

	//swprintf_s(OutText, L"Screen X : %f, Y : %f ", OVERPLAYER->ScreenPos().X, OVERPLAYER->ScreenPos().Y);
	//TextOutW(BHDC, 5, 220, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L" X : %f, Y : %f ", OVERPLAYER->MainPlayerRender()->GetRenderPos().X, OVERPLAYER->MainPlayerRender()->GetRenderPos().Y);
	//TextOutW(BHDC, 5, 240, OutText, lstrlenW(OutText));
}

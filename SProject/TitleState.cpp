#include "stdafx.h"
#include "TitleState.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "TitleBack.h"
#include "TitleCloud.h"
#include "SecondCloud.h"
#include "ResourceMgr.h"
#include "StarTitle.h"
#include "SingleActorRender.h"
#include "TimeMgr.h"
#include "ButtonMgr.h"
#include "Brighten.h"
#include "MouseBaby.h"
#include "SoundPlayer.h"

//마우스 충돌체 랜드할때 오차생기는거 고치기

TitleState::TitleState()
{
}


TitleState::~TitleState()
{
}

void TitleState::StateInit()
{
	MakeActor<Brighten>();
	MakeActor<MouseBaby>();
	m_Back = MakeActor<TitleBack>();
	m_Cloud = MakeActor<TitleCloud>();
	SecondCloud* m_SCloud = MakeActor<SecondCloud>();
	StarTitle* Title = MakeActor<StarTitle>();

	TitleSp = GETSOUND;
	TitleSp->NewSoundPlay(L"TitleScreen.wav");

	TitleButton();
	Link(L"TitleButton", L"Mouse");
}

void TitleState::ChangeBegin()
{
}

void TitleState::ChangeEnd()
{
	TitleSp->Stop();
}

void TitleState::StateUpdate()
{
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
	if (true == ENTER.DownCondition(L"StoreState"))
	{
		CORE.ChangeState(ALLSTATE::STORE);
	}
}

void TitleState::DebugUpdate()
{
	//WCHAR OutText[100]{};
	//swprintf_s(OutText, L"TitleState");
	//TextOutW(BHDC, 5, 0, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"FPS %d", FPSTIME);
	//TextOutW(BHDC, 5, 20, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"AllActor %d", AllActorCount());
	//TextOutW(BHDC, 5, 40, OutText, lstrlenW(OutText));
}

void TitleState::TitleButton()
{
	ButtonMgr* NewButton = MakeActor<ButtonMgr>();
	NewButton->SetBaseImage(L"Button.bmp", 0);
	NewButton->SetClickImage(L"Button.bmp", 4);
	NewButton->SetEnterImage(L"Button.bmp", 4);
	NewButton->ButtonInit(L"TitleButton", L"MouseLeft", FPOS({ 1024 / 2 - 210, 600 }), FSIZE(185, 145));

	NewButton->SetClickFunc(GoRoomState);

	ButtonMgr* RoadButton = MakeActor<ButtonMgr>();
	RoadButton->SetBaseImage(L"Button.bmp", 1);
	RoadButton->SetClickImage(L"Button.bmp", 5);
	RoadButton->SetEnterImage(L"Button.bmp", 5);
	RoadButton->ButtonInit(L"TitleButton", L"MouseLeft", FPOS({ 1024 / 2 , 600 }), FSIZE(185, 145));

	ButtonMgr* ExitButton = MakeActor<ButtonMgr>();
	ExitButton->SetBaseImage(L"Button.bmp", 3);
	ExitButton->SetClickImage(L"Button.bmp", 7);
	ExitButton->SetEnterImage(L"Button.bmp", 7);
	ExitButton->ButtonInit(L"TitleButton", L"MouseLeft", FPOS({ 1024 / 2 + 210, 600 }), FSIZE(185, 145));
}

void TitleState::GoRoomState(void *)
{
	CORE.ChangeState(ALLSTATE::ROOM);
}

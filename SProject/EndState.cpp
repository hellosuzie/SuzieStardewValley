#include "stdafx.h"
#include "EndState.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "ResourceMgr.h"
#include "SingleActorRender.h"
#include "TimeMgr.h"
#include "ButtonMgr.h"
#include "MouseBaby.h"
#include "SoundPlayer.h"
#include "EndBack.h"
#include "Brighten.h"
#include "EndCat.h"

EndState::EndState()
{
}


EndState::~EndState()
{
}

void EndState::StateInit()
{
	MakeActor<Brighten>();
	MakeActor<MouseBaby>();
	m_Back = MakeActor<EndBack>();
	MakeActor<EndCat>();

	TitleSp = GETSOUND;
	TitleSp->NewSoundPlay(L"End.wav");
}

void EndState::ChangeBegin()
{
}

void EndState::ChangeEnd()
{
	TitleSp->Stop();
}

void EndState::StateUpdate()
{
}

void EndState::DebugUpdate()
{
	WCHAR OutText[100]{};
	swprintf_s(OutText, L"EndState");
	TextOutW(BHDC, 5, 0, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"FPS %d", FPSTIME);
	TextOutW(BHDC, 5, 20, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"AllActor %d", AllActorCount());
	TextOutW(BHDC, 5, 40, OutText, lstrlenW(OutText));
}
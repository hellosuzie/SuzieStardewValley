#include "stdafx.h"
#include "Fountain.h"
#include "AniActorRender.h"
#include "SingleActorRender.h"
#include "ActorCollision.h"
#include "ResourceMgr.h"
#include "SoundPlayer.h"

Fountain::Fountain()
{
	Pos({ 861, 1190 });
}


Fountain::~Fountain()
{
}

void Fountain::Init()
{
	FountainSp = GETSOUND;

	m_Bot = MakeRender<SingleActorRender>(11);
	m_Bot->SetSprite(L"FountainBot.bmp");
	m_Bot->Size({ 304, 380 });
	m_Bot->Pivot({ -4, 26 });

	m_DownWaterAni = MakeRender<AniActorRender>(11);
	m_DownWaterAni->MakeAni(L"FountainDown.bmp", L"DownWater", 0, 5);
	m_DownWaterAni->Size({ 64, 192 });
	m_DownWaterAni->Pivot({ 0, 0 });
	m_DownWaterAni->ChangeAni(L"DownWater");

	m_LeftWaterAni = MakeRender<AniActorRender>(11);
	m_LeftWaterAni->MakeAni(L"FountainLeft.bmp", L"LeftWater", 0, 2);
	m_LeftWaterAni->Size({ 64, 64 });
	m_LeftWaterAni->Pivot({ -64, -64 });
	m_LeftWaterAni->ChangeAni(L"LeftWater");

	m_RightWaterAni = MakeRender<AniActorRender>(11);
	m_RightWaterAni->MakeAni(L"FountainRight.bmp", L"RightWater", 0, 2);
	m_RightWaterAni->Size({ 64, 64 });
	m_RightWaterAni->Pivot({ 64, -64 });
	m_RightWaterAni->ChangeAni(L"RightWater");

	m_RightDWaterAni = MakeRender<AniActorRender>(11);
	m_RightDWaterAni->MakeAni(L"FountainWater.bmp", L"DRWater", 0, 5);
	m_RightDWaterAni->Size({ 64, 64 });
	m_RightDWaterAni->Pivot({ -64, 0 });
	m_RightDWaterAni->ChangeAni(L"DRWater");

	m_LeftDWaterAni = MakeRender<AniActorRender>(11);
	m_LeftDWaterAni->MakeAni(L"FountainWater.bmp", L"DLWater", 0, 5);
	m_LeftDWaterAni->Size({ 64, 64 });
	m_LeftDWaterAni->Pivot({ 64, 0 });
	m_LeftDWaterAni->ChangeAni(L"DLWater");

	ActorCollision* FountainColl = MakeCollision(L"Fountain", { 550, 550 });
	FountainColl->Pivot({ 10, 40 });
}

void Fountain::Update()
{
}

void Fountain::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
	FountainSp->NewSoundPlay(L"Fountain.wav");
}

void Fountain::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
}

void Fountain::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
	FountainSp->Stop();
}

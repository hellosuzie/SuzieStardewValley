#include "stdafx.h"
#include "Rocks.h"
#include "AniActorRender.h"

Rocks::Rocks()
{
}


Rocks::~Rocks()
{
}

void Rocks::Init()
{
	m_RockAni = MakeRender<AniActorRender>(8);
	m_RockAni->Size({ 64, 64 });

	ArrCropName[Rockone] = L"RockOne";
	ArrCropName[Rocktwo] = L"RockTwo";
	ArrCropName[Emerald] = L"Emerald";
	ArrCropName[Aquamarine] = L"Aquamarine";
	ArrCropName[Ruby] = L"Ruby";
	ArrCropName[Topaz] = L"Topaz";
	ArrCropName[Diamond] = L"Diamond";

	MakeRockAni();
}

void Rocks::PrevUpdate()
{
}

void Rocks::Update()
{
}

void Rocks::LaterUpdate()
{
}

void Rocks::MakeRockAni()
{
	m_RockAni->MakeAni(L"Rock.bmp", L"RockOne", 0, 0, 0.1f, false, 0);
	m_RockAni->MakeAni(L"Rock.bmp", L"RockTwo", 1, 1, 0.1f, false, 1);
	m_RockAni->MakeAni(L"Rock.bmp", L"Emerald", 2, 2, 0.1f, false, 2);
	m_RockAni->MakeAni(L"Rock.bmp", L"Aquamarine", 3, 3, 0.1f, false, 3);
	m_RockAni->MakeAni(L"Rock.bmp", L"Ruby", 4, 4, 0.1f, false, 4);
	m_RockAni->MakeAni(L"Rock.bmp", L"Topaz", 5, 5, 0.1f, false, 5);
	m_RockAni->MakeAni(L"Rock.bmp", L"Diamond", 6, 6, 0.1f, false, 6);
}

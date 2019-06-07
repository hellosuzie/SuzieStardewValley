#include "stdafx.h"
#include "Soil.h"
#include "AniActorRender.h"

Soil::Soil()
{
}


Soil::~Soil()
{
}

void Soil::Init()
{
	m_SoilAni = MakeRender<AniActorRender>(2);
	m_SoilAni->Size({ 64, 64 });
	MakeSoilAni();
	m_SoilAni->ChangeAni(L"HoeDirt");
}

void Soil::MakeSoilAni()
{
	m_SoilAni->MakeAni(L"Soil.bmp", L"HoeDirt", 1, 1, 50.0f, false, 0);
	m_SoilAni->MakeAni(L"Soil.bmp", L"WaterDirt", 0, 0, 50.0f, false, 1);
}

void Soil::PrevUpdate()
{
}

void Soil::Update()
{
}

void Soil::LaterUpdate()
{
}

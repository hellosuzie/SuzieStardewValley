#include "stdafx.h"
#include "Imotion.h"
#include "AniActorRender.h"
#include "TimeMgr.h"

Imotion::Imotion()
{
}


Imotion::~Imotion()
{
}

void Imotion::Init()
{
	m_ImoRender = MakeRender<AniActorRender>(50);
	m_ImoRender->Size({ 50, 50 });
	m_ImoRender->MakeAni(L"Imo.bmp", L"Heart", 61, 72, 0.15f, false);
	m_ImoRender->MakeAni(L"Imo.bmp", L"Sleep", 73, 84, 0.15f, false);
	m_ImoRender->ChangeAni(L"Heart");
}

void Imotion::PrevUpdate()
{
}

void Imotion::Update()
{
	if (true == m_ImoRender->AniEndCheck())
	{
		Die();
	}
}

void Imotion::LaterUpdate()
{
}

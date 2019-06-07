#include "stdafx.h"
#include "DirtEffect.h"
#include "AniActorRender.h"

DirtEffect::DirtEffect()
{
}


DirtEffect::~DirtEffect()
{
}

void DirtEffect::Init()
{
	m_DirtEffectRender = MakeRender<AniActorRender>(11);
	m_DirtEffectRender->Size({ 64, 64 });
	
	m_DirtEffectRender->MakeAni(L"DirtEffect.bmp", L"DirtEffect", 0, 7, 0.1f, false);
	m_DirtEffectRender->ChangeAni(L"DirtEffect");
}

void DirtEffect::PrevUpdate()
{
}

void DirtEffect::Update()
{
	if (true == m_DirtEffectRender->AniEndCheck())
	{
		Die();
	}
}

void DirtEffect::LaterUpdate()
{
}

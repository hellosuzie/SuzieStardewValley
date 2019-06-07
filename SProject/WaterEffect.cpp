#include "stdafx.h"
#include "WaterEffect.h"
#include "AniActorRender.h"

WaterEffect::WaterEffect()
{
}


WaterEffect::~WaterEffect()
{
}

void WaterEffect::Init()
{
	m_WaterEffectRender = MakeRender<AniActorRender>(5);
	m_WaterEffectRender->Size({ 64, 64 });

	m_WaterEffectRender->MakeAni(L"WaterEffect.bmp", L"WaterEffect", 0, 9, 0.1f, false);
	m_WaterEffectRender->ChangeAni(L"WaterEffect");
}

void WaterEffect::PrevUpdate()
{
}

void WaterEffect::Update()
{
	if (true == m_WaterEffectRender->AniEndCheck())
	{
		Die();
	}
}

void WaterEffect::LaterUpdate()
{
}

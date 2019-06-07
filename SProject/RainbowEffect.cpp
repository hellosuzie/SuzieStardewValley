#include "stdafx.h"
#include "RainbowEffect.h"
#include "AniActorRender.h"

RainbowEffect::RainbowEffect()
{
}


RainbowEffect::~RainbowEffect()
{
}

void RainbowEffect::Init()
{
	m_RainbowEffectRender = MakeRender<AniActorRender>(11);
	m_RainbowEffectRender->Size({ 64, 64 });
	
	m_RainbowEffectRender->MakeAni(L"AnimalEffect.bmp", L"RainbowEffect", 0, 7, 0.1f, false);
	m_RainbowEffectRender->ChangeAni(L"RainbowEffect");
}

void RainbowEffect::PrevUpdate()
{
}

void RainbowEffect::Update()
{
	if (true == m_RainbowEffectRender->AniEndCheck())
	{
		Die();
	}
}

void RainbowEffect::LaterUpdate()
{
}

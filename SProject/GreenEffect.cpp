#include "stdafx.h"
#include "GreenEffect.h"
#include "AniActorRender.h"

GreenEffect::GreenEffect()
{
}


GreenEffect::~GreenEffect()
{
}

void GreenEffect::Init()
{
	m_GreenEffectRender = MakeRender<AniActorRender>(11);
	m_GreenEffectRender->Size({ 64, 64 });
	
	m_GreenEffectRender->MakeAni(L"AnimalEffect.bmp", L"GreenEffect", 8, 15, 0.1f, false);
	m_GreenEffectRender->ChangeAni(L"GreenEffect");
}

void GreenEffect::PrevUpdate()
{
}

void GreenEffect::Update()
{
	if (true == m_GreenEffectRender->AniEndCheck())
	{
		Die();
	}
}

void GreenEffect::LaterUpdate()
{
}

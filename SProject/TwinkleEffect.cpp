#include "stdafx.h"
#include "TwinkleEffect.h"
#include "AniActorRender.h"

TwinkleEffect::TwinkleEffect()
{
}


TwinkleEffect::~TwinkleEffect()
{
}

void TwinkleEffect::Init()
{
	m_TwinkleEffectRender = MakeRender<AniActorRender>(11);
	m_TwinkleEffectRender->Size({ 64, 64 });
	
	m_TwinkleEffectRender->MakeAni(L"Effect0.bmp", L"TwinkleEffect", 20, 29, 0.1f, false);
	m_TwinkleEffectRender->ChangeAni(L"TwinkleEffect");
}

void TwinkleEffect::PrevUpdate()
{
}

void TwinkleEffect::Update()
{
	if (true == m_TwinkleEffectRender->AniEndCheck())
	{
		Die();
	}
}

void TwinkleEffect::LaterUpdate()
{
}

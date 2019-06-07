#include "stdafx.h"
#include "BubbleEffect.h"
#include "AniActorRender.h"

BubbleEffect::BubbleEffect()
{
}


BubbleEffect::~BubbleEffect()
{
}

void BubbleEffect::Init()
{
	m_BubbleEffectRender = MakeRender<AniActorRender>(11);
	m_BubbleEffectRender->Size({ 64, 64 });
	
	m_BubbleEffectRender->MakeAni(L"Effect0.bmp", L"BubbleEffect", 10, 19, 0.1f, false);
	m_BubbleEffectRender->ChangeAni(L"BubbleEffect");
}

void BubbleEffect::PrevUpdate()
{
}

void BubbleEffect::Update()
{
	if (true == m_BubbleEffectRender->AniEndCheck())
	{
		Die();
	}
}

void BubbleEffect::LaterUpdate()
{
}

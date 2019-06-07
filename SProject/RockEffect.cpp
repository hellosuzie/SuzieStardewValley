#include "stdafx.h"
#include "RockEffect.h"
#include "AniActorRender.h"
#include "TimeMgr.h"

RockEffect::RockEffect()
{
}


RockEffect::~RockEffect()
{
}

void RockEffect::Init()
{
	m_RockEffectRender = MakeRender<AniActorRender>(5);
	m_RockEffectRender->Size({ 64, 64 });

	m_RockEffectRender->MakeAni(L"RockEffect.bmp", L"RockEffect", 0, 9, 0.1f, false);
	m_RockEffectRender->ChangeAni(L"RockEffect");
}

void RockEffect::PrevUpdate()
{
}

void RockEffect::Update()
{
	m_AlphaTime += DELTATIME;
	m_RockEffectRender->SetAlpha(255 - (int)((m_AlphaTime * 255) * 0.5f));

	if (true == m_RockEffectRender->AniEndCheck())
	{
		Die();
	}
}

void RockEffect::LaterUpdate()
{
}

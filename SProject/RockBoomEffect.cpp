#include "stdafx.h"
#include "RockBoomEffect.h"
#include "AniActorRender.h"

RockBoomEffect::RockBoomEffect()
{
}


RockBoomEffect::~RockBoomEffect()
{
}

void RockBoomEffect::Init()
{
	m_RockBoomEffectRender = MakeRender<AniActorRender>(11);
	m_RockBoomEffectRender->Size({ 64, 64 });
	
	m_RockBoomEffectRender->MakeAni(L"Effect1.bmp", L"RockBoomEffect", 0, 9, 0.1f, false);
	m_RockBoomEffectRender->ChangeAni(L"RockBoomEffect");
}

void RockBoomEffect::PrevUpdate()
{
}

void RockBoomEffect::Update()
{
	if (true == m_RockBoomEffectRender->AniEndCheck())
	{
		Die();
	}
}

void RockBoomEffect::LaterUpdate()
{
}

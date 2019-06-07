#include "stdafx.h"
#include "BoomEffect.h"
#include "AniActorRender.h"

BoomEffect::BoomEffect()
{
}


BoomEffect::~BoomEffect()
{
}

void BoomEffect::Init()
{
	m_BoomEffectRender = MakeRender<AniActorRender>(11);
	m_BoomEffectRender->Size({ 64, 64 });
	
	m_BoomEffectRender->MakeAni(L"AnimalEffect.bmp", L"BoomEffect", 16, 23, 0.1f, false);
	m_BoomEffectRender->ChangeAni(L"BoomEffect");
}

void BoomEffect::PrevUpdate()
{
}

void BoomEffect::Update()
{
	if (true == m_BoomEffectRender->AniEndCheck())
	{
		Die();
	}
}

void BoomEffect::LaterUpdate()
{
}

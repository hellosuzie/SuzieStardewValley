#include "stdafx.h"
#include "SelectEffect.h"
#include "AniActorRender.h"

SelectEffect::SelectEffect()
{
}


SelectEffect::~SelectEffect()
{
}

void SelectEffect::Init()
{
	m_SelectEffectRender = MakeRender<AniActorRender>(28);
	m_SelectEffectRender->Size({ 64, 64 });
	
	m_SelectEffectRender->MakeAni(L"Effect1.bmp", L"SelectEffect", 10, 19, 0.1f, false);
	m_SelectEffectRender->ChangeAni(L"SelectEffect");
}

void SelectEffect::PrevUpdate()
{
}

void SelectEffect::Update()
{
	if (true == m_SelectEffectRender->AniEndCheck())
	{
		Die();
	}
}

void SelectEffect::LaterUpdate()
{
}

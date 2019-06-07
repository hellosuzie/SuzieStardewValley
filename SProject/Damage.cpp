#include "stdafx.h"
#include "Damage.h"
#include "SingleActorRender.h"
#include "SCore.h"
#include "TimeMgr.h"

Damage::Damage() : m_Time(0.0f)
{
}


Damage::~Damage()
{
}

void Damage::Init()
{
	m_PlayerDamageRender = MakeRender<SingleActorRender>(200);
	m_PlayerDamageRender->SetSprite(L"BloodNum.bmp");
	m_PlayerDamageRender->Size({ 64, 32 });
}

void Damage::PrevUpdate()
{
}

void Damage::Update()
{
	m_Time += DELTATIME;
	m_PlayerDamageRender->Pivot(m_PlayerDamageRender->Pivot() += FPOS::UP * DELTATIME * 300.0F);
	m_PlayerDamageRender->SetAlpha(255 - (int)((m_Time * 255) * 0.5f));

	m_Time += DELTATIME;
	if (3.0f < m_Time)
	{
		m_PlayerDamageRender->Die();
	}
}

void Damage::LaterUpdate()
{
}

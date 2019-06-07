#include "stdafx.h"
#include "HarvEffect.h"
#include "SingleActorRender.h"
#include "TimeMgr.h"

HarvEffect::HarvEffect() : Time(0.0f)
{
}


HarvEffect::~HarvEffect()
{
}

void HarvEffect::Init()
{
	m_HarvRender = MakeRender<SingleActorRender>(50);
	m_HarvRender->Size({ 64, 64 });
}

void HarvEffect::PrevUpdate()
{
}

void HarvEffect::Update()
{
	Time += DELTATIME;
	m_HarvRender->Pivot(m_HarvRender->Pivot() += FPOS::UP * DELTATIME * 200.0F);
	m_HarvRender->SetAlpha(255 - (int)((Time * 255) * 0.5f));

	Time += DELTATIME;
	if (2.0f < Time)
	{
		m_HarvRender->Die();
	}
}

void HarvEffect::LaterUpdate()
{
}

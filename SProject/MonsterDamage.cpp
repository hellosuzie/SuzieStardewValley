#include "stdafx.h"
#include "MonsterDamage.h"
#include "SingleActorRender.h"
#include "SCore.h"
#include "TimeMgr.h"

MonsterDamage::MonsterDamage() : m_Time(0.0f)
{
}


MonsterDamage::~MonsterDamage()
{
}

void MonsterDamage::Init()
{
	m_MonsterDamageRender = MakeRender<SingleActorRender>(200);
	//m_MonsterDamageRender->SetSprite(L"MonsterNum.bmp", 0);
	m_MonsterDamageRender->Size({ 64, 32 });
}

void MonsterDamage::PrevUpdate()
{
}

void MonsterDamage::Update()
{
	m_Time += DELTATIME;
	m_MonsterDamageRender->Pivot(m_MonsterDamageRender->Pivot() += FPOS::UP * DELTATIME * 300.0F);
	m_MonsterDamageRender->SetAlpha(255 - (int)((m_Time * 255) * 0.5f));

	m_Time += DELTATIME;
	if (3.0f < m_Time)
	{
		m_MonsterDamageRender->Die();
	}
}

void MonsterDamage::LaterUpdate()
{
}

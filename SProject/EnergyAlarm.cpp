#include "stdafx.h"
#include "EnergyAlarm.h"
#include "SingleActorRender.h"
#include "TimeMgr.h"

EnergyAlarm::EnergyAlarm()
{
	Pos({ 140, 450 });
}


EnergyAlarm::~EnergyAlarm()
{
}

void EnergyAlarm::Init()
{
	m_AlarmRender = MakeRender<SingleActorRender>(500);
	m_AlarmRender->SetSprite(L"Outof.bmp");
	m_AlarmRender->Size({ 222, 58 });
	m_AlarmRender->CameraMode(false);
}

void EnergyAlarm::PrevUpdate()
{
}

void EnergyAlarm::Update()
{
	m_Time += DELTATIME;
	if (2.0f < m_Time)
	{
		m_AlarmRender->Die();
	}
}

void EnergyAlarm::LaterUpdate()
{
}

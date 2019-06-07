#include "stdafx.h"
#include "FullAlarm.h"
#include "SingleActorRender.h"
#include "TimeMgr.h"

FullAlarm::FullAlarm()
{
	Pos({ 140, 450 });
}


FullAlarm::~FullAlarm()
{
}

void FullAlarm::Init()
{
	m_AlarmRender = MakeRender<SingleActorRender>(500);
	m_AlarmRender->SetSprite(L"Full.bmp");
	m_AlarmRender->Size({ 222, 58 });
	m_AlarmRender->CameraMode(false);
}

void FullAlarm::PrevUpdate()
{
}

void FullAlarm::Update()
{
	m_Time += DELTATIME;
	if (2.0f < m_Time)
	{
		m_AlarmRender->Die();
	}
}

void FullAlarm::LaterUpdate()
{
}

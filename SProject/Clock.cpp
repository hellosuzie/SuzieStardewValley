#include "stdafx.h"
#include "Clock.h"
#include "SingleActorRender.h"

SingleActorRender* Clock::m_ClockRender = nullptr;

Clock::Clock()
{
	Pos({ 910, 100 });
}


Clock::~Clock()
{
}

void Clock::Init()
{
	m_ClockRender = MakeRender<SingleActorRender>(17);
	m_ClockRender->Size({ 226, 179 });
	m_ClockRender->CameraMode(false);
}

void Clock::PrevUpdate()
{
}

void Clock::Update()
{
}

void Clock::LaterUpdate()
{
}

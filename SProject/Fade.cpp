#include "stdafx.h"
#include "Fade.h"
#include "SingleActorRender.h"
#include "SCore.h"
#include "TimeMgr.h"

Fade::Fade() : m_DTimer(1.0f)
{
	Pos({ WINSIZEXH, WINSIZEYH });
}


Fade::~Fade()
{
}

void Fade::Init()
{
	m_FadeRedner = MakeRender<SingleActorRender>(200);
	m_FadeRedner->SetSprite(L"StateChange.bmp");
	m_FadeRedner->Size({ WINSIZEX, WINSIZEY });
	m_FadeRedner->CameraMode(false);
}

void Fade::PrevUpdate()
{
}

void Fade::Update()
{
	m_AlphaTime += DELTATIME;
	m_FadeRedner->SetAlpha(255 - (int)(m_AlphaTime * 255.0f));

	if (true == m_DTimer.TimeCheck())
	{
		Die();
		m_DTimer.TimeReset();
	}
}

void Fade::LaterUpdate()
{
}

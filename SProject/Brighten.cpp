#include "stdafx.h"
#include "Brighten.h"
#include "SingleActorRender.h"
#include "SCore.h"
#include "TimeMgr.h"

Brighten::Brighten() : m_DTimer(1.0f)
{
	Pos({ WINSIZEXH, WINSIZEYH });
}


Brighten::~Brighten()
{
}

void Brighten::Init()
{
	m_BrightRedner = MakeRender<SingleActorRender>(1001);
	m_BrightRedner->SetSprite(L"EditState.bmp");
	m_BrightRedner->Size({ WINSIZEX, WINSIZEY });
	m_BrightRedner->CameraMode(false);
}

void Brighten::PrevUpdate()
{
}

void Brighten::Update()
{
	m_AlphaTime += DELTATIME;
	m_BrightRedner->SetAlpha(255 - (int)(m_AlphaTime * 255.0f));

	if (true == m_DTimer.TimeCheck())
	{
		Die();
		m_DTimer.TimeReset();
	}
}

void Brighten::LaterUpdate()
{
}

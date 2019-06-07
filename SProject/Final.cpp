#include "stdafx.h"
#include "Final.h"
#include "SingleActorRender.h"
#include "SCore.h"
#include "TimeMgr.h"

Final::Final() : m_DTimer(1.0f)
{
}


Final::~Final()
{
}

void Final::Init()
{
	m_FinalRedner = MakeRender<SingleActorRender>(11);
	m_FinalRedner->SetSprite(L"TheEnd.bmp");
	m_FinalRedner->Size({ 400, 200 });
	m_FinalRedner->SetAlpha(0);
}

void Final::PrevUpdate()
{
}

void Final::Update()
{
	if (255 == m_FinalRedner->GetAlpha())
	{
		return;
	}
	else
	{
		m_FinalRedner->SetAlpha(m_FinalRedner->GetAlpha() + 1);
	}
}

void Final::LaterUpdate()
{
}

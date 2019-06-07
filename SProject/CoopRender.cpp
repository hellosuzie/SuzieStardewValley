#include "stdafx.h"
#include "CoopRender.h"
#include "SingleActorRender.h"

CoopRender::CoopRender()
{
	Pos({ 1024, 800 });
}


CoopRender::~CoopRender()
{
}

void CoopRender::Init()
{
	m_CoopRender = MakeRender<SingleActorRender>(10);
	m_CoopRender->SetSprite(L"Coop.bmp");
	m_CoopRender->Size({ 384, 448 });
}

#include "stdafx.h"
#include "CoopBack.h"
#include "SingleActorRender.h"

CoopBack::CoopBack()
{
	Pos({ 1088 * 0.5f, 960 * 0.5f });
}


CoopBack::~CoopBack()
{
}

void CoopBack::Init()
{
	m_CoopBack = MakeRender<SingleActorRender>(0);
	m_CoopBack->SetSprite(L"CoopMap.bmp");
	m_CoopBack->Size({ 1088, 960 });
}

void CoopBack::PrevUpdate()
{
}

void CoopBack::Update()
{
}

void CoopBack::LaterUpdate()
{
}

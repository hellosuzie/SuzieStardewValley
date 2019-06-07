#include "stdafx.h"
#include "FarmBack.h"
#include "SingleActorRender.h"

SingleActorRender* FarmBack::m_FarmBack;

FarmBack::FarmBack()
{
	Pos({ 2176 * 0.5f, 2368 * 0.5f });
}


FarmBack::~FarmBack()
{
}

void FarmBack::Init()
{
	m_FarmBack = MakeRender<SingleActorRender>(0);
	m_FarmBack->SetSprite(L"FarmMap.bmp");
	m_FarmBack->Size({ 2176, 2368 });
}

void FarmBack::PrevUpdate()
{
}

void FarmBack::Update()
{
}

void FarmBack::LaterUpdate()
{
}

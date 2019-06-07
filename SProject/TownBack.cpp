#include "stdafx.h"
#include "TownBack.h"
#include "SingleActorRender.h"

TownBack::TownBack()
{
	Pos({ 2560 * 0.5f, 1728 * 0.5f });
}


TownBack::~TownBack()
{
}

void TownBack::Init()
{
	m_TownBack = MakeRender<SingleActorRender>(0);
	m_TownBack->SetSprite(L"TownMap.bmp");
	m_TownBack->Size({ 2560, 1728 });
}

void TownBack::PrevUpdate()
{
}

void TownBack::Update()
{
}

void TownBack::LaterUpdate()
{
}

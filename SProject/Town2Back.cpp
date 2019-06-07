#include "stdafx.h"
#include "Town2Back.h"
#include "SingleActorRender.h"

Town2Back::Town2Back()
{
	Pos({ 1664 * 0.5f, 1728 * 0.5f });
}


Town2Back::~Town2Back()
{
}

void Town2Back::Init()
{
	m_Town2Back = MakeRender<SingleActorRender>(0);
	m_Town2Back->SetSprite(L"TownMap2.bmp");
	m_Town2Back->Size({ 1664, 1728 });
}

void Town2Back::PrevUpdate()
{
}

void Town2Back::Update()
{
}

void Town2Back::LaterUpdate()
{
}

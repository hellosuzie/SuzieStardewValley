#include "stdafx.h"
#include "BarnBack.h"
#include "SingleActorRender.h"

BarnBack::BarnBack()
{
	Pos({ 1408 * 0.5f, 960 * 0.5f });
}


BarnBack::~BarnBack()
{
}

void BarnBack::Init()
{
	m_BarnBack = MakeRender<SingleActorRender>(0);
	m_BarnBack->SetSprite(L"BarnMap.bmp");
	m_BarnBack->Size({ 1408, 960 });
}

void BarnBack::PrevUpdate()
{
}

void BarnBack::Update()
{
}

void BarnBack::LaterUpdate()
{
}

#include "stdafx.h"
#include "BarnRender.h"
#include "SingleActorRender.h"

BarnRender::BarnRender()
{
	Pos({ 543, 800 });
}


BarnRender::~BarnRender()
{
}

void BarnRender::Init()
{
	m_BarnRender = MakeRender<SingleActorRender>(10);
	m_BarnRender->SetSprite(L"Barn.bmp");
	m_BarnRender->Size({ 448, 448 });
}

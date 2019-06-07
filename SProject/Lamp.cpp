#include "stdafx.h"
#include "Lamp.h"
#include "SingleActorRender.h"

Lamp::Lamp()
{
}


Lamp::~Lamp()
{
}

void Lamp::Init()
{
	m_LampRender = MakeRender<SingleActorRender>(11);
	m_LampRender->SetSprite(L"Lamp.bmp");
	m_LampRender->Size({ 64, 256 });
}

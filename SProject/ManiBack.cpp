#include "stdafx.h"
#include "ManiBack.h"
#include "SingleActorRender.h"

ManiBack::ManiBack()
{
	Pos({ 1088 * 0.5f, 960 * 0.5f });
}


ManiBack::~ManiBack()
{
}

void ManiBack::Init()
{
	m_ManiBack = MakeRender<SingleActorRender>(0);
	m_ManiBack->SetSprite(L"ManiMap.bmp");
	m_ManiBack->Size({ 1088, 960 });
}

void ManiBack::PrevUpdate()
{
}

void ManiBack::Update()
{
}

void ManiBack::LaterUpdate()
{
}

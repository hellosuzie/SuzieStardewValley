#include "stdafx.h"
#include "RobinBack.h"
#include "SingleActorRender.h"

RobinBack::RobinBack()
{
	Pos({ 1088 * 0.5f, 960 * 0.5f });
}


RobinBack::~RobinBack()
{
}

void RobinBack::Init()
{
	m_RobinBack = MakeRender<SingleActorRender>(0);
	m_RobinBack->SetSprite(L"RobinMap.bmp");
	m_RobinBack->Size({ 1088, 960 });
}

void RobinBack::PrevUpdate()
{
}

void RobinBack::Update()
{
}

void RobinBack::LaterUpdate()
{
}

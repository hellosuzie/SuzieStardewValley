#include "stdafx.h"
#include "MineNum.h"
#include "SingleActorRender.h"

MineNum::MineNum()
{
}


MineNum::~MineNum()
{
}

void MineNum::Init()
{
	m_NumRender = MakeRender<SingleActorRender>(17);
	m_NumRender->Size({ 63, 45 });
	m_NumRender->CameraMode(false);
}

void MineNum::PrevUpdate()
{
}

void MineNum::Update()
{
}

void MineNum::LaterUpdate()
{
}


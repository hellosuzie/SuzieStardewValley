#include "stdafx.h"
#include "MineBack.h"
#include "SingleActorRender.h"

MineBack::MineBack()
{
	Pos({ 1088 * 0.5f, 1152 * 0.5f });
}


MineBack::~MineBack()
{
}

void MineBack::Init()
{
	m_MineBack = MakeRender<SingleActorRender>(0);
	m_MineBack->SetSprite(L"MineMap.bmp");
	m_MineBack->Size({ 1088, 1152 });
}

void MineBack::PrevUpdate()
{
}

void MineBack::Update()
{
}

void MineBack::LaterUpdate()
{
}

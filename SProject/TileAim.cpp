#include "stdafx.h"
#include "TileAim.h"
#include "SingleActorRender.h"
#include "EnterMgr.h"
#include "TimeMgr.h"

SingleActorRender* TileAim::m_Aim;

TileAim::TileAim()
{
	m_Pos = { WINSIZEXH, WINSIZEYH };
}


TileAim::~TileAim()
{
}

void TileAim::Init()
{
	m_Aim = MakeRender<SingleActorRender>(100);
	m_Aim->SetSprite(L"TileAim.bmp");
	m_Aim->Size({ 64, 64 });
}

void TileAim::PrevUpdate()
{
}

void TileAim::Update()
{
	if (true == KEYDOWNSTAY("LEFT"))
	{
		m_Pos.X += (1700.0f * DELTATIME * DLEFT.X);
	}
	else if (true == KEYDOWNSTAY("RIGHT"))
	{
		m_Pos.X += (1700.0f * DELTATIME * DRIGHT.X);
	}
	else if (true == KEYDOWNSTAY("DOWN"))
	{
		m_Pos.Y += (1700.0f * DELTATIME * DDOWN.Y);
	}
	else if (true == KEYDOWNSTAY("UP"))
	{
		m_Pos.Y += (1700.0f * DELTATIME * DUP.Y);
	}
}

void TileAim::LaterUpdate()
{
}

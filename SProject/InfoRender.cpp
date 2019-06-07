#include "stdafx.h"
#include "InfoRender.h"
#include "SingleActorRender.h"
#include "ActorCollision.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "Player.h"
#include "MineState.h"
#include "Fade.h"
#include "EnterMgr.h"

InfoRender::InfoRender() 
{
}


InfoRender::~InfoRender()
{
}

void InfoRender::Init()
{
	m_ItemInfoRender = MakeRender<SingleActorRender>(101);
	m_ItemInfoRender->SetSprite(L"Info.bmp");
	m_ItemInfoRender->Size({ 240, 240 });
	m_ItemInfoRender->CameraMode(false);
	m_ItemInfoRender->Pivot({ 160, 100 });
}

void InfoRender::PrevUpdate()
{
}

void InfoRender::Update()
{
	Pos(MOUSEF);
}

void InfoRender::LaterUpdate()
{
}


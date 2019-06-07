#include "stdafx.h"
#include "QuickInvenBack.h"
#include "SingleActorRender.h"
#include "SCore.h"

QuickInvenBack::QuickInvenBack()
{
	Pos({ WINSIZEXH, 715 });
}


QuickInvenBack::~QuickInvenBack()
{
}

void QuickInvenBack::Init()
{
	m_QuickInBack = MakeRender<SingleActorRender>(20);
	m_QuickInBack->SetSprite(L"MiniMenu.bmp");
	m_QuickInBack->Size({ 800, 96 });
	m_QuickInBack->CameraMode(false);
}

void QuickInvenBack::PrevUpdate()
{
}

void QuickInvenBack::Update()
{
}

void QuickInvenBack::LaterUpdate()
{
}

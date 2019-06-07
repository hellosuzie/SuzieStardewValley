#include "stdafx.h"
#include "MainInvenBack.h"
#include "SingleActorRender.h"
#include "SCore.h"

MainInvenBack::MainInvenBack()
{
	Pos({WINSIZEXH, WINSIZEYH + 250 - TILESIZEH});
}


MainInvenBack::~MainInvenBack()
{
}

void MainInvenBack::Init()
{
	m_MainInBack = MakeRender<SingleActorRender>(20);
	m_MainInBack->SetSprite(L"BigMenu.bmp");
	m_MainInBack->Size({ 808, 217 });
	m_MainInBack->CameraMode(false);
}

void MainInvenBack::PrevUpdate()
{
}

void MainInvenBack::Update()
{
}

void MainInvenBack::LaterUpdate()
{
}

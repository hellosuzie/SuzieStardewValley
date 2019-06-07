#include "stdafx.h"
#include "StarTitle.h"
#include "SingleActorRender.h"
#include "SCore.h"

StarTitle::StarTitle()
{
	Pos({ WINSIZEXH, 250 });
}


StarTitle::~StarTitle()
{
}

void StarTitle::Init()
{
	SingleActorRender* Title = MakeRender<SingleActorRender>(4);
	Title->SetSprite(L"Logo.bmp");
	Title->Size({ 700, 385 });
	Title->CameraMode(false);
}

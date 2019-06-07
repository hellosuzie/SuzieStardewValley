#include "stdafx.h"
#include "TitleBack.h"
#include "SingleActorRender.h"
#include "ActorRender.h"
#include "SCore.h"

TitleBack::TitleBack()
{
	Pos({ WINSIZEXH, WINSIZEYH });
}

TitleBack::~TitleBack()
{
}

void TitleBack::Init()
{
	m_TitleBack = MakeRender<SingleActorRender>(0);
	m_TitleBack->SetSprite(L"TitleBack.bmp");
	m_TitleBack->Size({ WINSIZEX, WINSIZEY });
	m_TitleBack->CameraMode(false);

}

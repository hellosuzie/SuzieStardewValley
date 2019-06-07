#include "stdafx.h"
#include "EndBack.h"
#include "SingleActorRender.h"
#include "ActorRender.h"
#include "SCore.h"

EndBack::EndBack()
{
	Pos({ WINSIZEXH, WINSIZEYH });
}

EndBack::~EndBack()
{
}

void EndBack::Init()
{
	m_EndBack = MakeRender<SingleActorRender>(0);
	m_EndBack->SetSprite(L"StateChange.bmp");
	m_EndBack->Size({ WINSIZEX, WINSIZEY });
	m_EndBack->CameraMode(false);

}

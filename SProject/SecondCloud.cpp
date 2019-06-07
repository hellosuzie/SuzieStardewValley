#include "stdafx.h"
#include "SecondCloud.h"
#include "SingleActorRender.h"
#include "SCore.h"
#include "TimeMgr.h"

SecondCloud::SecondCloud()
{
	Pos({ WINSIZEXH + 400 , WINSIZEYH - 200 });
}


SecondCloud::~SecondCloud()
{
}

void SecondCloud::Init()
{
	m_CloudTwo = MakeRender<SingleActorRender>(2);
	m_CloudTwo->SetSprite(L"BigCloud.bmp");
	m_CloudTwo->Size({ 246, 110 });
	m_CloudTwo->CameraMode(false);
}

void SecondCloud::Update()
{
	m_Pos.X += (20.0f * DELTATIME * DLEFT.X);
	if (0 >= m_Pos.X)
	{
		Die();
	}
}


#include "stdafx.h"
#include "TitleCloud.h"
#include "SingleActorRender.h"
#include "SCore.h"
#include "TimeHelper.h"
#include "TimeMgr.h"

TitleCloud::TitleCloud()
{
	Pos({ WINSIZEXH - 200, WINSIZEYH + 200 });
}


TitleCloud::~TitleCloud()
{
}

void TitleCloud::Init()
{
	m_CloudOne = MakeRender<SingleActorRender>(1);
	m_CloudOne->SetSprite(L"SmallCloud.bmp");
	m_CloudOne->Size({ 128, 72 });
	m_CloudOne->Pivot({ 300, -150 });
	m_CloudOne->CameraMode(false);

	m_CloudThree = MakeRender<SingleActorRender>(3);
	m_CloudThree->SetSprite(L"BigCloud.bmp");
	m_CloudThree->Size({ 123, 55 });
	m_CloudThree->Pivot({ 0, 0 });
	m_CloudThree->CameraMode(false);
}

void TitleCloud::PrevUpdate()
{
}

void TitleCloud::Update()
{
	//m_CloudOne->m_Pivot.X += (60 * DELTATIME * DLEFT.X);
	//m_CloudThree->m_Pivot.X += (80.0f * DELTATIME * DLEFT.X);

	m_Pos.X += (50.0f * DELTATIME * DLEFT.X);
	if (150 >= m_Pos.X)
	{
		Die();
	}
}

void TitleCloud::LaterUpdate()
{
}

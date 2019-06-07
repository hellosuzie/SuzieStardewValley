#include "stdafx.h"
#include "SecondTitleAni.h"
#include "AniActorRender.h"
#include "SingleActorRender.h"

SecondTitleAni::SecondTitleAni()
{
}


SecondTitleAni::~SecondTitleAni()
{
}

void SecondTitleAni::Init()
{
	m_SecondTitleAni = MakeRender<AniActorRender>();
	m_SecondTitleAni->MakeAni(L"SecondTitle.bmp", L"SecondTitle", 0, 1);
	m_SecondTitleAni->Size({ 220, 114 });
	m_SecondTitleAni->Pivot({ 100, 0 });
	m_SecondTitleAni->ChangeAni(L"SecondTitle");

	m_SecondTitleAni2 = MakeRender<AniActorRender>();
	m_SecondTitleAni2->MakeAni(L"ThirdTitle.bmp", L"ThirdTitle", 0, 3, 0.2f);
	m_SecondTitleAni2->Size({ 170, 138 });
	m_SecondTitleAni2->Pivot({ -100, 0});
	m_SecondTitleAni2->ChangeAni(L"ThirdTitle");

	m_NameRender = MakeRender<SingleActorRender>();
	m_NameRender->SetSprite(L"Suzie.bmp");
	m_NameRender->Size({ 300, 50 });
	m_NameRender->Pivot({ -345, 350 });
}

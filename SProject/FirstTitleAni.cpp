#include "stdafx.h"
#include "FirstTitleAni.h"
#include "AniActorRender.h"

FirstTitleAni::FirstTitleAni()
{
}


FirstTitleAni::~FirstTitleAni()
{
}

void FirstTitleAni::Init()
{
	m_FirstTitleAni = MakeRender<AniActorRender>();
	m_FirstTitleAni->MakeAni(L"FirstTitle.bmp", L"FirstTitle", 0, 1);
	m_FirstTitleAni->Size({ 400, 291 });
	m_FirstTitleAni->ChangeAni(L"FirstTitle");
}

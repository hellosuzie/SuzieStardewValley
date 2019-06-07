#include "stdafx.h"
#include "EndCat.h"
#include "TimeHelper.h"
#include "TimeMgr.h"
#include "AniActorRender.h"
#include "Imotion.h"
#include "Final.h"
#include "SelectEffect.h"

bool EndCat::CTest = false;
bool EndCat::LetterCheck = false;

EndCat::EndCat() : CatTime(10.0f)
{
	Pos({-WINSIZEXH, -120});
}


EndCat::~EndCat()
{
}

void EndCat::Init()
{
	m_EndCatRender = MakeRender<AniActorRender>(11);
	m_EndCatRender->Size({ 128, 128 });
	
	m_EndCatRender->MakeAni(L"cat1.bmp", L"CatWalk", 4, 7, 0.1f, true);
	m_EndCatRender->MakeAni(L"cat1.bmp", L"CatSleep", 24, 27, 0.1f, false);
	m_EndCatRender->ChangeAni(L"CatWalk");
}

void EndCat::PrevUpdate()
{
}

void EndCat::Update()
{
	if ( 0 <= m_Pos.X)
	{
		if (false == EndCat::CTest)
		{
			m_EndCatRender->ChangeAni(L"CatSleep");
			Imotion* Test = Parent()->MakeActor<Imotion>();
			Test->ImoRender()->ChangeAni(L"Sleep");
			Test->Pos({ m_EndCatRender->PivotPos().X, m_EndCatRender->PivotPos().Y - 30 });
			EndCat::CTest = true;

			Final* Temp = Parent()->MakeActor<Final>();
		}
		return;
	}
	else
	{
		m_Pos.X += (800.f * DELTATIME * DRIGHT.X);
	}
}

void EndCat::LaterUpdate()
{
}

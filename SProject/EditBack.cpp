#include "stdafx.h"
#include "EditBack.h"
#include "SingleActorRender.h"
#include "SCore.h"

EditBack::EditBack()
{
	m_Pos = { WINSIZEXH, WINSIZEYH };
}


EditBack::~EditBack()
{
}

void EditBack::Init()
{
	m_EditBack = MakeRender<SingleActorRender>(0);
	m_EditBack->SetSprite(L"EditState.bmp");
	m_EditBack->Size({ 1024, 768 });
}

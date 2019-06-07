#include "stdafx.h"
#include "StoreBack.h"
#include "SingleActorRender.h"

StoreBack::StoreBack()
{
	Pos({ 1152 * 0.5f, 1216 * 0.5f });
}


StoreBack::~StoreBack()
{
}

void StoreBack::Init()
{
	m_StoreBack = MakeRender<SingleActorRender>(0);
	m_StoreBack->SetSprite(L"StoreMap.bmp");
	m_StoreBack->Size({ 1152, 1216 });
}

void StoreBack::PrevUpdate()
{
}

void StoreBack::Update()
{
}

void StoreBack::LaterUpdate()
{
}

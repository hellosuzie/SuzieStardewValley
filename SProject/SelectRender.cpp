#include "stdafx.h"
#include "SelectRender.h"
#include "SingleActorRender.h"

SelectRender::SelectRender()
{

}


SelectRender::~SelectRender()
{
}

void SelectRender::Init()
{
	m_SelectRender = MakeRender<SingleActorRender>(19);
	m_SelectRender->SetSprite(L"SelectRender.bmp");
	m_SelectRender->Size({ 64, 64 });
}

void SelectRender::PrevUpdate()
{
}

void SelectRender::Update()
{
}

void SelectRender::LaterUpdate()
{
}


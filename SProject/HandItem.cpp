#include "stdafx.h"
#include "HandItem.h"
#include "SingleActorRender.h"
#include "ItemMgr.h"

HandItem::HandItem() : m_PlayerHandItem(nullptr)
{
}


HandItem::~HandItem()
{
}

void HandItem::Init()
{
	m_HandRender = MakeRender<SingleActorRender>(20);
	m_HandRender->Size({ TILESIZE, TILESIZE });
}

void HandItem::PrevUpdate()
{
}

void HandItem::Update()
{
}

void HandItem::LaterUpdate()
{
}

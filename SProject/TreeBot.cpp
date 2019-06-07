#include "stdafx.h"
#include "TreeBot.h"
#include "AniActorRender.h"

TreeBot::TreeBot()
{
}


TreeBot::~TreeBot()
{
}

void TreeBot::Init()
{
	m_TreeAniBot = MakeRender<AniActorRender>(10);
	m_TreeAniBot->Size({ 64, 128 });
	m_TreeAniBot->Pivot({ 0, -32 });

	MakeTreeAni();
}

void TreeBot::PrevUpdate()
{
}

void TreeBot::Update()
{
}

void TreeBot::LaterUpdate()
{
}

void TreeBot::MakeTreeAni()
{
	m_TreeAniBot->MakeAni(L"RootTree.bmp", L"MapleTreeBot", 1, 1, false, 0);
	m_TreeAniBot->MakeAni(L"RootTree.bmp", L"AcronTreeBot", 0, 0, false, 0);
	m_TreeAniBot->MakeAni(L"RootTree.bmp", L"PineTreeBot", 2, 2, false, 0);
}

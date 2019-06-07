#include "stdafx.h"
#include "TreeTop.h"
#include "AniActorRender.h"
#include "ActorCollision.h"
#include "TimeMgr.h"
#include "EnterMgr.h"

TreeTop::TreeTop()
{
}


TreeTop::~TreeTop()
{
}


void TreeTop::Init()
{
	m_TreeAniTop = MakeRender<AniActorRender>(11);
	m_TreeAniTop->Size({ 256, 384 });
	m_TreeAniTop->Pivot({ 0, -148 });

	m_TreeCollLeap = MakeCollision(L"Tree", { 192, 256 });
	m_TreeCollLeap->Pivot({ 0, -215 });

	m_TreeColl = MakeCollision(L"Tree", { 64, 64 });
	m_TreeColl->Pivot({ 0, -64 });

	MakeTreeAni();
}

void TreeTop::PrevUpdate()
{
}

void TreeTop::Update()
{
}

void TreeTop::LaterUpdate()
{
}


void TreeTop::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
	m_TreeAniTop->SetAlpha(150);

}

void TreeTop::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
}

void TreeTop::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
	m_TreeAniTop->SetAlpha(255);
}

void TreeTop::MakeTreeAni()
{
	m_TreeAniTop->MakeAni(L"MapleTree.bmp", L"MapleTreeTop", 0, 0, 0.01f, false, 0);
	m_TreeAniTop->MakeAni(L"AcornTree.bmp", L"AcronTreeTop", 1, 1, 0.01f, false, 1);
	m_TreeAniTop->MakeAni(L"PineTree.bmp", L"PineTreeTop", 2, 2, 0.01f, false, 2);

	m_TreeAniTop->MakeAni(L"MapleTree.bmp", L"MapleTreeTop1", 0, 17, 0.003f, false, 0);
	m_TreeAniTop->MakeAni(L"AcornTree.bmp", L"AcronTreeTop1", 0, 17, 0.003f, false, 0);
	m_TreeAniTop->MakeAni(L"PineTree.bmp", L"PineTreeTop1", 0, 17, 0.003f, false, 0);
}

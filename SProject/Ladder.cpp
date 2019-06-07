#include "stdafx.h"
#include "Ladder.h"
#include "SingleActorRender.h"
#include "ActorCollision.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "Player.h"
#include "MineState.h"
#include "Fade.h"

Ladder::Ladder() : m_Count(0)
{
}


Ladder::~Ladder()
{
}

void Ladder::Init()
{
	m_LadderRender = MakeRender<SingleActorRender>(7);
	m_LadderRender->SetSprite(L"Ladder.bmp");
	m_LadderRender->Size({ 54, 54 });

	MakeCollision(L"Ladder", { 60, 60 });
}

void Ladder::PrevUpdate()
{
}

void Ladder::Update()
{
}

void Ladder::LaterUpdate()
{
}

void Ladder::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
	
}

void Ladder::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (0 == m_Count)
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::MINE1);
			Player::CurPlayer->Pos(MineState::MineStartPos);
			Fade* F = _This->Actor()->Parent()->MakeActor<Fade>();
		}
	}
	if (1 == m_Count)
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::MINE2);
			Player::CurPlayer->Pos(MineState::MineStartPos);
			Fade* F = _This->Actor()->Parent()->MakeActor<Fade>();
		}
	}
	if (2 == m_Count)
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::MINE3);
			Player::CurPlayer->Pos(MineState::MineStartPos);
			Fade* F = _This->Actor()->Parent()->MakeActor<Fade>();
		}
	}
	if (3 == m_Count)
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::MINE4);
			Player::CurPlayer->Pos(MineState::MineStartPos);
			Fade* F = _This->Actor()->Parent()->MakeActor<Fade>();
		}
	}
	if (4 == m_Count)
	{
		if (true == ENTER.DownCondition(L"Enter"))
		{
			CORE.ChangeState(ALLSTATE::MINE5);
			Player::CurPlayer->Pos(MineState::MineStartPos);
			Fade* F = _This->Actor()->Parent()->MakeActor<Fade>();
		}
	}
}

void Ladder::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

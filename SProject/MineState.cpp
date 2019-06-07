#include "stdafx.h"
#include "MineState.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"
#include "MineBack.h"
#include "TimeMgr.h"
#include "Player.h"
#include "SingleActorRender.h"
#include "AniActorRender.h"
#include "GameSprite.h"
#include "MineDoor.h"
#include "MineTile.h"
#include "Fade.h"
#include "Rocks.h"
#include "MouseBaby.h"
#include "MainInButton.h"
#include "QuickInButton.h"
#include "RockEffect.h"
#include "HarvEffect.h"
#include "HandItem.h"
#include "Ladder.h"
#include "MineNum.h"
#include "SoundPlayer.h"
#include "TileActorRender.h"
#include "EnergyAlarm.h"

FPOS MineState::MineStartPos = FPOS::Zero;
SoundPlayer* MineState::MineSp0 = nullptr;

void MineState::ChangeBegin()
{
	MineSp0->NewSoundPlay(L"Mines.wav");

	Player::CurPlayer = OVERPLAYER;
	OVERPLAYER->Pos(StartPlayerPos);

	FPOS BackStartPos = m_MineBack->GetMineBack()->Sprite()->Pos();
	FRECT SetBackRect = { BackStartPos, m_MineBack->GetMineBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_MineTile->MineTileMap());
}

void MineState::ChangeEnd()
{
	SCore::CurState = ALLSTATE::MINE;
}

MineState::MineState()
{
}


MineState::~MineState()
{
}

void MineState::StateInit()
{
	MineSp = GETSOUND;
	MineSp0 = GETSOUND;

	Fade* F = MakeActor<Fade>();

	m_MineBack = MakeActor<MineBack>();
	m_MineTile = MakeActor<MineTile>();
	MineDoor* Door = MakeActor<MineDoor>();
	MakeActor<MouseBaby>();

	MineNum* Num = MakeActor<MineNum>();
	Num->NumRender()->SetSprite(L"MineNum.bmp", 0);
	Num->Pos({ 50, 40 });

	m_Ladder = MakeActor<Ladder>();
	m_Ladder->Pos(Player::IndexWorldPos({ 7, 11 }));

	StartPlayerPos = Player::IndexWorldPos(m_MineTile->PlayerStartIndex());
	OVERPLAYER->Pos(StartPlayerPos);

	Link(L"Door", L"Player");
	Link(L"Inventory", L"Mouse");
	Link(L"Ladder", L"Player");

	FPOS BackStartPos = m_MineBack->GetMineBack()->Sprite()->Pos();
	FPOS BackEndPos = m_MineBack->GetMineBack()->Sprite()->Pos() + m_MineBack->GetMineBack()->Sprite()->Size();

	MainCamera()->Target(OVERPLAYER);
	MainCamera()->SetRange(true);
	MainCamera()->StartPos(BackStartPos);
	MainCamera()->EndPos(BackEndPos);

	//플레이어 배경밖으로 이동 막기
	FRECT SetBackRect = { BackStartPos, m_MineBack->GetMineBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_MineTile->MineTileMap());
}

void MineState::StateUpdate()
{
	if (true == ENTER.DownCondition(L"CollDebug"))
	{
		if (true == DebugRender())
		{
			DebugRender(false);
		}
		else
		{
			DebugRender(true);
		}
	}
	if (true == ENTER.DownCondition(L"CountDebug"))
	{
		if (true == SCore::DebugRenderCheck())
		{
			SCore::DebugRenderOff();
		}
		else
		{
			SCore::DebugRenderOn();
		}
	}
	if (true == ENTER.DownCondition(L"TitleState"))
	{
		CORE.ChangeState(ALLSTATE::TITLE);
	}
	if (true == ENTER.DownCondition(L"RoomState"))
	{
		CORE.ChangeState(ALLSTATE::ROOM);
	}
	if (true == ENTER.DownCondition(L"FarmState"))
	{
		CORE.ChangeState(ALLSTATE::FARM);
	}
	if (true == ENTER.DownCondition(L"TownState"))
	{
		CORE.ChangeState(ALLSTATE::TOWN);
	}
	if (true == ENTER.DownCondition(L"StoreState"))
	{
		CORE.ChangeState(ALLSTATE::STORE);
	}

	m_RectPos = OVERPLAYER->RectPos();
	PlayerAction();
}


void MineState::PlayerAction()
{
	if (true == ENTER.DownCondition(L"Action"))
	{
		switch (OVERPLAYER->PlayerState())
		{
		case Player::PICK:
			break;
		case Player::EAT:
			OVERPLAYER->EatWork(QuickInButton::m_QCount);
			break;
		default:
			break;
		}
		switch (OVERPLAYER->PlayerItem())
		{
		case Player::PICKAXE:
			PickAxeWork(m_RectPos);
			break;
		case Player::SICKLE:
			break;
		case Player::RUSTYSWORD:
			break;
		case Player::RAPIER:
			break;
		case Player::PIRATESWORD:
			break;
		case Player::GALAXYSWORD:
			break;
		case Player::CLAYMORE:
			break;
		default:
			break;
		}
	}
}

void MineState::PlayerDirCheck(IPOS _Pos)
{
	IPOS DirCheckPos = Player::WorldPlayerIndex(OVERPLAYER->Pos());
	if (_Pos.Y < DirCheckPos.Y)
	{
		OVERPLAYER->PlayerDir(L"Up");
	}
	else if (_Pos.Y > DirCheckPos.Y)
	{
		OVERPLAYER->PlayerDir(L"Down");
	}
	if (_Pos.Y == DirCheckPos.Y && _Pos.X < DirCheckPos.X)
	{
		OVERPLAYER->PlayerDir(L"Left");
	}
	else if (_Pos.Y == DirCheckPos.Y && _Pos.X > DirCheckPos.X)
	{
		OVERPLAYER->PlayerDir(L"Right");
	}
}

void MineState::PickAxeWork(IPOS _Pos)
{
	PlayerDirCheck(_Pos);
	m_RFindIter = m_RockMap.find(_Pos);
	if (m_RFindIter == m_RockMap.end())
	{
		return;
	}

	if (nullptr != m_RFindIter->second)
	{
		const WCHAR* Name = ITEM.GetItem(4, m_RFindIter->second->RockAniRender()->AniNum())->m_SpriteName.c_str();
		int Num = ITEM.GetItem(4, m_RFindIter->second->RockAniRender()->AniNum())->m_SpriteNum;

		bool RockCheck = OVERPLAYER->PutItem(ITEM.GetItem(4, m_RFindIter->second->RockAniRender()->AniNum())->m_ItemName.c_str());
		if (true == RockCheck)
		{
			MineSp->NewSoundPlay(L"take_stone.wav");

			RockEffect* RockEf = MakeActor<RockEffect>();
			RockEf->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y });

			m_HEffect = MakeActor<HarvEffect>();
			m_HEffect->HarvRender()->SetSprite(Name, Num);
			m_HEffect->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y - 15 });

			m_RFindIter->second->Die();
			m_RockMap.erase(m_RFindIter);

			if (false == OVERPLAYER->ReducePlayerEnergy(3))
			{
				OVERPLAYER->ReducePlayerEnergy(3);
			}
			m_MineTile->MineTileMap()->SetTile(_Pos, 5);
		}
	}
}

void MineState::DebugUpdate()
{
	//WCHAR OutText[100]{};
	//swprintf_s(OutText, L"MineState");
	//TextOutW(BHDC, 5, 0, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"FPS %d", FPSTIME);
	//TextOutW(BHDC, 5, 20, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"AllActor %d", AllActorCount());
	//TextOutW(BHDC, 5, 40, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Mouse X : %d, Y : %d ", MOUSEI.X, MOUSEI.Y);
	//TextOutW(BHDC, 5, 60, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"PlayerState %d ", OVERPLAYER->PlayerState());
	//TextOutW(BHDC, 5, 100, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"PlayerItem %d ", OVERPLAYER->PlayerItem());
	//TextOutW(BHDC, 5, 120, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"PlayerHp %d ", OVERPLAYER->PlayerEnergy());
	//TextOutW(BHDC, 5, 140, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Player X : %f, Y : %f ", OVERPLAYER->Pos().X, OVERPLAYER->Pos().Y);
	//TextOutW(BHDC, 5, 160, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Rect Index X : %d, Y : %d ", OVERPLAYER->RectPos().X, OVERPLAYER->RectPos().Y);
	//TextOutW(BHDC, 5, 180, OutText, lstrlenW(OutText));
}

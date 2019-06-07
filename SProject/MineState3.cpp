#include "stdafx.h"
#include "MineState3.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"
#include "MineBack.h"
#include "TimeMgr.h"
#include "Player.h"
#include "SingleActorRender.h"
#include "AniActorRender.h"
#include "GameSprite.h"
#include "Monster.h"
#include "MineDoor.h"
#include "MineTile3.h"
#include "Fade.h"
#include "Rocks.h"
#include "MouseBaby.h"
#include "MainInButton.h"
#include "QuickInButton.h"
#include "RockEffect.h"
#include "HarvEffect.h"
#include "HandItem.h"
#include "MineNum.h"
#include "Ladder.h"
#include "SoundPlayer.h"
#include "TileActorRender.h"
#include "RockBoomEffect.h"
#include "EnergyAlarm.h"

void MineState3::ChangeBegin()
{
	Player::CurPlayer = OVERPLAYER;
	OVERPLAYER->Pos(StartPlayerPos);

	FPOS BackStartPos = m_MineBack->GetMineBack()->Sprite()->Pos();
	FRECT SetBackRect = { BackStartPos, m_MineBack->GetMineBack()->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_MineTile->MineTileMap());
}

void MineState3::ChangeEnd()
{
	SCore::CurState = ALLSTATE::MINE;
}

MineState3::MineState3()
{
}


MineState3::~MineState3()
{
}

void MineState3::StateInit()
{
	Mine3Sp = GETSOUND;

	MineNum* Num = MakeActor<MineNum>();
	Num->NumRender()->SetSprite(L"MineNum.bmp", 3);
	Num->Pos({ 50, 40 });

	Ladder* m_Ladder = MakeActor<Ladder>();
	m_Ladder->Pos(Player::IndexWorldPos({ 8, 10 }));
	m_Ladder->m_Count = 3;

	Fade* F = MakeActor<Fade>();

	m_MineBack = MakeActor<MineBack>();
	m_MineTile = MakeActor<MineTile3>();
	MineDoor* Door = MakeActor<MineDoor>();
	MakeActor<MouseBaby>();

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

	RockInit();
}

void MineState3::RockInit()
{
	for (size_t i = 0; i < m_MineTile->m_RockPosVec.size(); i++)
	{
		Rocks* DefaultRocks = MakeActor<Rocks>();
		DefaultRocks->Pos(Player::IndexWorldPos(m_MineTile->m_RockPosVec[i]));
		DefaultRocks->RockAniRender()->ChangeAni(DefaultRocks->ArrCropName[rand() % 7].c_str());
		m_RockMap.insert(std::map<__int64, Rocks*>::value_type(m_MineTile->m_RockPosVec[i], DefaultRocks));
	}
}

void MineState3::StateUpdate()
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


void MineState3::PlayerAction()
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

void MineState3::PlayerDirCheck(IPOS _Pos)
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


void MineState3::PickAxeWork(IPOS _Pos)
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
			Mine3Sp->NewSoundPlay(L"take_stone.wav");

			RockEffect* RockEf = MakeActor<RockEffect>();
			RockEf->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y });
			RockBoomEffect* BoomEf = MakeActor<RockBoomEffect>();
			BoomEf->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y });

			m_HEffect = MakeActor<HarvEffect>();
			m_HEffect->HarvRender()->SetSprite(Name, Num);
			m_HEffect->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y - 15 });

			m_RFindIter->second->Die();
			m_RockMap.erase(m_RFindIter);

			m_MineTile->MineTileMap()->SetTile(_Pos, 5);
			if (false == OVERPLAYER->ReducePlayerEnergy(3))
			{
				EnergyAlarm* EnergyAl = MakeActor<EnergyAlarm>();
			}
		}
	}
}

void MineState3::DebugUpdate()
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
	////swprintf_s(OutText, L"MonsterState %d ", m_MainMonster->MonsterState());
	////TextOutW(BHDC, 5, 80, OutText, lstrlenW(OutText));
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

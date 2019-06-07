#include "stdafx.h"
#include "FarmState.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"
#include "TimeMgr.h"
#include "MathMgr.h"
#include "GameSprite.h"
#include "SingleActorRender.h"
#include "AniActorRender.h"
#include "TileActorRender.h"

#include "Player.h"
#include "MouseBaby.h"
#include "Fade.h"
#include "FarmTile.h"
#include "FarmBack.h"
#include "FarmDoor.h"
#include "Soil.h"
#include "Crops.h"
#include "Rocks.h"
#include "TreeBot.h"
#include "TreeTop.h"
#include "HarvEffect.h"
#include "DirtEffect.h"
#include "RockEffect.h"
#include "WaterEffect.h"
#include "HandItem.h"
#include "MainInButton.h"
#include "QuickInButton.h"
#include "CoopRender.h"
#include "BarnRender.h"
#include "SoundPlayer.h"
#include "GreenEffect.h"
#include "RockBoomEffect.h"
#include "EnergyAlarm.h"

int FarmState::AxeCount = 0;
BarnRender* FarmState::BRender = nullptr;
CoopRender* FarmState::CRender = nullptr;

FarmState::FarmState()
{
}

FarmState::~FarmState()
{
}

void FarmState::ChangeBegin()
{
	FarmSp2->NewSoundPlay(L"Farm.wav");

	Player::CurPlayer = OVERPLAYER;
	FPOS BackStartPos = FarmBack::m_FarmBack->Sprite()->Pos();
	FRECT SetBackRect = { BackStartPos, FarmBack::m_FarmBack->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_FarmTile->FarmTileMap());

	if (ALLSTATE::ROOM == SCore::CurState)
	{
		OVERPLAYER->Pos(StartPlayerPos);
	}
	else if(ALLSTATE::TOWN == SCore::CurState)
	{
		OVERPLAYER->Pos(FPOS{ 2160, 1200 });
	}
	else if (ALLSTATE::BARN == SCore::CurState)
	{
		OVERPLAYER->Pos(FPOS{ 400, 1040 });
	}
	else
	{
		OVERPLAYER->Pos(FPOS{ 980, 1040 });
	}
}

void FarmState::ChangeEnd()
{
	SCore::CurState = ALLSTATE::FARM;
	FarmSp2->Stop();
}

void FarmState::StateInit()
{
	FarmSp = GETSOUND;
	FarmSp2 = GETSOUND;

	YsortOn(10);

	Fade* F = MakeActor<Fade>();
	MakeActor<MouseBaby>();
	m_FarmBack = MakeActor<FarmBack>();
	m_FarmTile = MakeActor<FarmTile>();
	FarmDoor* Door = MakeActor<FarmDoor>();
	FarmState::CRender = MakeActor<CoopRender>();
	FarmState::CRender->Off();
	FarmState::BRender = MakeActor<BarnRender>();
	FarmState::BRender->Off();

	StartPlayerPos = Player::IndexWorldPos(m_FarmTile->PlayerStartIndex());
	OVERPLAYER->Pos(StartPlayerPos);

	Link(L"Door", L"Player");
	Link(L"Inventory", L"Mouse");
	Link(L"Tree", L"Player");

	FPOS BackStartPos = FarmBack::m_FarmBack->Sprite()->Pos();
	FPOS BackEndPos = FarmBack::m_FarmBack->Sprite()->Pos() + FarmBack::m_FarmBack->Sprite()->Size();
	
	MainCamera()->Target(OVERPLAYER);
	MainCamera()->SetRange(true);
	MainCamera()->StartPos(BackStartPos);
	MainCamera()->EndPos(BackEndPos);

	//플레이어 배경밖으로 이동 막기
	FRECT SetBackRect = { BackStartPos, FarmBack::m_FarmBack->Sprite()->Size() };
	OVERPLAYER->BackRect(SetBackRect);
	OVERPLAYER->SetPlayerTile(m_FarmTile->FarmTileMap());

	TreeInit();
	RockInit();
}

void FarmState::StateUpdate()
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
	if (true == KEYDOWN("TitleState"))
	{
		CORE.ChangeState(ALLSTATE::TITLE);
	}
	if (true == KEYDOWN("RoomState"))
	{
		CORE.ChangeState(ALLSTATE::ROOM);
	}
	if (true == KEYDOWN("TownState"))
	{
		CORE.ChangeState(ALLSTATE::TOWN);
	}
	if (true == KEYDOWN("MineState"))
	{
		CORE.ChangeState(ALLSTATE::MINE);
	}
	if (true == KEYDOWN("StoreState"))
	{
		CORE.ChangeState(ALLSTATE::STORE);
	}
	if (true == ENTER.DownCondition(L"EditState"))
	{
		CORE.ChangeState(ALLSTATE::EDIT);
	}

	m_RectPos = OVERPLAYER->RectPos();
	PlayerAction();
}

void FarmState::RockInit()
{
	for (size_t i = 0; i < m_FarmTile->m_RockPosVec.size(); i++)
	{
		Rocks* DefaultRocks = MakeActor<Rocks>();
		DefaultRocks->Pos(Player::IndexWorldPos(m_FarmTile->m_RockPosVec[i]));
		m_RockMap.insert(std::map<__int64, Rocks*>::value_type(m_FarmTile->m_RockPosVec[i], DefaultRocks));
		if (0 == i % 2)
		{
			DefaultRocks->RockAniRender()->ChangeAni(L"RockOne");
		}
		else
		{
			DefaultRocks->RockAniRender()->ChangeAni(L"RockTwo");
		}
	}
}

void FarmState::TreeInit()
{
	for (size_t i = 0; i < m_FarmTile->m_TreePosVec.size(); i++)
	{
		TreeBot* DefaultTreeBot = MakeActor<TreeBot>();
		TreeTop* DefaultTreesTop = MakeActor<TreeTop>();
		
		DefaultTreeBot->Pos(Player::IndexWorldPos(m_FarmTile->m_TreePosVec[i]));
		DefaultTreesTop->Pos(Player::IndexWorldPos(m_FarmTile->m_TreePosVec[i]));

		m_TreeTopMap.insert(std::map<__int64, TreeTop*>::value_type(m_FarmTile->m_TreePosVec[i], DefaultTreesTop));
		m_TreeBotMap.insert(std::map<__int64, TreeBot*>::value_type(m_FarmTile->m_TreePosVec[i], DefaultTreeBot));
		
		int TreeType = rand() % 3;
		if (0 == TreeType)
		{
			DefaultTreesTop->TreeAniTopRender()->ChangeAni(L"MapleTreeTop");
			DefaultTreeBot->TreeAniBotRnder()->ChangeAni(L"MapleTreeBot");
			DefaultTreesTop->TreeType(0);
		}
		else if (1 == TreeType)
		{
			DefaultTreesTop->TreeAniTopRender()->ChangeAni(L"AcronTreeTop");
			DefaultTreeBot->TreeAniBotRnder()->ChangeAni(L"AcronTreeBot");
			DefaultTreesTop->TreeType(1);
		}
		else if (2 == TreeType)
		{
			DefaultTreesTop->TreeAniTopRender()->ChangeAni(L"PineTreeTop");
			DefaultTreeBot->TreeAniBotRnder()->ChangeAni(L"PineTreeBot");
			DefaultTreesTop->TreeType(2);
		}
	}
}

void FarmState::PlayerAction()
{
	if (true == ENTER.DownCondition(L"Action"))
	{
		switch (OVERPLAYER->PlayerState())
		{
		case Player::PICK:
			CropsWork(m_RectPos, QuickInButton::m_QCount);
			break;
		case Player::EAT:
			OVERPLAYER->EatWork(QuickInButton::m_QCount);
			break;
		default:
			break;
		}
		switch (OVERPLAYER->PlayerItem())
		{
		case Player::AXE:
			FarmSp->NewSoundPlay(L"take_tree.wav");
			ShakeTree(m_RectPos);
			if (3 == AxeCount)
			{
				GreenEffect* TestEf = MakeActor<GreenEffect>();
				TestEf->Pos({ m_RectPos.X, m_RectPos.Y - TILESIZE });
				AxeWork(m_RectPos);
				AxeCount = 0;
			}
			++AxeCount;
			break;
		case Player::HOE:
			if (true == OVERPLAYER->MainPlayerRender()->AniStartCheck())
			{
				HoeWork(m_RectPos);
			}
			break;
		case Player::PICKAXE:
			PickAxeWork(m_RectPos);
			break;
		case Player::SICKLE:
			break;
		case Player::WATERCAN:
			WaterWork(m_RectPos);
			break;
		default:
			break;
		}
		Harvest(m_RectPos);
	}
}

void FarmState::PlayerDirCheck(IPOS _Pos)
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

void FarmState::ShakeTree(IPOS _Pos)
{
	m_TBFindIter = m_TreeBotMap.find(_Pos);
	m_TTFindIter = m_TreeTopMap.find(_Pos);

	if (m_TTFindIter != m_TreeTopMap.end() && m_TBFindIter != m_TreeBotMap.end())
	{
		GreenEffect* TestEf1 = MakeActor<GreenEffect>();
		TestEf1->Pos({ m_TTFindIter->second->Pos().X - TILESIZE, m_TTFindIter->second->Pos().Y - TILESIZE });
		GreenEffect* TestEf2 = MakeActor<GreenEffect>();
		TestEf2->Pos({ m_TTFindIter->second->Pos().X + TILESIZE, m_TTFindIter->second->Pos().Y - TILESIZE });

		switch (m_TTFindIter->second->TreeType())
		{
		case 0:
			m_TTFindIter->second->TreeAniTopRender()->ChangeAni(L"MapleTreeTop1");
			break;
		case 1:
			m_TTFindIter->second->TreeAniTopRender()->ChangeAni(L"AcronTreeTop1");
			break;
		case 2:
			m_TTFindIter->second->TreeAniTopRender()->ChangeAni(L"PineTreeTop1");
			break;
		default:
			break;
		}
	}
}

void FarmState::PickAxeWork(IPOS _Pos)
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
			FarmSp->NewSoundPlay(L"take_stone.wav");

			RockEffect* RockEf = MakeActor<RockEffect>();
			RockEf->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y});

			RockBoomEffect* BoomEf = MakeActor<RockBoomEffect>();
			BoomEf->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y });

			m_HEffect = MakeActor<HarvEffect>();
			m_HEffect->HarvRender()->SetSprite(Name, Num);
			m_HEffect->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y - 15 });
			m_FarmTile->FarmTileMap()->SetTile(_Pos, 5);

			m_RFindIter->second->Die();
			m_RockMap.erase(m_RFindIter);

			if (false == OVERPLAYER->ReducePlayerEnergy(3))
			{
				EnergyAlarm* EnergyAl = MakeActor<EnergyAlarm>();
			}
		}
	}
}

void FarmState::AxeWork(IPOS _Pos)
{
	m_TTFindIter = m_TreeTopMap.find(_Pos);
	m_TBFindIter = m_TreeBotMap.find(_Pos);

	if (m_TTFindIter != m_TreeTopMap.end() && m_TBFindIter != m_TreeBotMap.end())
	{
		bool HarvestCheck = OVERPLAYER->PutItem(L"Wood");
		if (true == HarvestCheck)
		{
			m_HEffect = MakeActor<HarvEffect>();
			m_HEffect->HarvRender()->SetSprite(L"Spring.bmp", 388);
			m_HEffect->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y - 15 });

			m_TTFindIter->second->Die();
			m_TreeTopMap.erase(m_TTFindIter);
		}
	}
	else if (m_TTFindIter == m_TreeTopMap.end() && m_TBFindIter != m_TreeBotMap.end())
	{
		bool HarvestCheck = OVERPLAYER->PutItem(L"Wood");
		if (true == HarvestCheck)
		{
			m_HEffect = MakeActor<HarvEffect>();
			m_HEffect->HarvRender()->SetSprite(L"Spring.bmp", 388);
			m_HEffect->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y - 15 });

			m_TBFindIter->second->Die();
			m_TreeBotMap.erase(m_TBFindIter);

			m_FarmTile->FarmTileMap()->SetTile(_Pos, 5);
			if (false == OVERPLAYER->ReducePlayerEnergy(3))
			{
				EnergyAlarm* EnergyAl = MakeActor<EnergyAlarm>();
			}
		}
	}
}

void FarmState::CropsWork(IPOS _Pos, int _InvenNum)
{
	PlayerDirCheck(_Pos);
	m_SFindIter = m_SoilMap.find(_Pos);
	m_CFindIter = m_CropsMap.find(_Pos);

	if (m_SFindIter != m_SoilMap.end() && m_CFindIter == m_CropsMap.end())
	{
		//들고있는 아이템이 null 이 아니고 씨앗일때만
		if (nullptr != OVERPLAYER->MainHandItem()->PlayerHandItem() && 0 == OVERPLAYER->MainHandItem()->PlayerHandItem()->m_ItemType)
		{
			FarmSp->NewSoundPlay(L"Crop.wav");

			Crops* NewCrops = MakeActor<Crops>();
			std::wstring SeedName = OVERPLAYER->MainHandItem()->PlayerHandItem()->m_ItemName;

			size_t SCount = SeedName.find_last_of(L'S', SeedName.size());
			SeedName.erase(SCount);
			SeedName += L"1";
			NewCrops->CropsAni()->ChangeAni(SeedName.c_str());
			m_CropsMap.insert(std::map<__int64, Crops*>::value_type(_Pos, NewCrops));
			NewCrops->Pos(Player::IndexWorldPos(_Pos));

			OVERPLAYER->RemoveItem(_InvenNum);
			OVERPLAYER->MainHandItem()->HandRender()->Off();
			OVERPLAYER->MainHandItem()->PlayerHandItem(nullptr);

			if (false == OVERPLAYER->ReducePlayerEnergy(3))
			{
				EnergyAlarm* EnergyAl = MakeActor<EnergyAlarm>();
			}
		}
	}
}

void FarmState::Harvest(IPOS _Pos)
{
	//작물맵에서 찾기
	m_CFindIter = m_CropsMap.find(_Pos);
	//없으면
	if (m_CFindIter == m_CropsMap.end())
	{
		return;
	}
	//작물이 있고 그 작물의 애니메이션이 끝났다면
	if (true == m_CFindIter->second->CropsAni()->AniEndCheck())
	{
		//수확애니메이션 실행하고 아이템 획득하고 땅에서는 없애줘야함.
		const WCHAR* Name = ITEM.GetItem(1, m_CFindIter->second->CropsAni()->AniNum())->m_SpriteName.c_str();
		int Num = ITEM.GetItem(1, m_CFindIter->second->CropsAni()->AniNum())->m_SpriteNum;

		bool HarvestCheck = OVERPLAYER->PutItem(ITEM.GetItem(1, m_CFindIter->second->CropsAni()->AniNum())->m_ItemName.c_str());
		if (true == HarvestCheck)
		{
			FarmSp->NewSoundPlay(L"take_crop.wav");

			m_HEffect = MakeActor<HarvEffect>();
			m_HEffect->HarvRender()->SetSprite(Name, Num);
			m_HEffect->Pos({ Player::IndexWorldPos(_Pos).X, Player::IndexWorldPos(_Pos).Y - 15 });

			m_CFindIter->second->Die();
			m_CropsMap.erase(m_CFindIter);
			if (false == OVERPLAYER->ReducePlayerEnergy(3))
			{
				EnergyAlarm* EnergyAl = MakeActor<EnergyAlarm>();
			}
		}
	}
}

void FarmState::HoeWork(IPOS _Pos)
{
	PlayerDirCheck(_Pos);
	m_SFindIter = m_SoilMap.find(_Pos);

	//타일이 없는 곳에만
	if (-1 == m_FarmTile->FarmTileMap()->FindSpriteIndex(_Pos))
	{
		//그 위치에 땅이 hoedirt가 아닐때만
		if (m_SFindIter == m_SoilMap.end())
		{
			FarmSp->NewSoundPlay(L"Dig_Ground.wav");
			Soil* HoeSoil = MakeActor<Soil>();
			m_SoilMap.insert(std::map<__int64, Soil*>::value_type(_Pos, HoeSoil));
			HoeSoil->Pos(Player::IndexWorldPos(_Pos));

			DirtEffect* DirtEf = MakeActor<DirtEffect>();
			DirtEf->Pos(Player::IndexWorldPos(_Pos));
			if (false == OVERPLAYER->ReducePlayerEnergy(3))
			{
				EnergyAlarm* EnergyAl = MakeActor<EnergyAlarm>();
			}
		}
	}
}

void FarmState::WaterWork(IPOS _Pos)
{
	PlayerDirCheck(_Pos);
	m_SFindIter = m_SoilMap.find(_Pos);
	m_WFindIter = m_WaterMap.find(_Pos);
	m_CFindIter = m_CropsMap.find(_Pos);


	if (m_SFindIter != m_SoilMap.end())
	{
		if (m_CFindIter != m_CropsMap.end())
		{
			FarmSp->NewSoundPlay(L"watercan.wav");
			Soil* WaterSoil = MakeActor<Soil>();
			WaterSoil->SoilAni()->ChangeAni(L"WaterDirt");
			m_WaterMap.insert(std::map<__int64, Soil*>::value_type(_Pos, WaterSoil));
			WaterSoil->Pos(Player::IndexWorldPos(_Pos));

			WaterEffect* WaterEf = MakeActor<WaterEffect>();
			WaterEf->Pos(Player::IndexWorldPos(_Pos));

			if (false == OVERPLAYER->ReducePlayerEnergy(3))
			{
				EnergyAlarm* EnergyAl = MakeActor<EnergyAlarm>();
			}

			if (m_WFindIter == m_WaterMap.end())
			{
				std::wstring TempName = m_CFindIter->second->CropsAni()->AniName();
				size_t SCount = TempName.find_last_of(L'1', TempName.size());
				TempName.erase(SCount);
				m_CFindIter->second->CropsAni()->ChangeAni(TempName.c_str());
			}
		}
	}
}

void FarmState::DebugUpdate()
{
	//WCHAR OutText[100]{};
	//swprintf_s(OutText, L"FarmState");
	//TextOutW(BHDC, 5, 0, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"FPS %d", FPSTIME);
	//TextOutW(BHDC, 5, 20, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"AllActor %d", AllActorCount());
	//TextOutW(BHDC, 5, 40, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Mouse X : %d, Y : %d ", MOUSEI.X, MOUSEI.Y);
	//TextOutW(BHDC, 5, 60, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Player X : %f, Y : %f ", OVERPLAYER->Pos().X, OVERPLAYER->Pos().Y);
	//TextOutW(BHDC, 5, 80, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Camera X : %f, Y : %f ", MainCamera()->CameraPos().X, MainCamera()->CameraPos().Y);
	//TextOutW(BHDC, 5, 100, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Screen X : %f, Y : %f ", OVERPLAYER->ScreenPos().X, OVERPLAYER->ScreenPos().Y);
	//TextOutW(BHDC, 5, 120, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"PlayerState %d ", OVERPLAYER->PlayerState());
	//TextOutW(BHDC, 5, 140, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"PlayerItem %d ", OVERPLAYER->PlayerItem());
	//TextOutW(BHDC, 5, 160, OutText, lstrlenW(OutText));

	//swprintf_s(OutText, L"World Index X : %d, Y : %d ", Player::WorldPlayerIndex(OVERPLAYER->Pos()).X, Player::WorldPlayerIndex(OVERPLAYER->Pos()).Y);
	//TextOutW(BHDC, 5, 180, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Rect Index X : %d, Y : %d ", OVERPLAYER->RectPos().X, OVERPLAYER->RectPos().Y);
	//TextOutW(BHDC, 5, 200, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"TileSpriteIndex %d ", m_FarmTile->FarmTileMap()->FindSpriteIndex(OVERPLAYER->RectPos()));
	//TextOutW(BHDC, 5, 220, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"ItemMapSize %d ", OVERPLAYER->ItemVecSize());
	//TextOutW(BHDC, 5, 240, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"HandItem %d ", OVERPLAYER->MainHandItem()->HandItemCheck());
	//TextOutW(BHDC, 5, 260, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"InvenCount %d ", MainInButton::m_InvenCount);
	//TextOutW(BHDC, 5, 280, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"ChangeInvenCount %d ", MainInButton::m_ChangeInvenCount);
	//TextOutW(BHDC, 5, 300, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"Energy %d ", OVERPLAYER->PlayerEnergy());
	//TextOutW(BHDC, 5, 320, OutText, lstrlenW(OutText));
	//swprintf_s(OutText, L"QuickInvenCount %d ", QuickInButton::m_QCount);
	//TextOutW(BHDC, 5, 340, OutText, lstrlenW(OutText));

	//swprintf_s(OutText, L" X : %f, Y : %f ", OVERPLAYER->MainPlayerRender()->GetRenderPos().X, OVERPLAYER->MainPlayerRender()->GetRenderPos().Y);
	//TextOutW(BHDC, 5, 360, OutText, lstrlenW(OutText));
}


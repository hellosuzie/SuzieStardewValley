#include "stdafx.h"
#include "Player.h"
#include "EnterMgr.h"
#include "TimeMgr.h"
#include "MathMgr.h"
#include "ButtonMgr.h"

#include "SingleActorRender.h"
#include "TileActorRender.h"
#include "AniActorRender.h"
#include "ActorCollision.h"
#include "GameSprite.h"
#include "HPBar.h"
#include "Clock.h"
#include "QuickInvenBack.h"
#include "MainInvenBack.h"
#include "MainInButton.h"
#include "QuickInButton.h"
#include "SelectRender.h"
#include "FullAlarm.h"
#include "HandItem.h"
#include "InfoRender.h"
#include "NumberActor.h"
#include "SecondNumberActor.h"
#include "ResourceMgr.h"
#include "ClockNumber.h"
#include "Monster.h"
#include "ItemMgr.h"
#include "MonsterDamage.h"
#include "SoundPlayer.h"

Player* Player::CurPlayer;
int Player::m_StartCount = 0;
int Player::m_ChangeCount = 0;
bool Player::m_SwapCheck = true;

Player::Player() : m_Speed(1800.0f), m_Energy(200), m_Money(100000), m_InvenCheck(false)
{
	m_MainInButtonVec.reserve(36);
	m_QuickInButtonVec.reserve(12);
}

Player::~Player()
{
}

void Player::SetMainHandItem(ItemMgr::ItemInfo * _Item)
{
	m_MainHandItem->PlayerHandItem(_Item);
}

IPOS Player::WorldPlayerIndex(FPOS _WorldPos)
{
	IPOS PosIndex = { (int)(_WorldPos.X / TILESIZE), (int)(_WorldPos.Y / TILESIZE) };
	return PosIndex;
}

FPOS Player::IndexWorldPos(IPOS _Index)
{
	FPOS IndexPos = { (float)(_Index.X * TILESIZE) + TILESIZEH, (float)(_Index.Y * TILESIZE) + TILESIZEH };
	return IndexPos;
}

void Player::Init()
{
	PlayerSp = GETSOUND;

	m_MainPlayerRender = MakeRender<AniActorRender>(10);
	m_MainPlayerRender->Size(FSIZE{ 64, 128 });
	m_MainPlayerRender->Debug = true;

	m_MainItemRender = MakeRender<AniActorRender>(10);
	m_MainItemRender->Size(FSIZE{ 192, 192 });

	ActorCollision* PlayerColl = MakeCollision(L"Player", { 64, 128 }, 101);
	MakePlayerAni();

	m_LColl = MakeCollision(L"PlayerCheck", { 5, 5 }, 33);
	m_LColl->Pivot({ -PLAYERSIZEXH + 2, 0 });
	m_LSColl = MakeCollision(L"PlayerCheck", { 5, 5 }, 33);
	m_LSColl->Pivot({ -PLAYERSIZEXH + 2, PLAYERSIZEYH - 10 });

	m_RColl = MakeCollision(L"PlayerCheck", { 5, 5 }, 33);
	m_RColl->Pivot({ PLAYERSIZEXH - 2, 0 });
	m_RSColl = MakeCollision(L"PlayerCheck", { 5, 5 }, 33);
	m_RSColl->Pivot({ PLAYERSIZEXH - 2, PLAYERSIZEYH -10 });

	m_UColl = MakeCollision(L"PlayerCheck", { 5, 5 }, 33);
	m_UColl->Pivot({ 20, -2 });
	m_USColl = MakeCollision(L"PlayerCheck", { 5, 5 }, 33);
	m_USColl->Pivot({ -20, -2 });

	m_DColl = MakeCollision(L"PlayerCheck", { 5, 5 }, 33);
	m_DColl->Pivot({ 20, PLAYERSIZEYH - 2 });
	m_DSColl = MakeCollision(L"PlayerCheck", { 5, 5 }, 33);
	m_DSColl->Pivot({ -20, PLAYERSIZEYH - 2 });

	m_PlayerAniName[STAY] = L"StayBody";
	m_PlayerAniName[WALK] = L"WalkBody";
	m_PlayerAniName[PICKWALK] = L"PickWalkBody";
	m_PlayerAniName[EAT] = L"EatBody";
	m_PlayerAniName[PICK] = L"PickBody";
	m_PlayerAniName[TOOL] = L"ToolBody";
	m_PlayerAniName[WEAPON] = L"WeaponBody";
	m_PlayerAniName[WATER] = L"WaterBody";
	m_PlayerAniName[RIDE] = L"RideBody";

	m_ItemAniName[AXE] = L"Axe";
	m_ItemAniName[HOE] = L"Hoe";
	m_ItemAniName[PICKAXE] = L"Pick";
	m_ItemAniName[SICKLE] = L"Sickle";
	m_ItemAniName[WATERCAN] = L"Watercan";
	m_ItemAniName[RUSTYSWORD] = L"Rustysword";
	m_ItemAniName[RAPIER] = L"Rapier";
	m_ItemAniName[PIRATESWORD] = L"Piratesword";
	m_ItemAniName[GALAXYSWORD] = L"Galaxysword";
	m_ItemAniName[CLAYMORE] = L"Claymore";
	m_ItemAniName[HORSE] = L"Horse";

	m_PlayerDir = L"Left";
	ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
	ChangePlayerAni(PLAYERSTATE::STAY, PLAYERTOOL::NONE);

	m_HpBar = Parent()->MakeActor<HPBar>(200);
	m_HpBar->StateOverOn(
		ALLSTATE::FARM
		, ALLSTATE::TOWN
		, ALLSTATE::STORE
		, ALLSTATE::MINE
		, ALLSTATE::MINE1
		, ALLSTATE::MINE2
		, ALLSTATE::MINE3
		, ALLSTATE::MINE4
		, ALLSTATE::MINE5
		, ALLSTATE::TOWN2
		, ALLSTATE::COOP
		, ALLSTATE::BARN
		, ALLSTATE::MANI
		, ALLSTATE::ROBIN);

	m_Clock = Parent()->MakeActor<Clock>();
	m_Clock->ClockRender()->SetSprite(L"Clock.bmp", 0);
	m_Clock->StateOverOn(
		ALLSTATE::FARM
		, ALLSTATE::TOWN
		, ALLSTATE::STORE
		, ALLSTATE::MINE
		, ALLSTATE::MINE1
		, ALLSTATE::MINE2
		, ALLSTATE::MINE3
		, ALLSTATE::MINE4
		, ALLSTATE::MINE5
		, ALLSTATE::TOWN2
		, ALLSTATE::COOP
		, ALLSTATE::BARN
		, ALLSTATE::MANI
		, ALLSTATE::ROBIN);

	ClockNumber* CNum = Parent()->MakeActor<ClockNumber>();
	CNum->StateOverOn(
		ALLSTATE::FARM
		, ALLSTATE::TOWN
		, ALLSTATE::STORE
		, ALLSTATE::MINE
		, ALLSTATE::MINE1
		, ALLSTATE::MINE2
		, ALLSTATE::MINE3
		, ALLSTATE::MINE4
		, ALLSTATE::MINE5
		, ALLSTATE::TOWN2
		, ALLSTATE::COOP
		, ALLSTATE::BARN
		, ALLSTATE::MANI
		, ALLSTATE::ROBIN);

	m_NActor = Parent()->MakeActor<NumberActor>();
	m_NActor->NumberInit(8, L"Number.bmp", { 20, 24 });
	m_NActor->Pos({ 855, 167 });
	m_NActor->Value(m_Money);
	m_NActor->StateOverOn(
		ALLSTATE::FARM
		, ALLSTATE::TOWN
		, ALLSTATE::STORE
		, ALLSTATE::MINE
		, ALLSTATE::MINE1
		, ALLSTATE::MINE2
		, ALLSTATE::MINE3
		, ALLSTATE::MINE4
		, ALLSTATE::MINE5
		, ALLSTATE::TOWN2
		, ALLSTATE::COOP
		, ALLSTATE::BARN
		, ALLSTATE::MANI
		, ALLSTATE::ROBIN);

	m_NActor2 = Parent()->MakeActor<SecondNumberActor>();
	m_NActor2->NumberInit(8, L"Number.bmp", { 20, 24 });
	m_NActor2->Pos({ 645, 134 });
	m_NActor->Value(m_Money);
	m_NActor2->Off();
	m_NActor2->StateOverOn(
		ALLSTATE::FARM
		, ALLSTATE::TOWN
		, ALLSTATE::STORE
		, ALLSTATE::MINE
		, ALLSTATE::MINE1
		, ALLSTATE::MINE2
		, ALLSTATE::MINE3
		, ALLSTATE::MINE4
		, ALLSTATE::MINE5
		, ALLSTATE::TOWN2
		, ALLSTATE::COOP
		, ALLSTATE::BARN
		, ALLSTATE::MANI
		, ALLSTATE::ROBIN);

	m_SelectRenderer = Parent()->MakeActor<SelectRender>();
	m_SelectRenderer->StateOverOn(
		ALLSTATE::FARM
		, ALLSTATE::TOWN
		, ALLSTATE::STORE
		, ALLSTATE::MINE
		, ALLSTATE::MINE1
		, ALLSTATE::MINE2
		, ALLSTATE::MINE3
		, ALLSTATE::MINE4
		, ALLSTATE::MINE5
		, ALLSTATE::TOWN2
		, ALLSTATE::COOP
		, ALLSTATE::BARN
		, ALLSTATE::MANI
		, ALLSTATE::ROBIN);

	m_QuickInven = Parent()->MakeActor<QuickInvenBack>();
	m_QuickInven->StateOverOn(
		ALLSTATE::FARM
		, ALLSTATE::TOWN
		, ALLSTATE::STORE
		, ALLSTATE::MINE
		, ALLSTATE::MINE1
		, ALLSTATE::MINE2
		, ALLSTATE::MINE3
		, ALLSTATE::MINE4
		, ALLSTATE::MINE5
		, ALLSTATE::TOWN2
		, ALLSTATE::COOP
		, ALLSTATE::BARN
		, ALLSTATE::MANI
		, ALLSTATE::ROBIN);

	m_MainInven = Parent()->MakeActor<MainInvenBack>();
	m_MainInven->StateOverOn(
		ALLSTATE::FARM
		, ALLSTATE::TOWN
		, ALLSTATE::STORE
		, ALLSTATE::MINE
		, ALLSTATE::MINE1
		, ALLSTATE::MINE2
		, ALLSTATE::MINE3
		, ALLSTATE::MINE4
		, ALLSTATE::MINE5
		, ALLSTATE::TOWN2
		, ALLSTATE::COOP
		, ALLSTATE::BARN
		, ALLSTATE::MANI
		, ALLSTATE::ROBIN);
	m_MainInven->Off();

	m_MainHandItem = Parent()->MakeActor<HandItem>();
	m_MainHandItem->StateOverOn(
		ALLSTATE::FARM
		, ALLSTATE::TOWN
		, ALLSTATE::STORE
		, ALLSTATE::MINE
		, ALLSTATE::MINE1
		, ALLSTATE::MINE2
		, ALLSTATE::MINE3
		, ALLSTATE::MINE4
		, ALLSTATE::MINE5
		, ALLSTATE::TOWN2
		, ALLSTATE::COOP
		, ALLSTATE::BARN
		, ALLSTATE::MANI
		, ALLSTATE::ROBIN);
	m_MainHandItem->HandRender()->Pivot({ 3, -60 });
	m_MainHandItem->HandRender()->Off();

	MakeInven();
	MakeQuick();

	PutItem(L"Hoe");
	PutItem(L"Axe");
	PutItem(L"Pick");
	PutItem(L"Sickle");
	PutItem(L"Watercan");
	PutItem(L"Galaxysword");
	PutItem(L"Starfruit");
}

void Player::PrevUpdate()
{
}

void Player::Update()
{
	DirCheck();
	StateUpdate();
	SelectRect();
	PlayerMove();
	TimeBooster();

	if (true == m_HpBar->HpUpdate(m_Energy))
	{
		m_HpBar->Reduce(m_HpBar->PosTest());
	}
}

void Player::LaterUpdate()
{

}

void Player::DebugRender()
{
	//WCHAR OutText[100]{};
	//swprintf_s(OutText, L"Test2 %d ", WorldPlayerIndex(m_RColl->PivotPos()).X);
	//TextOutW(BHDC, 500, 25, OutText, lstrlenW(OutText));
}

void Player::OtherCollStart(ActorCollision * _This, ActorCollision * _Other)
{

}

void Player::OtherCollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (102 == _Other->CollNum())
	{
		if (m_PlayerState == PLAYERSTATE::WEAPON && true == KEYDOWN("Action"))
		{
			Monster* Test = (Monster*)_Other->Actor();
			ItemMgr::ItemInfo* Temp = nullptr;
			MonsterDamage* Damage = Parent()->MakeActor<MonsterDamage>();
			Damage->Pos({ Test->Pos().X, Test->Pos().Y - 16 });
			PlayerSp->NewSoundPlay(L"attack.wav");

			switch (m_PlayerItem)
			{
			case Player::RUSTYSWORD:
				Temp = ITEM.GetItem(L"Rustysword");
				if (true == Test->MonsterHp(Temp->m_Att))
				{
					Damage->MonsterDamageRender()->SetSprite(L"MonsterNum.bmp", 0);
				}
				else
				{
					Damage->Off();
				}
				break;
			case Player::RAPIER:
				Temp = ITEM.GetItem(L"Rapier");
				if (true == Test->MonsterHp(Temp->m_Att))
				{
					Damage->MonsterDamageRender()->SetSprite(L"MonsterNum.bmp", 1);
				}
				else
				{
					Damage->Off();
				}
				break;
			case Player::PIRATESWORD:
				Temp = ITEM.GetItem(L"Piratesword");
				if (true == Test->MonsterHp(Temp->m_Att))
				{
					Damage->MonsterDamageRender()->SetSprite(L"MonsterNum.bmp", 2);
				}
				else
				{
					Damage->Off();
				}
				break;
			case Player::GALAXYSWORD:
				Temp = ITEM.GetItem(L"Galaxysword");
				if (true == Test->MonsterHp(Temp->m_Att))
				{
					Damage->MonsterDamageRender()->SetSprite(L"MonsterNum.bmp", 3);
				}
				else
				{
					Damage->Off();
				}
				break;
			case Player::CLAYMORE:
				Temp = ITEM.GetItem(L"Claymore");
				if (true == Test->MonsterHp(Temp->m_Att))
				{
					Damage->MonsterDamageRender()->SetSprite(L"MonsterNum.bmp", 4);
				}
				else
				{
					Damage->Off();
				}
				break;
			default:
				break;
			}
		}
	}
}

void Player::OtherCollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

void Player::TimeBooster()
{
	if (true == KEYDOWNSTAY("Booster"))
	{
		ClockNumber::TimeBoost = 24.0f * 6.0f;
	}
	if (true == KEYDOWNSTAY("Reset"))
	{
		ClockNumber::TimeBoost = 1.0f;
	}
}

void Player::MakeInven()
{
	for (size_t i = 0; i < 36; ++i)
	{
		m_MainInButtonVec.push_back(Parent()->MakeActor<MainInButton>());
		m_MainInButtonVec[i]->MainInvenRender()->Size({ 54, 54 });
		m_MainInButtonVec[i]->m_MainInButton = Parent()->MakeActor<ButtonMgr>();

		m_MainInButtonVec[i]->m_MainInButton->SetBaseImage(L"Select.bmp", 1);
		m_MainInButtonVec[i]->m_MainInButton->SetEnterImage(L"Select.bmp", 0);
		m_MainInButtonVec[i]->m_MainInButton->SetClickImage(L"Select.bmp", 0);
		if (12 > i)
		{
			m_MainInButtonVec[i]->Pos({ (float)160 + (i * 64), (float)575 - TILESIZEH });
			m_MainInButtonVec[i]->m_MainInButton->ButtonInit(L"Inventory", L"MouseLeft", { (float)160 + (i * 64), (float)575 - TILESIZEH }, { 56, 56 });
		}
		else if (23 < i)
		{
			m_MainInButtonVec[i]->Pos({ (float)160 + ((i - 24) * 64), (float)697 - TILESIZEH });
			m_MainInButtonVec[i]->m_MainInButton->ButtonInit(L"Inventory", L"MouseLeft", { (float)160 + ((i - 24) * 64), (float)697 - TILESIZEH }, { 56, 56 });
		}
		else
		{
			m_MainInButtonVec[i]->Pos({ (float)160 + ((i - 12) * 64), (float)636 - TILESIZEH });
			m_MainInButtonVec[i]->m_MainInButton->ButtonInit(L"Inventory", L"MouseLeft", { (float)160 + ((i - 12) * 64), (float)636 - TILESIZEH }, { 56, 56 });
		}
		m_MainInButtonVec[i]->ButtonInit();
		m_MainInButtonVec[i]->Off();
		m_MainInButtonVec[i]->m_MainInButton->Off();

		m_MainInButtonVec[i]->m_MainInButton->StateOverOn(
			ALLSTATE::FARM
			, ALLSTATE::TOWN
			, ALLSTATE::STORE
			, ALLSTATE::MINE
			, ALLSTATE::MINE1
			, ALLSTATE::MINE2
			, ALLSTATE::MINE3
			, ALLSTATE::MINE4
			, ALLSTATE::MINE5
			, ALLSTATE::TOWN2
			, ALLSTATE::COOP
			, ALLSTATE::BARN
			, ALLSTATE::MANI
			, ALLSTATE::ROBIN);

		m_MainInButtonVec[i]->StateOverOn(
			ALLSTATE::FARM
			, ALLSTATE::TOWN
			, ALLSTATE::STORE
			, ALLSTATE::MINE
			, ALLSTATE::MINE1
			, ALLSTATE::MINE2
			, ALLSTATE::MINE3
			, ALLSTATE::MINE4
			, ALLSTATE::MINE5
			, ALLSTATE::TOWN2
			, ALLSTATE::COOP
			, ALLSTATE::BARN
			, ALLSTATE::MANI
			, ALLSTATE::ROBIN);

		m_MainInButtonVec[i]->m_InfoRender = Parent()->MakeActor<InfoRender>();
		m_MainInButtonVec[i]->m_InfoRender->StateOverOn(
			ALLSTATE::FARM
			, ALLSTATE::TOWN
			, ALLSTATE::STORE
			, ALLSTATE::MINE
			, ALLSTATE::MINE1
			, ALLSTATE::MINE2
			, ALLSTATE::MINE3
			, ALLSTATE::MINE4
			, ALLSTATE::MINE5
			, ALLSTATE::TOWN2
			, ALLSTATE::COOP
			, ALLSTATE::BARN
			, ALLSTATE::MANI
			, ALLSTATE::ROBIN);
		m_MainInButtonVec[i]->m_InfoRender->Off();
	}
}

void Player::MakeQuick()
{
	for (size_t i = 0; i < 12; ++i)
	{
		m_QuickInButtonVec.push_back(Parent()->MakeActor<QuickInButton>());
		m_QuickInButtonVec[i]->QuickInRender()->Size({ 54, 54 });

		m_QuickInButtonVec[i]->m_QuickInButton->SetBaseImage(L"Select.bmp", 1);
		m_QuickInButtonVec[i]->m_QuickInButton->SetEnterImage(L"Select.bmp", 0);
		m_QuickInButtonVec[i]->m_QuickInButton->SetClickImage(L"Select.bmp", 0);

		m_QuickInButtonVec[i]->Pos({ (float)160 + (i * 64), (float)715 });
		m_QuickInButtonVec[i]->m_QuickInButton->ButtonInit(L"Inventory", L"MouseLeft", { (float)160 + (i * 64), (float)715 }, { 60, 60 });
		m_QuickInButtonVec[i]->ButtonInit();

		m_QuickInButtonVec[i]->StateOverOn(
			ALLSTATE::FARM
			, ALLSTATE::TOWN
			, ALLSTATE::STORE
			, ALLSTATE::MINE
			, ALLSTATE::MINE1
			, ALLSTATE::MINE2
			, ALLSTATE::MINE3
			, ALLSTATE::MINE4
			, ALLSTATE::MINE5
			, ALLSTATE::TOWN2
			, ALLSTATE::COOP
			, ALLSTATE::BARN
			, ALLSTATE::MANI
			, ALLSTATE::ROBIN);

		m_QuickInButtonVec[i]->m_QuickInButton->StateOverOn(
			ALLSTATE::FARM
			, ALLSTATE::TOWN
			, ALLSTATE::STORE
			, ALLSTATE::MINE
			, ALLSTATE::MINE1
			, ALLSTATE::MINE2
			, ALLSTATE::MINE3
			, ALLSTATE::MINE4
			, ALLSTATE::MINE5
			, ALLSTATE::TOWN2
			, ALLSTATE::COOP
			, ALLSTATE::BARN
			, ALLSTATE::MANI
			, ALLSTATE::ROBIN);
	}
}

//2 - 13 , 8
//2 - 13 , 9
//2 - 13 , 10

//2 - 13 , 11

bool Player::PutItem(const WCHAR* _ItemName, int _Num)
{
	ItemMgr::ItemInfo* TestItem = ITEM.FindItem(_ItemName);
	if (nullptr == TestItem)
	{
		Tassert(true);
		return false;
	}
	for (size_t i = 0; i < m_MainInButtonVec.size(); i++)
	{
		PlayerSp->NewSoundPlay(L"take_crop.wav");

		m_MainInButtonVec[_Num]->SetItemInfo(TestItem);
		//인벤토리 안에 넣어줄때 퀵슬롯에도 같이 넣어준다.
		SetItemClickFunc(TestItem, _Num);
		return true;
	}
	return false;
}

bool Player::PutItem(ItemMgr::ItemInfo* _ItemInfo)
{
	return PutItem(_ItemInfo->m_ItemName.c_str());
}

bool Player::PutItem(const WCHAR* _ItemName)
{
	//아이템 찾아서 없으면 터트리기
	ItemMgr::ItemInfo* TestItem = ITEM.FindItem(_ItemName);
	if (nullptr == TestItem)
	{
		Tassert(true);
		return false;
	}
	for (size_t i = 0; i < m_MainInButtonVec.size(); ++i)
	{	
		if (nullptr == m_MainInButtonVec[i]->MainItemInfo())
		{
			PutItem(_ItemName, i);
			return true;
		}
	}
	//가득찼을때 경고
	if (36 == m_MainInButtonVec.size())
	{
		FullAlarm* m_Alarm = Parent()->MakeActor<FullAlarm>();
		m_Alarm->StateOverOn(
			ALLSTATE::FARM
			, ALLSTATE::TOWN
			, ALLSTATE::STORE
			, ALLSTATE::MINE
			, ALLSTATE::MINE1
			, ALLSTATE::MINE2
			, ALLSTATE::MINE3
			, ALLSTATE::MINE4
			, ALLSTATE::MINE5
			, ALLSTATE::TOWN2
			, ALLSTATE::COOP
			, ALLSTATE::BARN
			, ALLSTATE::MANI
			, ALLSTATE::ROBIN);
		return false;
	}
	return false;
}

//퀵인벤 자리에 null채워주고 메인 인벤 벡터에서 빼주고 다시 랜드해준다
bool Player::RemoveItem(size_t _Num)
{
	if (m_QuickInButtonVec.size() > _Num)
	{
		m_QuickInButtonVec[_Num]->QuickInRender()->SetSprite(L"Select.bmp", 1);
	}
	SetItemClickFunc(nullptr, _Num);
	m_MainInButtonVec[_Num]->SetItemInfo(nullptr);
	m_MainInButtonVec[_Num]->MainItemInfo(nullptr);
	return true;
}

ItemMgr::ItemInfo* Player::ReturnItemInfo(size_t _InvenCount)
{
	return m_MainInButtonVec[_InvenCount]->MainItemInfo();
}

void Player::InvenSwapCheck()
{
	Player::CurPlayer->InvenSwap(MainInButton::m_InvenCount, MainInButton::m_ChangeInvenCount);
}

bool Player::InvenSwap(int _Start, int _Next)
{
	MainInButton* Button = m_MainInButtonVec[_Next];
	m_MainInButtonVec[_Next] = m_MainInButtonVec[_Start];
	m_MainInButtonVec[_Start] = Button;

	for (int i = 0; i < 12; i++)
	{
		SetItemClickFunc(m_MainInButtonVec[i]->MainItemInfo(), i);
	}
	return true;
}

void Player::EatWork(int _InvenNum)
{
	if (nullptr != OVERPLAYER->MainHandItem()->PlayerHandItem())
	{
		if (true == OVERPLAYER->MainHandItem()->PlayerHandItem()->m_Eat)
		{
			if (true == OVERPLAYER->IncreasePlayerEnergy(OVERPLAYER->MainHandItem()->PlayerHandItem()->m_EatCount))
			{
				PlayerSp->NewSoundPlay(L"eat.wav");

				OVERPLAYER->MainHandItem()->HandRender()->Off();
				OVERPLAYER->MainHandItem()->PlayerHandItem(nullptr);
				OVERPLAYER->RemoveItem(_InvenNum);
			}
		}
	}
}

void Player::SelectRect()
{
	m_RectPos = WorldPlayerIndex({m_Pos.X + PLAYERSIZEX, m_Pos.Y + PLAYERSIZEYH});

	IPOS TempMouse = IPOS();
	TempMouse.X = MOUSEI.X + (int)Parent()->MainCamera()->CameraPos().X;
	TempMouse.Y = MOUSEI.Y + (int)Parent()->MainCamera()->CameraPos().Y;

	if (m_Pos.X - TILESIZEH > TempMouse.X)
	{
		m_RectPos.X += -1;
	}
	else if (m_Pos.X + TILESIZEH < TempMouse.X)
	{
		m_RectPos.X += 1;
	}
	else
	{
		m_RectPos.X += 0;
	}

	if (m_Pos.Y - TILESIZEH > TempMouse.Y)
	{
		m_RectPos.Y += -1;
	}
	else if (m_Pos.Y + TILESIZEH < TempMouse.Y)
	{
		m_RectPos.Y += 1;
	}
	else
	{
		m_RectPos.Y += 0;
	}

	m_RectPos.X -= 1;
	m_RectPos.Y -= 1;

	FPOS TempPos = IndexWorldPos(m_RectPos);
	m_SelectRenderer->Pos(TempPos);
}

void Player::PlayerMove()
{
	if (nullptr != m_MainHandItem)
	{
		//손 아이템 플레이어 따라다니게 하기
		m_MainHandItem->Pos(m_Pos);
	}

	//배경 못가게하기
	m_BackStartPos - m_BackGround.Pos;
	m_BackEndPos = m_BackStartPos + m_BackGround.Size;

	//rectpos + 1 타일이 0이면 못가면 댐?
	IPOS CheckPos;
	CheckPos = WorldPlayerIndex({ m_Pos.X + PLAYERSIZEX, m_Pos.Y + PLAYERSIZEYH });
	CheckPos.X -= 1;
	CheckPos.Y -= 1;

	if (true == KEYDOWNSTAY("DOWN"))
	{
		if (false == KEYDOWNSTAY("RIGHT") || 
			false == KEYDOWNSTAY("LEFT") || 
			false == KEYDOWN("RIGHT") || 
			false == KEYDOWN("LEFT"))
		{
			if (m_BackEndPos.Y - PLAYERSIZEYH >= m_Pos.Y)
			{
				if (0 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_DColl->PivotPos()))
					&& 0 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_DSColl->PivotPos()))
					&& 1 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_DColl->PivotPos()))
					&& 1 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_DSColl->PivotPos()))
					&& 3 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_DColl->PivotPos()))
					&& 3 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_DSColl->PivotPos())))
				{
					m_Pos.Y += (m_Speed * DELTATIME * DDOWN.Y);
				}
			}
		}
	}
	else if (true == KEYDOWNSTAY("UP"))
	{
		if (false == KEYDOWNSTAY("RIGHT") ||
			false == KEYDOWNSTAY("LEFT") ||
			false == KEYDOWN("RIGHT") ||
			false == KEYDOWN("LEFT"))
		{
			if (m_BackStartPos.Y + PLAYERSIZEYH <= m_Pos.Y)
			{
				if (0 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_UColl->PivotPos()))
					&& 0 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_USColl->PivotPos()))
					&& 1 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_UColl->PivotPos()))
					&& 1 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_USColl->PivotPos()))
					&& 3 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_UColl->PivotPos()))
					&& 3 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_USColl->PivotPos())))
				{
					m_Pos.Y += (m_Speed * DELTATIME * DUP.Y);
				}
			}
		}
	}
	else if (true == KEYDOWNSTAY("RIGHT"))
	{
		if (false == KEYDOWNSTAY("UP") ||
			false == KEYDOWNSTAY("DOWN") ||
			false == KEYDOWN("UP") ||
			false == KEYDOWN("DOWN"))
		{
			if (m_BackEndPos.X - PLAYERSIZEXH >= m_Pos.X)
			{
				if ( 0 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_RColl->PivotPos())) 
					&& 0 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_RSColl->PivotPos()))
					&& 1 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_RColl->PivotPos()))
					&& 1 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_RSColl->PivotPos()))
					&& 3 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_RColl->PivotPos()))
					&& 3 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_RSColl->PivotPos())))
				{
					m_Pos.X += (m_Speed * DELTATIME * DRIGHT.X);
				}
			}
		}
	}
	else if (true == KEYDOWNSTAY("LEFT"))
	{
		if (false == KEYDOWNSTAY("UP") ||
			false == KEYDOWNSTAY("DOWN") ||
			false == KEYDOWN("UP") ||
			false == KEYDOWN("DOWN"))
		{
			if (m_BackStartPos.X + PLAYERSIZEXH <= m_Pos.X)
			{
				if (0 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_LColl->PivotPos()))
					&& 0 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_LSColl->PivotPos()))
					&& 1 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_LColl->PivotPos()))
					&& 1 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_LSColl->PivotPos()))
					&& 3 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_LColl->PivotPos()))
					&& 3 != m_PlayerTile->FindSpriteIndex(WorldPlayerIndex(m_LSColl->PivotPos())))
				{
					m_Pos.X += (m_Speed * DELTATIME * DLEFT.X);
				}
			}
		}
	}

	if (true == KEYDOWN("Inven"))
	{
		OpenMainInven();
		//메인인벤 켜져있다면
		if (true == m_InvenCheck)
		{
			CloseMainInven();
			m_InvenCheck = false;
			return;
		}
		m_InvenCheck = true;
	}
}

void Player::OpenMainInven()
{
	//메인인벤 켜기(렌더러 + 버튼)
	m_MainInven->On();
	for (size_t i = 0; i < m_MainInButtonVec.size(); ++i)
	{
		m_MainInButtonVec[i]->On();
		m_MainInButtonVec[i]->m_MainInButton->On();
	}
	//퀵슬롯 끄기(렌더러 + 버튼)
	m_QuickInven->Off();
	for (size_t i = 0; i < m_QuickInButtonVec.size(); ++i)
	{
		m_QuickInButtonVec[i]->QuickInRender()->Off();
		m_QuickInButtonVec[i]->QuickInvenButton()->Off();
	}
}

void Player::CloseMainInven()
{
	//메인인벤 끄기(렌더러 + 버튼)
	m_MainInven->Off();
	for (size_t i = 0; i < m_MainInButtonVec.size(); ++i)
	{
		m_MainInButtonVec[i]->Off();
		m_MainInButtonVec[i]->m_MainInButton->Off();
	}
	//퀵인벤 켜기(렌더러 + 버튼)
	m_QuickInven->On();
	for (size_t i = 0; i < m_QuickInButtonVec.size(); ++i)
	{
		m_QuickInButtonVec[i]->QuickInRender()->On();
		m_QuickInButtonVec[i]->QuickInvenButton()->On();
	}
	MainInButton::m_InfoRender->Off();
}
//아이템 클릭하면 해야할 행동
//Seed Crop tree rock - 아이템 들어야 함
//손아이템 랜더러 켜고
//아이템 랜드하고
//플레이어 스테이트 pick로 바꿔주고

//Tool weapon - 스테이트 바뀌어야함

void Player::SetItemClickFunc(ItemMgr::ItemInfo* _Item, size_t _Num)
{
	//인벤토리 안에 넣어줄때 퀵슬롯에도 같이 넣어준다. 12개만
	if (m_QuickInButtonVec.size() > _Num)
	{
		if (nullptr == _Item)
		{
			m_QuickInButtonVec[_Num]->QuickInRender()->SetSprite(L"Select.bmp", 1);
			m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(nullptr);
		}
		else
		{
			m_QuickInButtonVec[_Num]->QuickInRender()->SetSprite(_Item->m_SpriteName.c_str(), _Item->m_SpriteNum);

			switch (_Item->m_ItemType)
			{
			case ItemMgr::Seed:
				switch (_Item->m_ItemCount)
				{
				case ItemMgr::ParsnipSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(ParsnipSeed);
					break;
				case ItemMgr::GreenbeanSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(GreenbeanSeed);
					break;
				case ItemMgr::CauliflowerSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(CauliflowerSeed);
					break;
				case ItemMgr::PotatoSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(PotatoSeed);
					break;
				case ItemMgr::GarlicSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(GarlicSeed);
					break;
				case ItemMgr::KaleSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(KaleSeed);
					break;
				case ItemMgr::RhubarbSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(RhubarbSeed);
					break;
				case ItemMgr::MelonSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(MelonSeed);
					break;
				case ItemMgr::TomatoSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(TomatoSeed);
					break;
				case ItemMgr::BlueberrySeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(BlueberrySeed);
					break;
				case ItemMgr::HotpepperSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(HotpepperSeed);
					break;
				case ItemMgr::WheatSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(WheatSeed);
					break;
				case ItemMgr::RadishSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(RadishSeed);
					break;
				case ItemMgr::RedcabbageSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(RedcabbageSeed);
					break;
				case ItemMgr::StarfruitSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(StarfruitSeed);
					break;
				case ItemMgr::CornSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(CornSeed);
					break;
				case ItemMgr::EggplantSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(EggplantSeed);
					break;
				case ItemMgr::ArtichokeSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(ArtichokeSeed);
					break;
				case ItemMgr::PumpkinSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(PumpkinSeed);
					break;
				case ItemMgr::BokchoySeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(BokchoySeed);
					break;
				case ItemMgr::YamSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(YamSeed);
					break;
				case ItemMgr::CoffeebeanSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(CoffeebeanSeed);
					break;
				case ItemMgr::BeetSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(BeetSeed);
					break;
				case ItemMgr::AncientfruitSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(AncientfruitSeed);
					break;
				case ItemMgr::StrawberrySeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(StrawberrySeed);
					break;
				case ItemMgr::GrapeSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(GrapeSeed);
					break;
				case ItemMgr::HopsSeed:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(HopsSeed);
					break;
				default:
					break;
				}
				break;
			case ItemMgr::Crop:
				switch (_Item->m_ItemCount)
				{
				case ItemMgr::Parsnip:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Parsnip);
					break;
				case ItemMgr::Greenbean:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Greenbean);
					break;
				case ItemMgr::Cauliflower:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Cauliflower);
					break;
				case ItemMgr::Potato:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Potato);
					break;
				case ItemMgr::Garlic:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Garlic);
					break;
				case ItemMgr::Kale:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Kale);
					break;
				case ItemMgr::Rhubarb:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Rhubarb);
					break;
				case ItemMgr::Melon:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Melon);
					break;
				case ItemMgr::Tomato:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Tomato);
					break;
				case ItemMgr::Blueberry:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Blueberry);
					break;
				case ItemMgr::Hotpepper:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Hotpepper);
					break;
				case ItemMgr::Wheat:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Wheat);
					break;
				case ItemMgr::Radish:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Radish);
					break;
				case ItemMgr::Redcabbage:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Redcabbage);
					break;
				case ItemMgr::Starfruit:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Starfruit);
					break;
				case ItemMgr::Corn:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Corn);
					break;
				case ItemMgr::Eggplant:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Eggplant);
					break;
				case ItemMgr::Artichoke:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Artichoke);
					break;
				case ItemMgr::Pumpkin:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Pumpkin);
					break;
				case ItemMgr::Bokchoy:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Bokchoy);
					break;
				case ItemMgr::Yam:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Yam);
					break;
				case ItemMgr::Coffeebean:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Coffeebean);
					break;
				case ItemMgr::Beet:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Beet);
					break;
				case ItemMgr::Ancientfruit:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Ancientfruit);
					break;
				case ItemMgr::Strawberry:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Strawberry);
					break;
				case ItemMgr::Grape:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Grape);
					break;
				case ItemMgr::Hops:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Hops);
					break;
				default:
					break;
				}
				break;
			case ItemMgr::Tool:
				switch (_Item->m_ItemCount)
				{
				case ItemMgr::Axe:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Axe);
					break;
				case ItemMgr::Hoe:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Hoe);
					break;
				case ItemMgr::Pick:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Pick);
					break;
				case ItemMgr::Watercan:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Watercan);
					break;
				default:
					break;
				}
				break;
			case ItemMgr::Weapon:
				switch (_Item->m_ItemCount)
				{
				case ItemMgr::Sickle:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Sickle);
					break;
				case ItemMgr::Rustysword:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Rustysword);
					break;
				case ItemMgr::Rapier:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Rapier);
					break;
				case ItemMgr::Piratesword:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Piratesword);
					break;
				case ItemMgr::Galaxysword:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Galaxysword);
					break;
				case ItemMgr::Claymore:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Claymore);
					break;
				default:
					break;
				}
				break;
			case ItemMgr::Rock:
				switch (_Item->m_ItemCount)
				{
				case ItemMgr::Rockone:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Rockone);
					break;
				case ItemMgr::Rocktwo:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Rocktwo);
					break;
				case ItemMgr::Emerald:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Emerald);
					break;
				case ItemMgr::Aquamarine:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Aquamarine);
					break;
				case ItemMgr::Ruby:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Ruby);
					break;
				case ItemMgr::Topaz:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Topaz);
					break;
				case ItemMgr::Diamond:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Diamond);
					break;
				default:
					break;
				}
				break;
			case ItemMgr::Woods:
				m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Wood);
				break;
			case ItemMgr::Product:
				switch (_Item->m_ItemCount)
				{
				case ItemMgr::Milk:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Milk);
					break;
				case ItemMgr::GoetMilk:
					m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(GoetMilk);
					break;				
				case ItemMgr::Wool:
						m_QuickInButtonVec[_Num]->QuickInvenButton()->SetClickFunc(Wool);
						break;
				}
				break;
			default:
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////Wood////////////////////////////////////////////////////////////////////
void Player::Milk(void *)
{
	Player::CurPlayer->SetMainHandItem(nullptr);
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Milk"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}

void Player::GoetMilk(void *)
{
	Player::CurPlayer->SetMainHandItem(nullptr);
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"GoetMilk"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}

void Player::Wool(void *)
{
	Player::CurPlayer->SetMainHandItem(nullptr);
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Wool"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}

////////////////////////////////////////////////////////////////////Wood////////////////////////////////////////////////////////////////////
void Player::Wood(void *)
{
	Player::CurPlayer->SetMainHandItem(nullptr);
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Wood"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}

////////////////////////////////////////////////////////////////////Rocks////////////////////////////////////////////////////////////////////
void Player::Rockone(void *)
{
	Player::CurPlayer->SetMainHandItem(nullptr);
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"RockOne"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}

void Player::Rocktwo(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"RockTwo"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}

void Player::Emerald(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Emerald"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}

void Player::Aquamarine(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Aquamarine"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}

void Player::Ruby(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Ruby"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}

void Player::Topaz(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Topaz"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}

void Player::Diamond(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Diamond"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
}


////////////////////////////////////////////////////////////////////Weapons////////////////////////////////////////////////////////////////////
void Player::Sickle(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->Off();
	Player::CurPlayer->ChangeState(Player::PLAYERSTATE::WEAPON, Player::PLAYERTOOL::SICKLE);
	Player::CurPlayer->SetMainHandItem(nullptr);
}

void Player::Rustysword(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->Off();
	Player::CurPlayer->ChangeState(Player::PLAYERSTATE::WEAPON, Player::PLAYERTOOL::RUSTYSWORD);
	Player::CurPlayer->SetMainHandItem(nullptr);
}

void Player::Rapier(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->Off();
	Player::CurPlayer->ChangeState(Player::PLAYERSTATE::WEAPON, Player::PLAYERTOOL::RAPIER);
	Player::CurPlayer->SetMainHandItem(nullptr);
}

void Player::Piratesword(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->Off();
	Player::CurPlayer->ChangeState(Player::PLAYERSTATE::WEAPON, Player::PLAYERTOOL::PIRATESWORD);
	Player::CurPlayer->SetMainHandItem(nullptr);
}

void Player::Galaxysword(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->Off();
	Player::CurPlayer->ChangeState(Player::PLAYERSTATE::WEAPON, Player::PLAYERTOOL::GALAXYSWORD);
	Player::CurPlayer->SetMainHandItem(nullptr);
}

void Player::Claymore(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->Off();
	Player::CurPlayer->ChangeState(Player::PLAYERSTATE::WEAPON, Player::PLAYERTOOL::CLAYMORE);
	Player::CurPlayer->SetMainHandItem(nullptr);
}

////////////////////////////////////////////////////////////////////Tools////////////////////////////////////////////////////////////////////
void Player::Axe(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->Off();
	Player::CurPlayer->ChangeState(Player::PLAYERSTATE::TOOL, Player::PLAYERTOOL::AXE);
	Player::CurPlayer->SetMainHandItem(nullptr);
}

void Player::Hoe(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->Off();
	Player::CurPlayer->ChangeState(Player::PLAYERSTATE::TOOL, Player::PLAYERTOOL::HOE);
	Player::CurPlayer->SetMainHandItem(nullptr);
}

void Player::Pick(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->Off();
	Player::CurPlayer->ChangeState(Player::PLAYERSTATE::TOOL, Player::PLAYERTOOL::PICKAXE);
	Player::CurPlayer->SetMainHandItem(nullptr);
}

void Player::Watercan(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->Off();
	Player::CurPlayer->ChangeState(Player::PLAYERSTATE::TOOL, Player::PLAYERTOOL::WATERCAN);
	Player::CurPlayer->SetMainHandItem(nullptr);
}

////////////////////////////////////////////////////////////////////Crops////////////////////////////////////////////////////////////////////

void Player::Parsnip(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Parsnip"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Greenbean(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Greenbean"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Cauliflower(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Cauliflower"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Potato(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Potato"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
} 

void Player::Garlic(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Garlic"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Kale(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Kale"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Rhubarb(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Rhubarb"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Melon(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Melon"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Tomato(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Tomato"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Blueberry(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Blueberry"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Hotpepper(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Hotpepper"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Wheat(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Wheat"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Radish(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Radish"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Redcabbage(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Redcabbage"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Starfruit(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Starfruit"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Corn(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Corn"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Eggplant(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Eggplant"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Artichoke(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Artichoke"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Pumpkin(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Pumpkin"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Bokchoy(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Bokchoy"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Yam(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Yam"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Coffeebean(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Coffeebean"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Beet(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Beet"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Ancientfruit(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Ancientfruit"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Strawberry(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Strawberry"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Grape(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Grape"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::Hops(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"Hops"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

////////////////////////////////////////////////////////////////////Seed////////////////////////////////////////////////////////////////////

void Player::ParsnipSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"ParsnipSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);	
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::GreenbeanSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"GreenbeanSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::CauliflowerSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"CauliflowerSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::PotatoSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"PotatoSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::GarlicSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"GarlicSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::KaleSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"KaleSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::RhubarbSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"RhubarbSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::MelonSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"MelonSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::TomatoSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"TomatoSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::BlueberrySeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"BlueberrySeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::HotpepperSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"HotpepperSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::WheatSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"WheatSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::RadishSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"RadishSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::RedcabbageSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"RedcabbageSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::StarfruitSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"StarfruitSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::CornSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"CornSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::EggplantSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"EggplantSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::ArtichokeSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"ArtichokeSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::PumpkinSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"PumpkinSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::BokchoySeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"BokchoySeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::YamSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"YamSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::CoffeebeanSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"CoffeebeanSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::BeetSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"BeetSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::AncientfruitSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"AncientfruitSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::StrawberrySeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"StrawberrySeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::GrapeSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"GrapeSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::HopsSeed(void *)
{
	Player::CurPlayer->MainHandItem()->HandRender()->On();
	Player::CurPlayer->SetMainHandItem(ITEM.GetItem(L"HopsSeed"));
	Player::CurPlayer->MainHandItem()->HandRender()->SetSprite(Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteName.c_str(), Player::CurPlayer->MainHandItem()->PlayerHandItem()->m_SpriteNum);
	Player::CurPlayer->ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
	Player::CurPlayer->PlayerItem(PLAYERTOOL::NONE);
}

void Player::MakePlayerAni()
{
	m_MainPlayerRender->MakeAni(L"Walk.bmp", L"DownWalkBody", 1, 4, 0.15f);
	m_MainPlayerRender->MakeAni(L"Walk.bmp", L"UpWalkBody", 16, 19, 0.15f);
	m_MainPlayerRender->MakeAni(L"Walk.bmp", L"LeftWalkBody", 10, 13, 0.15f);
	m_MainPlayerRender->MakeAni(L"Walk.bmp", L"RightWalkBody", 6, 9, 0.15f);
		
	m_MainPlayerRender->MakeAni(L"Walk.bmp", L"DownStayBody", 0, 0, 0.15f);
	m_MainPlayerRender->MakeAni(L"Walk.bmp", L"UpStayBody", 15, 15, 0.15f);
	m_MainPlayerRender->MakeAni(L"Walk.bmp", L"LeftStayBody", 14, 14, 0.15f);
	m_MainPlayerRender->MakeAni(L"Walk.bmp", L"RightStayBody", 5, 5, 0.15f);

	//--------------------------------------------------------------------------------------------------------------

	m_MainPlayerRender->MakeAni(L"2farmer_girl_base.bmp", L"DownPickWalkBody", 0, 2, 0.15f);
	m_MainPlayerRender->MakeAni(L"2farmer_girl_base.bmp", L"UpPickWalkBody", 12, 14, 0.15f);
	m_MainPlayerRender->MakeAni(L"2farmer_girl_base_Reverse.bmp", L"LeftPickWalkBody", 9, 11, 0.15f);
	m_MainPlayerRender->MakeAni(L"2farmer_girl_base.bmp", L"RightPickWalkBody", 6, 8, 0.15f);
		
	m_MainPlayerRender->MakeAni(L"2farmer_girl_base.bmp", L"DownPickBody", 0, 0, 0.15f);
	m_MainPlayerRender->MakeAni(L"2farmer_girl_base.bmp", L"UpPickBody", 12, 12, 0.15f);
	m_MainPlayerRender->MakeAni(L"2farmer_girl_base_Reverse.bmp", L"LeftPickBody", 11, 11, 0.15f);
	m_MainPlayerRender->MakeAni(L"2farmer_girl_base.bmp", L"RightPickBody", 6, 6, 0.15f);

	//--------------------------------------------------------------------------------------------------------------

	m_MainPlayerRender->MakeAni(L"2farmer_girl_base.bmp", L"DownWeaponBody", 24, 28, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"2farmer_girl_base.bmp", L"UpWeaponBody", 36, 40, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"LeftWeaponBody.bmp", L"LeftWeaponBody", 0, 4, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"2farmer_girl_base.bmp", L"RightWeaponBody", 30, 34, 0.15f, false);

	//--------------------------------------------------------------------------------------------------------------

	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"DownToolBody", 66, 70, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"UpToolBody.bmp", L"UpToolBody", 0, 4, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"LeftToolBody.bmp", L"LeftToolBody", 0, 4, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"RightToolBody", 48, 52, 0.15f, false);

	//--------------------------------------------------------------------------------------------------------------

	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"DownEatBody", 84, 88, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"UpEatBody", 84, 88, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"LeftEatBody", 84, 88, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"RightEatBody", 84, 88, 0.15f, false);

	m_MainPlayerRender->MakeAni(L"DownWaterBody.bmp", L"DownWaterBody", 0, 4, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"UpWaterBody.bmp", L"UpWaterBody", 0, 4, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"LeftWaterBody.bmp", L"LeftWaterBody", 0, 4, 0.15f, false);
	m_MainPlayerRender->MakeAni(L"RightWaterBody.bmp", L"RightWaterBody", 0, 4, 0.15f, false);

	//--------------------------------------------------------------------------------------------------------------

	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"DownRideBody", 107, 107, 0.15f);
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"UpRideBody", 113, 113, 0.15f);
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base_Reverse.bmp", L"LeftRideBody", 103, 103, 0.15f);
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"RightRideBody", 106, 106, 0.15f);
			
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"DownRideStayBody", 107, 107, 0.15f);
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"UpRideStayBody", 113, 113, 0.15f);
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base_Reverse.bmp", L"LeftRideStayBody", 103, 103, 0.15f);
	m_MainPlayerRender->MakeAni(L"1farmer_girl_base.bmp", L"RightRideStayBody", 106, 106, 0.15f);

	//--------------------------------------------------------------------------------------------------------------

	m_MainItemRender->MakeAni(L"1axe_action.bmp", L"DownAxe", 10, 14, 0.15f, false);
	m_MainItemRender->MakeAni(L"1axe_action.bmp", L"UpAxe", 0, 4, 0.15f, false);
	m_MainItemRender->MakeAni(L"1axe_action.bmp", L"LeftAxe", 15, 19, 0.15f, false);
	m_MainItemRender->MakeAni(L"1axe_action.bmp", L"RightAxe", 5, 9, 0.15f, false);
		
	m_MainItemRender->MakeAni(L"2hoe_action.bmp", L"DownHoe", 10, 14, 0.15f, false);
	m_MainItemRender->MakeAni(L"2hoe_action.bmp", L"UpHoe", 0, 4, 0.15f, false);
	m_MainItemRender->MakeAni(L"2hoe_action.bmp", L"LeftHoe", 15, 19, 0.15f, false);
	m_MainItemRender->MakeAni(L"2hoe_action.bmp", L"RightHoe", 5, 9, 0.15f, false);
		
	m_MainItemRender->MakeAni(L"3pickaxe_action.bmp", L"DownPick", 10, 14, 0.15f, false);
	m_MainItemRender->MakeAni(L"3pickaxe_action.bmp", L"UpPick", 0, 4, 0.15f, false);
	m_MainItemRender->MakeAni(L"3pickaxe_action.bmp", L"LeftPick", 15, 19, 0.15f, false);
	m_MainItemRender->MakeAni(L"3pickaxe_action.bmp", L"RightPick", 5, 9, 0.15f, false);
		
	m_MainItemRender->MakeAni(L"4sickle_action.bmp", L"DownSickle", 10, 14, 0.15f, false);
	m_MainItemRender->MakeAni(L"4sickle_action.bmp", L"UpSickle", 0, 4, 0.15f, false);
	m_MainItemRender->MakeAni(L"4sickle_action.bmp", L"LeftSickle", 15, 19, 0.15f, false);
	m_MainItemRender->MakeAni(L"4sickle_action.bmp", L"RightSickle", 5, 9, 0.15f, false);
			
	m_MainItemRender->MakeAni(L"5watercan_action.bmp", L"DownWatercan", 10, 14, 0.15f, false);
	m_MainItemRender->MakeAni(L"5watercan_action.bmp", L"UpWatercan", 0, 4, 0.15f, false);
	m_MainItemRender->MakeAni(L"5watercan_action.bmp", L"LeftWatercan", 15, 19, 0.15f, false);
	m_MainItemRender->MakeAni(L"5watercan_action.bmp", L"RightWatercan", 5, 9, 0.15f, false);
		
	m_MainItemRender->MakeAni(L"6rustysword_action.bmp", L"DownRustysword", 10, 14, 0.15f, false);
	m_MainItemRender->MakeAni(L"6rustysword_action.bmp", L"UpRustysword", 0, 4, 0.15f, false);
	m_MainItemRender->MakeAni(L"6rustysword_action.bmp", L"LeftRustysword", 15, 19, 0.15f, false);
	m_MainItemRender->MakeAni(L"6rustysword_action.bmp", L"RightRustysword", 5, 9, 0.15f, false);
			
	m_MainItemRender->MakeAni(L"7Rapier_action.bmp", L"DownRapier", 10, 14, 0.15f, false);
	m_MainItemRender->MakeAni(L"7Rapier_action.bmp", L"UpRapier", 0, 4, 0.15f, false);
	m_MainItemRender->MakeAni(L"7Rapier_action.bmp", L"LeftRapier", 15, 19, 0.15f, false);
	m_MainItemRender->MakeAni(L"7Rapier_action.bmp", L"RightRapier", 5, 9, 0.15f, false);
		
	m_MainItemRender->MakeAni(L"8PirateSword_action.bmp", L"DownPiratesword", 10, 14, 0.15f, false);
	m_MainItemRender->MakeAni(L"8PirateSword_action.bmp", L"UpPiratesword", 0, 4, 0.15f, false);
	m_MainItemRender->MakeAni(L"8PirateSword_action.bmp", L"LeftPiratesword", 15, 19, 0.15f, false);
	m_MainItemRender->MakeAni(L"8PirateSword_action.bmp", L"RightPiratesword", 5, 9, 0.15f, false);
		
	m_MainItemRender->MakeAni(L"9galaxysword_action.bmp", L"DownGalaxysword", 10, 14, 0.15f, false);
	m_MainItemRender->MakeAni(L"9galaxysword_action.bmp", L"UpGalaxysword", 0, 4, 0.15f, false);
	m_MainItemRender->MakeAni(L"9galaxysword_action.bmp", L"LeftGalaxysword", 15, 19, 0.15f, false);
	m_MainItemRender->MakeAni(L"9galaxysword_action.bmp", L"RightGalaxysword", 5, 9, 0.15f, false);
			
	m_MainItemRender->MakeAni(L"10claymore_action.bmp", L"DownClaymore", 10, 14, 0.15f, false);
	m_MainItemRender->MakeAni(L"10claymore_action.bmp", L"UpClaymore", 0, 4, 0.15f, false);
	m_MainItemRender->MakeAni(L"10claymore_action.bmp", L"LeftClaymore", 15, 19, 0.15f, false);
	m_MainItemRender->MakeAni(L"10claymore_action.bmp", L"RightClaymore", 5, 9, 0.15f, false);
				
	//m_MainItem->MakeAni(L"horse.bmp", L"DownHorse", 0, 6, 0.15f);
	//m_MainItem->MakeAni(L"horse.bmp", L"UpHorse", 14, 20, 0.15f);
	//m_MainItem->MakeAni(L"horse.bmp", L"LeftHorse", 35, 41, 0.15f);
	//m_MainItem->MakeAni(L"horse.bmp", L"RightHorse", 7, 13, 0.15f);
}

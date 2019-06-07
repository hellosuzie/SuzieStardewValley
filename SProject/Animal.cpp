#include "stdafx.h"
#include "Animal.h"
#include "AniActorRender.h"
#include "EnterMgr.h"
#include "MathMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "ActorCollision.h"
#include "Damage.h"
#include "Imotion.h"
#include "TileActorRender.h"
#include "ClockNumber.h"
#include "Egg.h"
#include "BoomEffect.h"
#include "RainbowEffect.h"
#include "ResourceMgr.h"
#include "SoundPlayer.h"
#include "HarvEffect.h"
#include "SingleActorRender.h"
#include "TwinkleEffect.h"

TileActorRender* Animal::TempCoopTile = nullptr;

bool Animal::ChickenEggCheck = false;
bool Animal::DuckEggCheck = false;
int Animal::ChickenCount = 0;
int Animal::DuckCount = 0;
int Animal::TempChicken = 0;
int Animal::TempDuck = 0;
int Animal::BabyChickenCount = 0;
int Animal::BabyDuckCount = 0;
int Animal::BabyEggCount = 0;
int Animal::DBabyEggCount = 0;

//알 낳고 알에서 자라기
//충돌상태에서 버튼 클릭하면 팔기 돈 오르기

Animal::Animal(int _Type) 
	: m_RSpeed(280.0f), m_DSpeed(250.0f), m_CSpeed(300.0f), m_BCSpeed(310.0f), m_BDSpeed(260.0f), m_CGSpeed(250.0f)
	, m_StayToMoveTimer(2.0f), m_MoveToSitTimer(3.0f), m_SitToStayTimer(1.0f)
	, m_Time(0.0f), m_AnimalSpeed(0.0f)
	, m_UTemp(0.0f), m_DTemp(0.0f), m_RTemp(0.0f), m_LTemp(0.0f), TempTime(0.0f)
	, m_BabyChickenCheck(0.0f), m_BabyDuckCheck(0.0f)
{
	m_AnimalType = (ANIMALTYPE)_Type;

	m_RDir = rand() % 3;
	m_DDir = rand() % 3;
	m_CDir = rand() % 3;

	if (ANIMALTYPE::Chicken == m_AnimalType)
	{
		++Animal::ChickenCount;
	}
	if (ANIMALTYPE::Duck == m_AnimalType)
	{
		++Animal::DuckCount;
	}
	if (ANIMALTYPE::BabyChicken == m_AnimalType)
	{
		++Animal::BabyChickenCount;
	}
	if (ANIMALTYPE::BabyDuck == m_AnimalType)
	{
		++Animal::BabyDuckCount;
	}
}

Animal::~Animal()
{

}

void Animal::Init()
{
	ChickenSp = GETSOUND;
	DuckSp = GETSOUND;
	GoetSp = GETSOUND;
	CowSp = GETSOUND;

	if (ANIMALTYPE::Cow == m_AnimalType || ANIMALTYPE::Goet == m_AnimalType || ANIMALTYPE::Sheep == m_AnimalType)
	{
		m_AnimalAni = MakeRender<AniActorRender>(10);
		m_AnimalAni->Size(FPOS{ 128, 128 });

		if (ANIMALTYPE::Cow == m_AnimalType)
		{
			ActorCollision* MilkColl = MakeCollision(L"Milk", { 128, 100 }, 125);
		}
		else if (ANIMALTYPE::Goet == m_AnimalType)
		{
			ActorCollision* GMilkColl = MakeCollision(L"Milk", { 128, 100 }, 126);
		}
		else if (ANIMALTYPE::Sheep == m_AnimalType)
		{
			ActorCollision* GMilkColl = MakeCollision(L"Milk", { 128, 100 }, 127);
		}

		UColl = MakeCollision(L"Animal", { 10, 10 }, 122);
		UColl->Pivot({ 0, -TILESIZE });
		DColl = MakeCollision(L"Animal", { 10, 10 }, 122);
		DColl->Pivot({ 0, TILESIZE });
		LColl = MakeCollision(L"Animal", { 10, 10 }, 122);
		LColl->Pivot({ -TILESIZE, 0 });
		RColl = MakeCollision(L"Animal", { 10, 10 }, 122);
		RColl->Pivot({ TILESIZE, 0 });
	}
	else
	{
		m_AnimalAni = MakeRender<AniActorRender>(10);
		m_AnimalAni->Size(FPOS{ 64, 64 });

		UColl = MakeCollision(L"Animal", { 10, 10 });
		UColl->Pivot({ 0, -TILESIZEH });
		DColl = MakeCollision(L"Animal", { 10, 10 });
		DColl->Pivot({ 0, TILESIZEH });
		LColl = MakeCollision(L"Animal", { 10, 10 });
		LColl->Pivot({ -TILESIZEH, 0 });
		RColl = MakeCollision(L"Animal", { 10, 10 });
		RColl->Pivot({ TILESIZEH, 0 });
	}

	switch (m_AnimalType)
	{
	case Animal::Rabbit:
		m_AnimalSpeed = m_RSpeed;
		break;
	case Animal::Duck:
		m_AnimalSpeed = m_DSpeed;
		break;
	case Animal::Chicken:
		m_AnimalSpeed = m_CSpeed;
		break;
	case Animal::BabyChicken:
		m_AnimalSpeed = m_BCSpeed;
		break;
	case Animal::BabyDuck: 
		m_AnimalSpeed = m_BDSpeed;
		break;
	case Animal::Cow:
		m_AnimalSpeed = m_CGSpeed;
		break;
	case Animal::Goet:
		m_AnimalSpeed = m_CGSpeed;
		break;
	case Animal::Sheep:
		m_AnimalSpeed = m_CGSpeed;
		break;
	default:
		break;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	//Rabbit
	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"UpMove1", 8, 11, 0.2f);
	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"DownMove1", 0, 3, 0.2f);
	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"RightMove1", 4, 7, 0.2f);
	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"LeftMove1", 12, 15, 0.2f);

	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"UpStay1", 20, 20, 0.2f);
	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"DownStay1", 16, 16, 0.2f);
	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"RightStay1", 18, 18, 0.2f);
	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"LeftStay1", 22, 22, 0.2f);

	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"UpSit1", 20, 21, 0.3f, false);
	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"DownSit1", 16, 17, 0.3f, false);
	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"RightSit1", 18, 19, 0.3f, false);
	m_AnimalAni->MakeAni(L"Rabbit.bmp", L"LeftSit1", 22, 23, 0.3f, false);

	/////////////////////////////////////////////////////////////////////////////////////
	//Duck
	m_AnimalAni->MakeAni(L"Duck.bmp", L"UpMove2", 8, 11, 0.2f);
	m_AnimalAni->MakeAni(L"Duck.bmp", L"DownMove2", 0, 3, 0.2f);
	m_AnimalAni->MakeAni(L"Duck.bmp", L"RightMove2", 4, 7, 0.2f);
	m_AnimalAni->MakeAni(L"Duck.bmp", L"LeftMove2", 12, 15, 0.2f);

	m_AnimalAni->MakeAni(L"Duck.bmp", L"UpStay2", 20, 20, 0.2f);
	m_AnimalAni->MakeAni(L"Duck.bmp", L"DownStay2", 16, 16, 0.2f);
	m_AnimalAni->MakeAni(L"Duck.bmp", L"RightStay2", 18, 18, 0.2f);
	m_AnimalAni->MakeAni(L"Duck.bmp", L"LeftStay2", 22, 22, 0.2f);

	m_AnimalAni->MakeAni(L"Duck.bmp", L"UpSit2", 20, 21, 0.3f, false);
	m_AnimalAni->MakeAni(L"Duck.bmp", L"DownSit2", 16, 17, 0.3f, false);
	m_AnimalAni->MakeAni(L"Duck.bmp", L"RightSit2", 18, 19, 0.3f, false);
	m_AnimalAni->MakeAni(L"Duck.bmp", L"LeftSit2", 22, 23, 0.3f, false);

	/////////////////////////////////////////////////////////////////////////////////////
	//Chicken
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"UpMove3", 8, 11, 0.15f);
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"DownMove3", 0, 3, 0.15f);
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"RightMove3", 4, 7, 0.15f);
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"LeftMove3", 12, 15, 0.15f);
						 
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"UpStay3", 20, 20, 0.15f);
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"DownStay3", 16, 16, 0.15f);
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"RightStay3", 18, 18, 0.15f);
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"LeftStay3", 22, 22, 0.15f);
						   
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"UpSit3", 20, 21, 0.3f, false);
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"DownSit3", 16, 17, 0.3f, false);
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"RightSit3", 18, 19, 0.3f, false);
	m_AnimalAni->MakeAni(L"Chicken.bmp", L"LeftSit3", 22, 23, 0.3f, false);

	/////////////////////////////////////////////////////////////////////////////////////
	//BabyChicken
	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"UpMove4", 8, 11, 0.15f);
	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"DownMove4", 0, 3, 0.15f);
	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"RightMove4", 4, 7, 0.15f);
	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"LeftMove4", 12, 15, 0.15f);

	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"UpStay4", 20, 20, 0.15f);
	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"DownStay4", 16, 16, 0.15f);
	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"RightStay4", 18, 18, 0.15f);
	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"LeftStay4", 22, 22, 0.15f);

	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"UpSit4", 20, 21, 0.3f, false);
	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"DownSit4", 16, 17, 0.3f, false);
	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"RightSit4", 18, 19, 0.3f, false);
	m_AnimalAni->MakeAni(L"BabyChicken.bmp", L"LeftSit4", 22, 23, 0.3f, false);

	/////////////////////////////////////////////////////////////////////////////////////
	//BabyDuck
	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"UpMove5", 8, 11, 0.15f);
	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"DownMove5", 0, 3, 0.15f);
	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"RightMove5", 4, 7, 0.15f);
	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"LeftMove5", 12, 15, 0.15f);

	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"UpStay5", 20, 20, 0.15f);
	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"DownStay5", 16, 16, 0.15f);
	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"RightStay5", 18, 18, 0.15f);
	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"LeftStay5", 22, 22, 0.15f);

	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"UpSit5", 20, 21, 0.3f, false);
	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"DownSit5", 16, 17, 0.3f, false);
	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"RightSit5", 18, 19, 0.3f, false);
	m_AnimalAni->MakeAni(L"BabyDuck.bmp", L"LeftSit5", 22, 23, 0.3f, false);

	/////////////////////////////////////////////////////////////////////////////////////
	//Cow
	m_AnimalAni->MakeAni(L"Cow.bmp", L"UpMove6", 8, 11, 0.15f);
	m_AnimalAni->MakeAni(L"Cow.bmp", L"DownMove6", 0, 3, 0.15f);
	m_AnimalAni->MakeAni(L"Cow.bmp", L"RightMove6", 4, 7, 0.15f);
	m_AnimalAni->MakeAni(L"Cow.bmp", L"LeftMove6", 12, 15, 0.15f);

	m_AnimalAni->MakeAni(L"Cow.bmp", L"UpStay6", 8, 8, 0.15f);
	m_AnimalAni->MakeAni(L"Cow.bmp", L"DownStay6", 0, 0, 0.15f);
	m_AnimalAni->MakeAni(L"Cow.bmp", L"RightStay6", 4, 4, 0.15f);
	m_AnimalAni->MakeAni(L"Cow.bmp", L"LeftStay6", 12, 12, 0.15f);

	m_AnimalAni->MakeAni(L"Cow.bmp", L"UpSit6", 8, 8, 0.3f, false);
	m_AnimalAni->MakeAni(L"Cow.bmp", L"DownSit6", 0, 0, 0.3f, false);
	m_AnimalAni->MakeAni(L"Cow.bmp", L"RightSit6", 4, 4, 0.3f, false);
	m_AnimalAni->MakeAni(L"Cow.bmp", L"LeftSit6", 12, 12, 0.3f, false);

	/////////////////////////////////////////////////////////////////////////////////////
	//Goet
	m_AnimalAni->MakeAni(L"Goat.bmp", L"UpMove7", 8, 11, 0.15f);
	m_AnimalAni->MakeAni(L"Goat.bmp", L"DownMove7", 0, 3, 0.15f);
	m_AnimalAni->MakeAni(L"Goat.bmp", L"RightMove7", 4, 7, 0.15f);
	m_AnimalAni->MakeAni(L"Goat.bmp", L"LeftMove7", 12, 15, 0.15f);

	m_AnimalAni->MakeAni(L"Goat.bmp", L"UpStay7", 8, 8, 0.15f);
	m_AnimalAni->MakeAni(L"Goat.bmp", L"DownStay7", 0, 0, 0.15f);
	m_AnimalAni->MakeAni(L"Goat.bmp", L"RightStay7", 4, 4, 0.15f);
	m_AnimalAni->MakeAni(L"Goat.bmp", L"LeftStay7", 12, 12, 0.15f);

	m_AnimalAni->MakeAni(L"Goat.bmp", L"UpSit7", 8, 8, 0.3f, false);
	m_AnimalAni->MakeAni(L"Goat.bmp", L"DownSit7", 0, 0, 0.3f, false);
	m_AnimalAni->MakeAni(L"Goat.bmp", L"RightSit7", 4, 4, 0.3f, false);
	m_AnimalAni->MakeAni(L"Goat.bmp", L"LeftSit7", 12, 12, 0.3f, false);

	/////////////////////////////////////////////////////////////////////////////////////
	//Sheep
	m_AnimalAni->MakeAni(L"Sheep.bmp", L"UpMove8", 8, 11, 0.15f);
	m_AnimalAni->MakeAni(L"Sheep.bmp", L"DownMove8", 0, 3, 0.15f);
	m_AnimalAni->MakeAni(L"Sheep.bmp", L"RightMove8", 4, 7, 0.15f);
	m_AnimalAni->MakeAni(L"Sheep.bmp", L"LeftMove8", 12, 15, 0.15f);

	m_AnimalAni->MakeAni(L"Sheep.bmp", L"UpStay8", 8, 8, 0.15f);
	m_AnimalAni->MakeAni(L"Sheep.bmp", L"DownStay8", 0, 0, 0.15f);
	m_AnimalAni->MakeAni(L"Sheep.bmp", L"RightStay8", 4, 4, 0.15f);
	m_AnimalAni->MakeAni(L"Sheep.bmp", L"LeftStay8", 12, 12, 0.15f);

	m_AnimalAni->MakeAni(L"Sheep.bmp", L"UpSit8", 8, 8, 0.3f, false);
	m_AnimalAni->MakeAni(L"Sheep.bmp", L"DownSit8", 0, 0, 0.3f, false);
	m_AnimalAni->MakeAni(L"Sheep.bmp", L"RightSit8", 4, 4, 0.3f, false);
	m_AnimalAni->MakeAni(L"Sheep.bmp", L"LeftSit8", 12, 12, 0.3f, false);

	m_AnimalAniArr[ANIMALSTATE::Stay] = L"Stay";
	m_AnimalAniArr[ANIMALSTATE::Move] = L"Move";
	m_AnimalAniArr[ANIMALSTATE::Sit] = L"Sit";

	m_AnimalDirArr[ANIMALDIR::Up] = L"Up";
	m_AnimalDirArr[ANIMALDIR::Down] = L"Down";
	m_AnimalDirArr[ANIMALDIR::Right] = L"Right";
	m_AnimalDirArr[ANIMALDIR::Left] = L"Left";

	ChangeAnimalState(Down, Stay);
}

void Animal::PrevUpdate()
{
}

void Animal::Update()
{
	switch (m_AnimalState)
	{
	case ANIMALSTATE::Stay:
		AStay();
		break;
	case ANIMALSTATE::Move:
		AMove();
		break;
	case ANIMALSTATE::Sit:
		ASit();
		break;
	default:
		break;
	}

	if (false == ClockNumber::EggCheck)
	{
		Animal::TempChicken = Animal::ChickenCount;
	}
	if (false == ClockNumber::EggCheck)
	{
		Animal::TempDuck = Animal::DuckCount;
	}

	if (ANIMALTYPE::Chicken == m_AnimalType)
	{
		if (true == ClockNumber::EggCheck)
		{
			if (0 == Animal::TempChicken)
			{
				return;
			}
			int TempX = rand() % 12 + 1;
			if (3 >= TempX)
			{
				TempX += 2;
			}
			int TempY = rand() % 12 + 1;
			if (6 >= TempY)
			{
				TempY += 5;
			}

			ChickenSp->NewSoundPlay(L"Chicken.wav");
			
			m_ChickenEggPos = Player::IndexWorldPos({ TempX, TempY });
			Egg* CTempEgg = Parent()->MakeActor<Egg>(0);
			CTempEgg->Pos(m_ChickenEggPos);
			++Animal::BabyEggCount;
			--Animal::TempChicken;
			Animal::ChickenEggCheck = true;
		}
	}

	if (ANIMALTYPE::Duck == m_AnimalType)
	{
		if (true == ClockNumber::DEggCheck)
		{
			if (0 == Animal::TempDuck)
			{
				return;
			}
			int DTempX = rand() % 12 + 1;
			if (3 >= DTempX)
			{
				DTempX += 2;
			}
			int DTempY = rand() % 12 + 1;
			if (6 >= DTempY)
			{
				DTempY += 5;
			}

			DuckSp->NewSoundPlay(L"Duck.wav");

			m_DuckEggPos = Player::IndexWorldPos({ DTempX, DTempY });
			Egg* DTempEgg = Parent()->MakeActor<Egg>(1);
			DTempEgg->Pos(m_DuckEggPos);
			++Animal::DBabyEggCount;
			--Animal::TempDuck;
			Animal::DuckEggCheck = true;
		}
	}
}

void Animal::LaterUpdate()
{
}

void Animal::ChangeAnimalState(ANIMALDIR _Dir, ANIMALSTATE _State)
{
	std::wstring ChangeAniName = m_AnimalDirArr[_Dir] + m_AnimalAniArr[_State];
	m_AnimalState = _State;
	m_AnimalDir = _Dir;

	switch (m_AnimalType)
	{
	case Animal::Rabbit:
		ChangeAniName += L"1";
		m_AnimalAni->ChangeAni(ChangeAniName.c_str());
		break;
	case Animal::Duck:
		ChangeAniName += L"2";
		m_AnimalAni->ChangeAni(ChangeAniName.c_str());
		break;
	case Animal::Chicken:
		ChangeAniName += L"3";
		m_AnimalAni->ChangeAni(ChangeAniName.c_str());
		break;
	case Animal::BabyChicken:
		ChangeAniName += L"4";
		m_AnimalAni->ChangeAni(ChangeAniName.c_str());
		break;
	case Animal::BabyDuck:
		ChangeAniName += L"5";
		m_AnimalAni->ChangeAni(ChangeAniName.c_str());
		break;
	case Animal::Cow:
		ChangeAniName += L"6";
		m_AnimalAni->ChangeAni(ChangeAniName.c_str());
		break;
	case Animal::Goet:
		ChangeAniName += L"7";
		m_AnimalAni->ChangeAni(ChangeAniName.c_str());
		break;
	case Animal::Sheep:
		ChangeAniName += L"8";
		m_AnimalAni->ChangeAni(ChangeAniName.c_str());
		break;
	default:
		break;
	}
}

void Animal::AStay()
{
	m_RDir = rand() % 4;
	m_DDir = rand() % 4;
	m_CDir = rand() % 4;
	m_BCDir = rand() % 4;
	m_BDDir = rand() % 4;
	TempTime += DELTATIME * ClockNumber::TimeBoost;

	if (2.0f <= TempTime)
	{
		switch (m_AnimalType)
		{
		case Animal::Rabbit:
			ChangeAnimalState((ANIMALDIR)m_RDir, ANIMALSTATE::Move);
			break;
		case Animal::Duck:
			ChangeAnimalState((ANIMALDIR)m_DDir, ANIMALSTATE::Move);
			break;
		case Animal::Chicken:
			ChangeAnimalState((ANIMALDIR)m_CDir, ANIMALSTATE::Move);
			break;
		case Animal::BabyChicken:
			ChangeAnimalState((ANIMALDIR)m_BCDir, ANIMALSTATE::Move);
			break;
		case Animal::BabyDuck:
			ChangeAnimalState((ANIMALDIR)m_BDDir, ANIMALSTATE::Move);
			break;
		case Animal::Cow:
			ChangeAnimalState((ANIMALDIR)m_BCDir, ANIMALSTATE::Move);
			break;
		case Animal::Goet:
			ChangeAnimalState((ANIMALDIR)m_BDDir, ANIMALSTATE::Move);
			break;
		case Animal::Sheep:
			ChangeAnimalState((ANIMALDIR)m_RDir, ANIMALSTATE::Move);
			break;
		default:
			break;
		}
		TempTime = 0.0f;
	}
}

void Animal::AMove()
{
	int Test = 0;
	Test = rand() % 4;
	switch (Test)
	{
	case 0:
		m_UTemp = 5.05f;
		m_DTemp = 7.05f;
		m_RTemp = 6.05f;
		m_LTemp = 6.05f;
		break;
	case 1:
		m_UTemp = 8.05f;
		m_DTemp = 5.05f;
		m_RTemp = 4.05f;
		m_LTemp = 6.05f;
		break;
	case 2:
		m_UTemp = 2.05f;
		m_DTemp = 5.05f;
		m_RTemp = 4.05f;
		m_LTemp = 7.05f;
		break;
	case 3:
		m_UTemp = 6.05f;
		m_DTemp = 4.05f;
		m_RTemp = 3.05f;
		m_LTemp = 8.05f;
		break;
	default:
		break;
	}

	m_UTemp /= ClockNumber::TimeBoost;
	m_DTemp /= ClockNumber::TimeBoost;
	m_RTemp /= ClockNumber::TimeBoost;
	m_LTemp /= ClockNumber::TimeBoost;

	ANIMALDIR TempDir = m_AnimalDir;
	m_Time += DELTATIME;

	FPOS TestPos = m_Pos;

	if (Animal::Up == TempDir)
	{
		m_Pos.Y += (m_AnimalSpeed * ClockNumber::TimeBoost * DELTATIME * DUP.Y);
		if (0 == m_AnimalTile->FindSpriteIndex(Player::WorldPlayerIndex(UColl->PivotPos())))
		{
			m_Pos = TestPos;
		}
		if (m_UTemp <= m_Time)
		{
			m_Time = 0.0f;
			ChangeAnimalState(TempDir, ANIMALSTATE::Sit);
		}
	}
	else if (Animal::Down == TempDir)
	{
		m_Pos.Y += (m_AnimalSpeed * ClockNumber::TimeBoost * DELTATIME * DDOWN.Y);
		if (0 == m_AnimalTile->FindSpriteIndex(Player::WorldPlayerIndex(DColl->PivotPos())))
		{
			m_Pos = TestPos;
		}
		if (m_DTemp <= m_Time)
		{
			m_Time = 0.0f;
			ChangeAnimalState(TempDir, ANIMALSTATE::Sit);
		}
	}
	else if (Animal::Left == TempDir)
	{
		m_Pos.X += (m_AnimalSpeed * ClockNumber::TimeBoost * DELTATIME * DLEFT.X);
		if (0 == m_AnimalTile->FindSpriteIndex(Player::WorldPlayerIndex(LColl->PivotPos())))
		{
			m_Pos = TestPos;
		}
		if (m_LTemp <= m_Time)
		{
			m_Time = 0.0f;
			ChangeAnimalState(TempDir, ANIMALSTATE::Sit);
		}
	}
	else if (Animal::Right == TempDir)
	{
		m_Pos.X += (m_AnimalSpeed * ClockNumber::TimeBoost * DELTATIME * DRIGHT.X);
		if (0 == m_AnimalTile->FindSpriteIndex(Player::WorldPlayerIndex(RColl->PivotPos())))
		{
			m_Pos = TestPos;
		}
		if (m_RTemp <= m_Time)
		{
			m_Time = 0.0f;
			ChangeAnimalState(TempDir, ANIMALSTATE::Sit);
		}
	}
}

void Animal::ASit()
{
	if (true == m_AnimalAni->AniEndCheck())
	{
		ChangeAnimalState(m_AnimalDir, ANIMALSTATE::Stay);
	}
}

void Animal::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void Animal::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (ANIMALTYPE::Cow == m_AnimalType || ANIMALTYPE::Goet == m_AnimalType || ANIMALTYPE::Sheep == m_AnimalType)
	{
		if (125 == _This->CollNum())
		{
			if (true == KEYDOWN("Enter"))
			{
				if (true == OVERPLAYER->PutItem(ITEM.GetItem(6, 0)))
				{
					CowSp->NewSoundPlay(L"Cow.wav");

					TwinkleEffect* TestEf = Parent()->MakeActor<TwinkleEffect>();
					TestEf->Pos({ m_Pos.X, m_Pos.Y - 64 });

					HarvEffect* m_HEffect = Parent()->MakeActor<HarvEffect>();
					m_HEffect->HarvRender()->SetSprite(L"Milk.bmp", 0);
					m_HEffect->Pos({ m_Pos.X, m_Pos.Y - 40 });
				}
			}
		}
		if (126 == _This->CollNum())
		{
			if (true == KEYDOWN("Enter"))
			{
				if (true == OVERPLAYER->PutItem(ITEM.GetItem(6, 1)))
				{
					GoetSp->NewSoundPlay(L"Goet.wav");

					TwinkleEffect* TestEf = Parent()->MakeActor<TwinkleEffect>();
					TestEf->Pos({ m_Pos.X, m_Pos.Y - 64 });

					HarvEffect* m_HEffect = Parent()->MakeActor<HarvEffect>();
					m_HEffect->HarvRender()->SetSprite(L"Milk.bmp", 1);
					m_HEffect->Pos({ m_Pos.X, m_Pos.Y - 40 });
				}
			}
		}
		if (127 == _This->CollNum())
		{
			if (true == KEYDOWN("Enter"))
			{
				if (true == OVERPLAYER->PutItem(ITEM.GetItem(6, 2)))
				{
					GoetSp->NewSoundPlay(L"Sheep.wav");

					TwinkleEffect* TestEf = Parent()->MakeActor<TwinkleEffect>();
					TestEf->Pos({ m_Pos.X, m_Pos.Y - 64 });

					HarvEffect* m_HEffect = Parent()->MakeActor<HarvEffect>();
					m_HEffect->HarvRender()->SetSprite(L"Milk.bmp", 2);
					m_HEffect->Pos({ m_Pos.X, m_Pos.Y - 40 });
				}
			}
		}
	}
	else
	{
		if (122 == _This->CollNum())
		{
			if (true == KEYDOWN("Enter"))
			{
				Imotion* Temp = Parent()->MakeActor<Imotion>();
				Temp->Pos({ this->Pos().X, this->Pos().Y - TILESIZEH - 20 });
			}
		}
	}
}

void Animal::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}




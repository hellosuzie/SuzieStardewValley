#include "stdafx.h"
#include "Monster.h"
#include "AniActorRender.h"
#include "EnterMgr.h"
#include "MathMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "ActorCollision.h"
#include "Damage.h"
#include "SoundPlayer.h"
#include "ResourceMgr.h"

bool Monster::AttackCheck = true;
bool Monster::SoundCheck = true;

Monster::Monster(int _Num) 
	: m_MonsterSpeed(80.0f)
	, m_AttackHelper(4.0f)
	, m_DieHelper(2.0f)
	, m_PlayerRendCheck(true)
	, m_MonsterState(MONSTERSTATE::STAY)
	, m_MonsterType((MONSTERTYPE)_Num)
	, m_MonsterHp(50)
	, m_Att(10)
	, Time(0.0f)
{
	m_TypeNum = _Num;
}

Monster::~Monster()
{
	SoundCheck = true;
}

void Monster::Init()
{
	MonsterSp = GETSOUND;

	m_MonsterAni = MakeRender<AniActorRender>(15);
	m_MonsterAni->Size(FPOS{ 64, 68 });

	MakeCollision(L"Monster", { 64, 68 }, 102);

	//Ani
	m_MonsterAni->MakeAni(L"Monster.bmp", L"BatMove", 4, 7);
	m_MonsterAni->MakeAni(L"Monster.bmp", L"BatAtt", 4, 7);
	m_MonsterAni->MakeAni(L"Monster.bmp", L"BatStay", 0, 0);
	m_MonsterAni->MakeAni(L"Monster.bmp", L"BatDie", 13, 13);

	m_MonsterAni->MakeAni(L"Bug.bmp", L"UpBugMove", 8, 11);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"DownBugMove", 0, 3);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"LeftBugMove", 4, 7);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"RightBugMove", 12, 15);

	m_MonsterAni->MakeAni(L"Bug.bmp", L"UpBugAtt", 8, 11);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"DownBugAtt", 0, 3);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"RightBugAtt", 4, 7);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"LeftBugAtt", 12, 15);

	m_MonsterAni->MakeAni(L"Bug.bmp", L"UpBugStay", 8, 8);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"DownBugStay", 0, 0);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"RightBugStay", 9, 9);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"LeftBugStay", 12, 12);

	m_MonsterAni->MakeAni(L"Bug.bmp", L"UpBugDie", 16, 16);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"DownBugDie", 16, 16);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"LeftBugDie", 16, 16);
	m_MonsterAni->MakeAni(L"Bug.bmp", L"RightBugDie", 16, 16);

	//AniName
	m_MonsterTypeArr[Bat] = L"Bat";
	m_MonsterTypeArr[Bug] = L"Bug";

	m_MonsterAniArr[STAY] = L"Stay";
	m_MonsterAniArr[MOVE] = L"Move";
	m_MonsterAniArr[ATT] = L"Att";
	m_MonsterAniArr[DIE] = L"Die";

	m_MonsterDirArr[Up] = L"Up";
	m_MonsterDirArr[Down] = L"Down";
	m_MonsterDirArr[Left] = L"Left";
	m_MonsterDirArr[Right] = L"Right";

	ChangeMonsterState((MONSTERTYPE)m_TypeNum, MONSTERSTATE::STAY);
}

void Monster::PrevUpdate()
{
}

void Monster::Update()
{
	m_MToPDis = MathMgr::PointToPointDis(m_MonsterAni->GetRenderPos(), m_DirPlayer->MainPlayerRender()->GetRenderPos());

	switch (m_MonsterState)
	{
	case Monster::STAY:
		MStay();
		break;
	case Monster::MOVE:
		MMove();
		break;
	case Monster::ATT:
		MAtt();
		break;
	case Monster::DIE:
		MDie();
		break;
	default:
		break;
	}

	if (0 >= m_MonsterHp)
	{
		if (true == SoundCheck)
		{
			MonsterDieSound();
		}
		ChangeMonsterState(MONSTERSTATE::DIE);
	}
}

void Monster::LaterUpdate()
{
}

void Monster::MonsterDieSound()
{
	MonsterSp->NewSoundPlay(L"Mon_dead.wav");
	SoundCheck = false;	
}

void Monster::MonsterDirCheck()
{
	FPOS MonsterTempPos = m_MonsterAni->GetRenderPos();
	FPOS PlayerTempPos = m_DirPlayer->MainPlayerRender()->GetRenderPos();

	if (0 == m_TypeNum)
	{
		FPOS DirPos = MathMgr::PointToPointDir(MonsterTempPos, PlayerTempPos);
		m_Pos += DirPos * m_MonsterSpeed * DELTATIME;
	}
	else
	{
		if (MonsterTempPos.Y > PlayerTempPos.Y)
		{
			m_MonsterDir = MONSTERDIR::Up;
		}
		else if (MonsterTempPos.Y - TILESIZE <= PlayerTempPos.Y)
		{
			m_MonsterDir = MONSTERDIR::Down;
		}

		FPOS DirPos = MathMgr::PointToPointDir(MonsterTempPos, PlayerTempPos);
		m_Pos += DirPos * m_MonsterSpeed * DELTATIME;
	}
}

void Monster::ChangeMonsterState(MONSTERTYPE _Type, MONSTERSTATE _State)
{
	if (0 == m_TypeNum)
	{
		std::wstring ChangeStateName = m_MonsterTypeArr[_Type] + m_MonsterAniArr[_State];
		m_MonsterAni->ChangeAni(ChangeStateName.c_str());
		m_MonsterState = _State;
		m_MonsterType = _Type;
	}
	else
	{
		std::wstring ChangeStateName = m_MonsterDirArr[m_MonsterDir] + m_MonsterTypeArr[_Type] + m_MonsterAniArr[_State];
		m_MonsterAni->ChangeAni(ChangeStateName.c_str());
		m_MonsterState = _State;
		m_MonsterType = _Type;
	}
}

void Monster::ChangeMonsterState(MONSTERSTATE _State)
{
	if (0 == m_TypeNum)
	{
		std::wstring ChangeStateName = m_MonsterTypeArr[m_MonsterType] + m_MonsterAniArr[_State];
		m_MonsterAni->ChangeAni(ChangeStateName.c_str());
		m_MonsterState = _State;
	}
	else
	{
		std::wstring ChangeStateName = m_MonsterDirArr[m_MonsterDir] + m_MonsterTypeArr[m_MonsterType] + m_MonsterAniArr[_State];
		m_MonsterAni->ChangeAni(ChangeStateName.c_str());
		m_MonsterState = _State;
	}
}

void Monster::MStay()
{
	if (200 > m_MToPDis)
	{
		ChangeMonsterState(MONSTERSTATE::MOVE);
	}
}

void Monster::MMove()
{
	MonsterDirCheck();
	if (300 < m_MToPDis)
	{
		ChangeMonsterState(MONSTERSTATE::STAY);
	}
	if (100 > m_MToPDis)
	{
		ChangeMonsterState(MONSTERSTATE::ATT);
	}
}

void Monster::MAtt()
{
	MonsterDirCheck();
	if (200 < m_MToPDis)
	{
		ChangeMonsterState(MONSTERSTATE::MOVE);
	}
}

void Monster::MDie()
{
	Time += DELTATIME;
	m_MonsterAni->SetAlpha(255 - (int)((Time * 255) * 0.5f));

	if (true == m_DieHelper.TimeCheck())
	{
		Die();
		m_DieHelper.TimeReset();
	}
}

//검이랑 충돌하고 아무것도안하기
//bool 값으로 시간 재서 무적상태 만들기0

void Monster::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void Monster::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (MONSTERSTATE::ATT == m_MonsterState)
	{ 
		FPOS TempPos = m_MonsterAni->GetRenderPos();
		FPOS DirPos = MathMgr::PointToPointDir(TempPos, m_DirPlayer->MainPlayerRender()->GetRenderPos());
		
		if (101 == _Other->CollNum())
		{
			if (true == AttackCheck)
			{
				if (true == Player::CurPlayer->ReducePlayerEnergy(m_Att))
				{
					Damage* PlayerBlood = Parent()->MakeActor<Damage>();
					PlayerBlood->Pos({ Player::CurPlayer->Pos().X, Player::CurPlayer->Pos().Y - 70 });
					AttackCheck = false;
				}
			}
		}

		if (true == m_AttackHelper.TimeCheck())
		{
			AttackCheck = true;
			m_AttackHelper.TimeReset();
		}
	}
}

void Monster::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}




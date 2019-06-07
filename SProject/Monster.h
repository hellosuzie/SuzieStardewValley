#pragma once
#include "ActorBase.h"
#include "TimeHelper.h"

class SoundPlayer;
class Player;
class AniActorRender;
class Monster :	public ActorBase
{
	enum MONSTERTYPE
	{
		Bat,
		Bug,
		TypeMax
	};

	enum MONSTERSTATE
	{
		STAY,
		MOVE,
		ATT,
		DIE,
		STATEMAX
	};

	enum MONSTERDIR
	{
		Up,
		Down,
		Left,
		Right,
		MDirMax
	};

private:
	int m_MonsterHp;
	size_t m_MonsterAtt;

private:
	float m_MToPDis;

	Player* m_DirPlayer;
	float m_MonsterSpeed;

	TimeHelper m_AttackHelper;
	TimeHelper m_DieHelper;
	bool m_PlayerRendCheck;

	int m_TypeNum;
	size_t m_Att;
	float Time;

	MONSTERDIR m_MonsterDir;

private:
	SoundPlayer* MonsterSp;

public:
	static bool AttackCheck;
	static bool SoundCheck;

private:
	AniActorRender* m_MonsterAni;

	MONSTERSTATE m_MonsterState;
	MONSTERTYPE m_MonsterType;

	std::wstring m_MonsterDirArr[MDirMax];
	std::wstring m_MonsterTypeArr[TypeMax];
	std::wstring m_MonsterAniArr[STATEMAX];

public:
	Monster(int _Num);
	~Monster();

public:
	inline size_t MonsterHp()
	{
		return m_MonsterHp;
	}
	inline bool MonsterHp(int _Num)
	{
		if (0 == m_MonsterHp)
		{
			m_MonsterHp = 0;
			return false;
		}
		m_MonsterHp -= _Num;
		return true;
	}

	inline size_t MonsterAtt()
	{
		return m_MonsterAtt;
	}
	inline void MonsterAtt(size_t _Att)
	{
		m_MonsterAtt = _Att;
	}

	MONSTERSTATE MonsterState()
	{
		return m_MonsterState;
	}
	inline void SetDirPlayer(Player* _Player)
	{
		m_DirPlayer = _Player;
	}
	inline void MonsterType(int _Num)
	{
		m_MonsterType = (MONSTERTYPE)_Num;
	}

	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

private:
	void MonsterDirCheck();
	void MonsterDieSound();

public:
	void ChangeMonsterState(MONSTERTYPE _Type, MONSTERSTATE _State);
	void ChangeMonsterState(MONSTERSTATE _State);

private:
	void MStay();
	void MMove();
	void MAtt();
	void MDie();

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other);
	void CollStay(ActorCollision* _This, ActorCollision* _Other);
	void CollExit(ActorCollision* _This, ActorCollision* _Other);

};


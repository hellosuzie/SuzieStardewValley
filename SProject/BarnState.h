#pragma once
#include "GameState.h"
#include <set>

class SoundPlayer;
class Ladder;
class HarvEffect;
class Rocks;
class BarnTile;
class Player;
class Monster;
class BarnBack;
class BarnState :	public GameState
{
private:
	SoundPlayer* BarnSp;
	SoundPlayer* BarnSp0;
	SoundPlayer* BarnSp1;

private:
	BarnBack* m_BarnBack;
	Monster* m_MainMonster;
	Player* m_MainPlayer;
	Rocks* m_MineRocks;
	HarvEffect* m_HEffect;

	BarnTile* m_BarnTile;
	Ladder* m_Ladder;

	IPOS m_RectPos;
	FPOS StartPlayerPos;

	std::map<__int64, Rocks*> m_RockMap;
	std::map<__int64, Rocks*>::iterator m_RFindIter;

	std::set<int> m_RandomSet;
	std::set<int>::iterator StartIter;
	std::set<int>::iterator EndIter;

public:
	static FPOS MineStartPos;

public:
	BarnState();
	~BarnState();

public:
	inline BarnTile* GetBarnTile()
	{
		return m_BarnTile;
	}

public:
	void ChangeBegin() override;
	void ChangeEnd() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;

	void PlayerAction();
	void PlayerDirCheck(IPOS _Pos);
	void EatWork(int _InvenNum);
};


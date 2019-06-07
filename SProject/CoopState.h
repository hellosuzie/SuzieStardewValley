#pragma once
#include "GameState.h"
#include <set>

class SoundPlayer;
class Ladder;
class HarvEffect;
class Rocks;
class CoopTile;
class Player;
class Monster;
class CoopBack;
class CoopState :	public GameState
{
private:
	SoundPlayer* CoopSp;
	SoundPlayer* CoopSp0;
	SoundPlayer* CoopSp1;

private:
	CoopBack* m_CoopBack;
	Monster* m_MainMonster;
	Player* m_MainPlayer;
	Rocks* m_MineRocks;
	HarvEffect* m_HEffect;

	CoopTile* m_CoopTile;
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
	CoopState();
	~CoopState();

public:
	inline CoopTile* GetCoopTile()
	{
		return m_CoopTile;
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


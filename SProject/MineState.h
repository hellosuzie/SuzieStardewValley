#pragma once
#include "GameState.h"
#include <set>

class SoundPlayer;
class Ladder;
class HarvEffect;
class Rocks;
class MineTile;
class Player;
class Monster;
class MineBack;
class MineState :	public GameState
{
public:
	static SoundPlayer* MineSp0;

private:
	SoundPlayer* MineSp;


private:
	MineBack* m_MineBack;
	Monster* m_MainMonster;
	Player* m_MainPlayer;
	Rocks* m_MineRocks;
	HarvEffect* m_HEffect;

	MineTile* m_MineTile;
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
	MineState();
	~MineState();

public:
	void ChangeBegin() override;
	void ChangeEnd() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;

	void PlayerAction();
	void PlayerDirCheck(IPOS _Pos);
	void PickAxeWork(IPOS _Pos);
};


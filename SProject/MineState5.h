#pragma once
#include "GameState.h"
#include <set>

class SoundPlayer;
class HarvEffect;
class Rocks;
class MineTile5;
class Player;
class Monster;
class MineBack;
class MineState5 :	public GameState
{
private:
	SoundPlayer* Mine5Sp;

private:
	MineBack* m_MineBack;
	Monster* m_MainMonster;
	Player* m_MainPlayer;
	Rocks* m_MineRocks;
	HarvEffect* m_HEffect;

	MineTile5* m_MineTile;

	IPOS m_RectPos;
	FPOS StartPlayerPos;

	std::map<__int64, Rocks*> m_RockMap;
	std::map<__int64, Rocks*>::iterator m_RFindIter;

public:
	MineState5();
	~MineState5();

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

	void RockInit();
};


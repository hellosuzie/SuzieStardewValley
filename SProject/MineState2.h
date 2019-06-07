#pragma once
#include "GameState.h"
#include <set>

class SoundPlayer;
class HarvEffect;
class Rocks;
class MineTile2;
class Player;
class Monster;
class MineBack;
class MineState2 :	public GameState
{
private:
	SoundPlayer* Mine2Sp;

private:
	MineBack* m_MineBack;
	Monster* m_MainMonster;
	Player* m_MainPlayer;
	Rocks* m_MineRocks;
	HarvEffect* m_HEffect;

	MineTile2* m_MineTile;

	IPOS m_RectPos;
	FPOS StartPlayerPos;

	std::map<__int64, Rocks*> m_RockMap;
	std::map<__int64, Rocks*>::iterator m_RFindIter;

public:
	MineState2();
	~MineState2();

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


#pragma once
#include "GameState.h"
#include <set>

class SoundPlayer;
class HarvEffect;
class Rocks;
class MineTile1;
class Player;
class MineBack;
class MineState1 :	public GameState
{
private:
	SoundPlayer* Mine1Sp;

private:
	MineBack* m_MineBack;
	Player* m_MainPlayer;
	Rocks* m_MineRocks;
	HarvEffect* m_HEffect;

	MineTile1* m_MineTile;

	IPOS m_RectPos;
	FPOS StartPlayerPos;

	std::map<__int64, Rocks*> m_RockMap;
	std::map<__int64, Rocks*>::iterator m_RFindIter;

public:
	MineState1();
	~MineState1();

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


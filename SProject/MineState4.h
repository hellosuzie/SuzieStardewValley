#pragma once
#include "GameState.h"
#include <set>

class SoundPlayer;
class HarvEffect;
class Rocks;
class MineTile4;
class Player;
class MineBack;
class MineState4 :	public GameState
{
private:
	SoundPlayer* Mine4Sp;

private:
	MineBack* m_MineBack;
	Player* m_MainPlayer;
	Rocks* m_MineRocks;
	HarvEffect* m_HEffect;

	MineTile4* m_MineTile;

	IPOS m_RectPos;
	FPOS StartPlayerPos;

	std::map<__int64, Rocks*> m_RockMap;
	std::map<__int64, Rocks*>::iterator m_RFindIter;

public:
	MineState4();
	~MineState4();

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


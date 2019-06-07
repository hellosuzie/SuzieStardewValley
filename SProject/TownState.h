#pragma once
#include "GameState.h"

class SoundPlayer;
class Player;
class TownBack;
class TownTile;
class TownState :
	public GameState
{
private:
	SoundPlayer* TownSp;

private:
	Player* m_MainPlayer;
	TownBack* m_TownBack;
	TownTile* m_TownTile;

	FPOS StartPlayerPos;

public:
	TownState();
	~TownState();

public:
	void ChangeBegin() override;
	void ChangeEnd() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;
};


#pragma once
#include "GameState.h"

class SoundPlayer;
class Player;
class Town2Back;
class Town2Tile;
class Town2State :
	public GameState
{
private:
	SoundPlayer* Town2Sp;

private:
	Player* m_MainPlayer;
	Town2Back* m_Town2Back;
	Town2Tile* m_Town2Tile;

	FPOS StartPlayerPos;

public:
	Town2State();
	~Town2State();

public:
	void ChangeBegin() override;
	void ChangeEnd() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;
};


#pragma once
#include "GameState.h"

class SoundPlayer;
class Player;
class RobinTile;
class RobinBack;
class RobinState :
	public GameState
{
private:
	SoundPlayer* RobinSp;
	SoundPlayer* RobinSp0;

private:
	Player* m_MainPlayer;
	FPOS StartPlayerPos;
	RobinBack* m_RobinBack;
	RobinTile* m_RobinTile;

public:
	RobinState();
	~RobinState();

public:
	void ChangeBegin() override;
	void ChangeEnd() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;

};


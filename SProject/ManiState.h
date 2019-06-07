#pragma once
#include "GameState.h"

class SoundPlayer;
class Player;
class ManiTile;
class ManiBack;
class ManiState :
	public GameState
{
private:
	SoundPlayer* ManiSp;
	SoundPlayer* ManiSp0;

private:
	Player* m_MainPlayer;
	FPOS StartPlayerPos;
	ManiBack* m_ManiBack;
	ManiTile* m_ManiTile;

public:
	ManiState();
	~ManiState();

public:
	void ChangeBegin() override;
	void ChangeEnd() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;

};


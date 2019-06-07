#pragma once
#include "GameState.h"

class SoundPlayer;
class Player;
class StoreTile;
class StoreBack;
class StoreState :
	public GameState
{
private:
	SoundPlayer* StoreSp;
	SoundPlayer* StoreSp0;

private:
	Player* m_MainPlayer;
	FPOS StartPlayerPos;
	StoreBack* m_StoreBack;
	StoreTile* m_StoreTile;

public:
	StoreState();
	~StoreState();

public:
	void ChangeBegin() override;
	void ChangeEnd() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;

};


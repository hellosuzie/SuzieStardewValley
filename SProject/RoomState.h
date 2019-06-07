#pragma once
#include "GameState.h"

class SoundPlayer;
class RoomTile;
class RoomBack;
class RoomState :	public GameState
{
private:
	RoomBack* m_RoomBack;
	RoomTile* m_RoomTile;

	FPOS StartPlayerPos;
	SoundPlayer* RoomSp;
	SoundPlayer* RoomSp0;

public:
	RoomState();
	~RoomState();

public:
	void ChangeBegin() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;

	void ChangeEnd() override;
};


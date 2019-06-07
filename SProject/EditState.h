#pragma once
#include "GameState.h"

class TileMapEdit;
class TileAim;
class EditState :
	public GameState
{
private:
	TileAim* m_EditAim;
	TileMapEdit* m_TestTile;

public:
	EditState();
	~EditState();

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;
};


#pragma once
#include "GameState.h"

class SoundPlayer;
class TitleBack;
class TitleCloud;
class TitleState :
	public GameState
{
private:
	TitleCloud* m_Cloud;
	TitleBack* m_Back;

	SoundPlayer* TitleSp;

public:
	TitleState();
	~TitleState();

public:
	void ChangeBegin() override;
	void ChangeEnd() override;

	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;

	void TitleButton();
	static void __stdcall GoRoomState(void*);
};


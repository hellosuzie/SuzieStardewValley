#pragma once
#include "GameState.h"

class SoundPlayer;
class EndBack;
class EndState :
	public GameState
{
private:
	EndBack* m_Back;

	SoundPlayer* TitleSp;

public:
	EndState();
	~EndState();

public:
	void ChangeBegin() override;
	void ChangeEnd() override;

	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;
};


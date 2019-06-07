#pragma once
#include "GameState.h"
#include "TimeHelper.h"

class FirstTitle :
	public GameState
{
private:
	TimeHelper ChangeScene;

public:
	FirstTitle();
	~FirstTitle();

public:
	void ChangeBegin() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;

	void ChangeEnd() override;
};


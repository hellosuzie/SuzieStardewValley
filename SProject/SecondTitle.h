#pragma once
#include "GameState.h"
#include "TimeHelper.h"

class SingleActorRender;
class SecondTitle :
	public GameState
{
private:
	TimeHelper ChangeScene;

private:
	SingleActorRender* m_FirstTitleRender;

public:
	SecondTitle();
	~SecondTitle();

public:
	void ChangeBegin() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;

	void ChangeEnd() override;
};


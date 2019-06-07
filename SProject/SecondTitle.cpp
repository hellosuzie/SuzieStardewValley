#include "stdafx.h"
#include "SecondTitle.h"
#include "Brighten.h"
#include "SecondTitleAni.h"

SecondTitle::SecondTitle() : ChangeScene(5.0f)
{
}


SecondTitle::~SecondTitle()
{
}

void SecondTitle::ChangeBegin()
{
}

void SecondTitle::StateInit()
{
	MakeActor<Brighten>();
	MakeActor<SecondTitleAni>();
}

void SecondTitle::StateUpdate()
{
	if (true == ChangeScene.TimeCheck())
	{
		CORE.ChangeState(ALLSTATE::TITLE);
		ChangeScene.TimeReset();
	}
}

void SecondTitle::DebugUpdate()
{
}

void SecondTitle::ChangeEnd()
{
}

#include "stdafx.h"
#include "FirstTitle.h"
#include "AniActorRender.h"
#include "Brighten.h"
#include "FirstTitleAni.h"
#include "TimeHelper.h"

FirstTitle::FirstTitle() : ChangeScene(2.0f)
{
}


FirstTitle::~FirstTitle()
{
}

void FirstTitle::ChangeBegin()
{
}

void FirstTitle::ChangeEnd()
{
}

void FirstTitle::StateInit()
{
	MakeActor<Brighten>();
	MakeActor<FirstTitleAni>();
}

void FirstTitle::StateUpdate()
{
	if (true == ChangeScene.TimeCheck())
	{
		CORE.ChangeState(ALLSTATE::TITLE2);
		ChangeScene.TimeReset();
	}
}

void FirstTitle::DebugUpdate()
{
}




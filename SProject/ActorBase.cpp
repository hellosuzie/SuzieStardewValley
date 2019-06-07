#include "stdafx.h"
#include "ActorBase.h"
#include "ActorRender.h"
#include "ActorCollision.h"
#include "TimeMgr.h"
#include "TimeHelper.h"

ActorBase::ActorBase() : m_ScaleRatio(1.0f), m_TimerOne(0.1f), m_TimerTwo(0.2f), m_StateOver(false)
{
}


ActorBase::~ActorBase()
{
	std::list<ActorRender*>::iterator StartIter = m_RenderList.begin();
	std::list<ActorRender*>::iterator EndIter = m_RenderList.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			delete (*StartIter);
		}
	}
	m_RenderList.clear();

	std::list<ActorCollision*>::iterator StartCIter = m_CollList.begin();
	std::list<ActorCollision*>::iterator EndCIter = m_CollList.end();

	for (; StartCIter != EndCIter; ++StartCIter)
	{
		if (nullptr != (*StartCIter))
		{
			delete (*StartCIter);
		}
	}
	m_CollList.clear();
}

void ActorBase::PrevUpdate()
{
}

void ActorBase::Update()
{
}

void ActorBase::LaterUpdate()
{
}

FPOS ActorBase::ScreenPos()
{
	return m_Pos - Parent()->MainCamera()->CameraPos();
}

ActorCollision * ActorBase::MakeCollision(const WCHAR * _ColGroupName, FSIZE _Size, int _CollNum/* = 0*/)
{
	ActorCollision* NewColl= new ActorCollision();
	NewColl->Actor(this);
	NewColl->Size(_Size);
	NewColl->CollNum(_CollNum);
	NewColl->m_GroupName = _ColGroupName;
	m_CollList.push_back(NewColl);
	Parent()->PushCollision(_ColGroupName, NewColl);
	return NewColl;
}

void ActorBase::DebugRender()
{
}

void ActorBase::Vibration()
{
	if (nullptr != this)
	{
		if (true == m_TimerTwo.TimeCheck())
		{
			m_TimerOne.TimeReset();
			m_TimerTwo.TimeReset();
		}
		if (true == m_TimerOne.TimeCheck())
		{
			m_Pos += DRIGHT * DELTATIME * 1500.0f;
		}
		else
		{
			m_Pos += DLEFT * DELTATIME * 1500.0f;
		}
	}
}


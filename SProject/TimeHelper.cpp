#include "stdafx.h"
#include "TimeHelper.h"
#include "TimeMgr.h"

TimeHelper::TimeHelper(float _Time) : m_Time(_Time), m_CurTime(0.0f)
{
}


TimeHelper::~TimeHelper()
{
}

bool TimeHelper::TimeCheck(float _Scale)
{
	m_CurTime += (TIME.DeltaTime() * _Scale);
	if (m_CurTime >= m_Time)
	{
		return true;
	}
	return false;
}

void TimeHelper::TimeReset()
{
	m_CurTime = 0.0f;
}

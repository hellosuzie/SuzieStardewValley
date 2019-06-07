#include "stdafx.h"
#include "TimeMgr.h"


TimeMgr::Timer::Timer()
	: m_OneSecCount(), m_CurCount(), m_PrevCount(), m_DeltaTime(0.0f)
	, m_FPS(0), m_FPSAcc(0), m_FPSTimeAcc(0.0f)
{
	//cpu가 1초에 셀 수 있는 카운트.
	QueryPerformanceFrequency(&m_OneSecCount);
	//지금까지 센 카운트.
	QueryPerformanceCounter(&m_CurCount);
	m_PrevCount = m_CurCount;
}

TimeMgr::Timer::~Timer()
{
}

void TimeMgr::Timer::Update()
{
	QueryPerformanceCounter(&m_CurCount);
	m_DeltaTime = (m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)m_OneSecCount.QuadPart;
	m_PrevCount = m_CurCount;
}

void TimeMgr::Timer::CurFPS()
{
	++m_FPSAcc;
	m_FPSTimeAcc += m_DeltaTime;

	if ( 1.0f <= m_FPSTimeAcc )
	{
		m_FPS = (int)(m_FPSAcc / m_FPSTimeAcc);
		m_FPSAcc = 0;
		m_FPSTimeAcc = 0.0f;
	}
}


TimeMgr::TimeMgr()
{
}


TimeMgr::~TimeMgr()
{
}

void TimeMgr::Update()
{
	m_MainTimer.Update();
	m_MainTimer.CurFPS();
}


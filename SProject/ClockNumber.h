#pragma once
#include "ActorBase.h"
#include "TimeHelper.h"

class SingleActorRender;
class ClockNumber :
	public ActorBase
{
private:
	static int MinCheck;
	static int HourCheck;
	static int DayCheck;
	static int DayNumCheck;
	static int ClockNum;

public:
	static float TimeBoost;
	static bool EggCheck;
	static bool DEggCheck;
	static bool BabyCheck;
	static bool DBabyCheck;

private:
	SingleActorRender* m_DayRender;
	SingleActorRender* m_DayNumRender;
	
	SingleActorRender* m_1TimeRender;
	SingleActorRender* m_2TimeRender;
	SingleActorRender* m_3TimeRender;
	SingleActorRender* m_ColonRender;

	SingleActorRender* m_NightRender;

private:
	TimeHelper MinTimer;

public:
	ClockNumber();
	~ClockNumber();

public:
	SingleActorRender* DayRender()
	{
		return m_DayRender;
	}
	SingleActorRender* DayNumRender()
	{
		return m_DayNumRender;
	}

	SingleActorRender* TimeRender1() 
	{
		return m_1TimeRender;
	}
	SingleActorRender* TimeRender2()
	{
		return m_2TimeRender;
	}
	SingleActorRender* TimeRender3()
	{
		return m_3TimeRender;
	}
	SingleActorRender* ColonRender()
	{
		return m_ColonRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

};


#include "stdafx.h"
#include "ClockNumber.h"
#include "SingleActorRender.h"
#include "Clock.h"
#include "GameSprite.h"
#include "Animal.h"

int ClockNumber::MinCheck = 0;
int ClockNumber::HourCheck = 0;
int ClockNumber::DayCheck = 0;
int ClockNumber::DayNumCheck = 0;
int ClockNumber::ClockNum = 0;
float ClockNumber::TimeBoost = 1.0f;
bool ClockNumber::EggCheck = false;
bool ClockNumber::DEggCheck = false;
bool ClockNumber::BabyCheck = false;
bool ClockNumber::DBabyCheck = false;

ClockNumber::ClockNumber() : MinTimer(10.0f)
{
	Pos({ 910, 120 });
}

ClockNumber::~ClockNumber()
{
}

void ClockNumber::Init()
{
	m_DayRender = MakeRender<SingleActorRender>(20);
	m_DayRender->SetSprite(L"Day.bmp", 0);
	m_DayRender->Size({ 70, 26 });
	m_DayRender->Pivot({ 15, -80 });
	m_DayRender->CameraMode(false);

	m_DayNumRender = MakeRender<SingleActorRender>(18);
	m_DayNumRender->SetSprite(L"TimeNumber.bmp", 0);
	m_DayNumRender->Size({ 32, 24 });
	m_DayNumRender->Pivot({ 73, -80 });
	m_DayNumRender->CameraMode(false);

	m_1TimeRender = MakeRender<SingleActorRender>(18);
	m_1TimeRender->SetSprite(L"TimeNumber.bmp", 0);
	m_1TimeRender->Size({ 32, 24 });
	m_1TimeRender->Pivot({ 10, -9 });
	m_1TimeRender->CameraMode(false);

	m_2TimeRender = MakeRender<SingleActorRender>(18);
	m_2TimeRender->SetSprite(L"SingleTimeNum.bmp", 0);
	m_2TimeRender->Size({ 32, 24 });
	m_2TimeRender->Pivot({ 50, -9 });
	m_2TimeRender->CameraMode(false);

	m_3TimeRender = MakeRender<SingleActorRender>(18);
	m_3TimeRender->SetSprite(L"SingleTimeNum.bmp", 0);
	m_3TimeRender->Size({ 32, 24 });
	m_3TimeRender->Pivot({ 68, -9 });
	m_3TimeRender->CameraMode(false);

	m_ColonRender = MakeRender<SingleActorRender>(18);
	m_ColonRender->SetSprite(L"Colon.bmp");
	m_ColonRender->Size({ 32, 24 });
	m_ColonRender->Pivot({ 35, -9 });
	m_ColonRender->CameraMode(false);

	m_NightRender = MakeRender<SingleActorRender>(16);
	m_NightRender->SetSprite(L"Night.bmp");
	m_NightRender->Size({ WINSIZEX, WINSIZEY });
	m_NightRender->Pivot({ -910 + WINSIZEXH , -120 + WINSIZEYH });
	m_NightRender->SetAlpha(100);
	m_NightRender->CameraMode(false);
	m_NightRender->Off();

}

void ClockNumber::PrevUpdate()
{
}

void ClockNumber::Update()
{
	if (true == MinTimer.TimeCheck(TimeBoost))
	{
		++MinCheck;
		if (6 <= MinCheck)
		{
			MinCheck = 0;

			++HourCheck;
			if (3 == HourCheck)
			{
				ClockNum = 1;
				m_NightRender->SetAlpha(80);
			}
			if (7 == HourCheck)
			{
				ClockNum = 2;
				m_NightRender->Off();
			}
			if (11 == HourCheck)
			{
				ClockNum = 3;
			}
			if (12 == HourCheck)
			{
				ClockNumber::EggCheck = true;
				ClockNumber::DEggCheck = true;
			}			
			if (13 == HourCheck)
			{
				ClockNumber::EggCheck = false;
				ClockNumber::DEggCheck = false;
			}
			if (15 == HourCheck)
			{
				ClockNum = 4;
				m_NightRender->On();
			}
			if (19 == HourCheck)
			{
				ClockNum = 5;
				m_NightRender->SetAlpha(200);
			}
			if (22 == HourCheck)
			{
				ClockNumber::BabyCheck = true;
				ClockNumber::DBabyCheck = true;
			}
			if (23 == HourCheck)
			{
				ClockNumber::BabyCheck = false;
				ClockNumber::DBabyCheck = false;
			}
			if (24 <= HourCheck)
			{
				HourCheck = 0;
				ClockNum = 0;

				++DayCheck;
				if (7 <= DayCheck)
				{
					DayCheck = 0;
				}
				m_DayRender->SetSprite(L"Day.bmp", DayCheck);

				++DayNumCheck;
				if (29 <= DayNumCheck)
				{
					DayNumCheck = 0;
				}
				m_DayNumRender->SetSprite(L"TimeNumber.bmp", DayNumCheck);
			}
			m_1TimeRender->SetSprite(L"TimeNumber.bmp", HourCheck);
		}
		m_2TimeRender->SetSprite(L"SingleTimeNum.bmp", MinCheck);
		MinTimer.TimeReset();
	}
	Clock::m_ClockRender->SetSprite(L"Clock.bmp", ClockNum);
}

void ClockNumber::LaterUpdate()
{
}

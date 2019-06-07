#pragma once
class TimeHelper
{
private:
	float m_Time;
	float m_CurTime;

public:
	TimeHelper(float _Time);
	~TimeHelper();

public:
	//내가 넣은 시간이 지나면 트루 리턴해주는 함수.
	bool TimeCheck(float _Scale = 1.0f);
	void TimeReset();
};


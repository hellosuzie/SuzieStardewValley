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
	//���� ���� �ð��� ������ Ʈ�� �������ִ� �Լ�.
	bool TimeCheck(float _Scale = 1.0f);
	void TimeReset();
};


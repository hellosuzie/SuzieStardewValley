#pragma once
#include "ActorBase.h"

class SingleActorRender;
class HPBar :
	public ActorBase
{
private:
	SingleActorRender* m_BarBack;
	SingleActorRender* m_EnergyBar;
	SingleActorRender* m_BarBackGround;

	int m_MaxValue;
	int ResetY;
	static int Temp;

public:
	HPBar(int _MaxValue);
	~HPBar();

public:
	int PosTest()
	{
		return (int)((float)(m_MaxValue - ResetY) * 0.5);
	}
	SingleActorRender* EnergyBarRender()
	{
		return m_EnergyBar;
	}

public:
	void Init() override;
	bool HpUpdate(int _Value);
	void Reduce(int _Value);
};


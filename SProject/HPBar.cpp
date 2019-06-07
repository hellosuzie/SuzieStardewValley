#include "stdafx.h"
#include "HPBar.h"
#include "SingleActorRender.h"

int HPBar::Temp = 0;

HPBar::HPBar(int _MaxValue) : m_MaxValue(_MaxValue)
{
}

HPBar::~HPBar()
{
}

void HPBar::Init()
{
	m_BarBackGround = MakeRender<SingleActorRender>(17);
	m_BarBackGround->SetSprite(L"BarBack.bmp");
	m_BarBackGround->Size({ HPX, HPY });
	m_BarBackGround->Pivot({ WINSIZEX - 22, WINSIZEY - 72 });
	m_BarBackGround->CameraMode(false);

	m_BarBack = MakeRender<SingleActorRender>(17);
	m_BarBack->SetSprite(L"Bar.bmp");
	m_BarBack->Size({ 37, 175 });
	m_BarBack->Pivot({ WINSIZEX - 22, WINSIZEY - 90 });
	m_BarBack->CameraMode(false);

	m_EnergyBar = MakeRender<SingleActorRender>(17);
	m_EnergyBar->SetSprite(L"EBar.bmp");
	m_EnergyBar->Size({ HPX, HPY });
	m_EnergyBar->Pivot({ WINSIZEX - 22, WINSIZEY - 72});
	m_EnergyBar->CameraMode(false);
}

bool HPBar::HpUpdate(int _Value)
{
	ResetY = HPY * _Value / m_MaxValue;
	if (Temp == ResetY)
	{
		return false;
	}
	Temp = ResetY;
	m_EnergyBar->Size({ HPX, ResetY });
	return true;
}

void HPBar::Reduce(int _Value)
{
	m_EnergyBar->Pivot({ WINSIZEX - 22, WINSIZEY -108 + _Value });
}

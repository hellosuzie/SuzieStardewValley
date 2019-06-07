#include "stdafx.h"
#include "QuickInButton.h"
#include "SingleActorRender.h"
#include "ButtonMgr.h"
#include "Player.h"

QuickInButton* QuickInButton::m_SelectButton = nullptr;
int QuickInButton::m_QCount = 0;

void _stdcall SelectQuickInven(void* _Data)
{
	QuickInButton* TempButton = (QuickInButton*)_Data;
	IPOS Test[12];
	int Num = 0;
	int Count = 0;

	for (int j = 2; j < 14; ++j)
	{
		Test[Num] = { j, 11 };
		++Num;
	}

	if (nullptr == QuickInButton::m_SelectButton)
	{
		//첫번째로 눌려진 버튼을 FirstSelect에 넣는다.
		QuickInButton::m_SelectButton = TempButton;

		for (int k = 0; k < 12; ++k)
		{
			if (Test[k] == QuickInButton::m_SelectButton->DefaultIndex())
			{
				QuickInButton::m_QCount = Count;
			}
			else
			{
				++Count;
			}
		}
		return;
	}
	QuickInButton::m_SelectButton = nullptr;
}

QuickInButton::QuickInButton()
{
}


QuickInButton::~QuickInButton()
{
}

void QuickInButton::Init()
{
	m_QuickInRender = MakeRender<SingleActorRender>(100);
	m_QuickInRender->SetSprite(L"Select.bmp", 1);
	m_QuickInRender->CameraMode(false);

	m_QuickInButton = Parent()->MakeActor<ButtonMgr>();
	m_QuickInButton->CameraMode(false);
}

void QuickInButton::ButtonInit()
{
	m_QuickInButton->SetData(this);
	m_QuickInButton->SetDownStayFunc(SelectQuickInven);
	m_DefaultIndex = Player::WorldPlayerIndex(Pos());
}

void QuickInButton::PrevUpdate()
{
}

void QuickInButton::Update()
{
}

void QuickInButton::LaterUpdate()
{
}

void QuickInButton::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void QuickInButton::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
}

void QuickInButton::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

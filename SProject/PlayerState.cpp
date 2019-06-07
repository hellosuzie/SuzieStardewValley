#include "stdafx.h"
#include "Player.h"
#include "EnterMgr.h"
#include "AniActorRender.h"
#include "EnterMgr.h"
#include "HandItem.h"
#include "SoundPlayer.h"

void Player::StateUpdate()
{
	switch (m_PlayerState)
	{
	case Player::STAY:
		Stay();
		break;
	case Player::PICK:
		Pick();
		break;
	case Player::WALK:
		Walk();
		break;
	case Player::PICKWALK:
		Pickwalk();
		break;
	case Player::EAT:
		Eat();
		break;
	case Player::TOOL:
		Tool();
		break;
	case Player::WEAPON:
		Weapon();
		break;
	case Player::WATER:
		Water();
		break;
	case Player::RIDE:
		Ride();
		break;
	default:
		break;
	}
}

//������Ʈ �ٲٸ� �ִϸ��̼� �ٲ��ִ� �Լ�
void Player::ChangePlayerAni(PLAYERSTATE _State)
{
	std::wstring ChangeAniName = m_PlayerDir + m_PlayerAniName[_State];
	m_MainPlayerRender->ChangeAni(ChangeAniName.c_str());
}

void Player::ChangePlayerAni(PLAYERSTATE _State, PLAYERTOOL _Tool)
{
	std::wstring ChangeAniName = m_PlayerDir + m_PlayerAniName[_State];
	m_MainPlayerRender->ChangeAni(ChangeAniName.c_str());

	if (m_PlayerItem != PLAYERTOOL::NONE && _Tool != PLAYERTOOL::NONE)
	{
		m_MainItemRender->On();
		std::wstring ChangeItemName = m_PlayerDir + m_ItemAniName[_Tool];
		m_MainItemRender->ChangeAni(ChangeItemName.c_str());
	}
	else if (m_PlayerItem == PLAYERTOOL::NONE || _Tool == PLAYERTOOL::NONE)
	{
		m_MainItemRender->Off();
	}
}

//������Ʈ �ٲٴ� �Լ�
void Player::ChangeState(PLAYERSTATE _State)
{
	m_PlayerState = _State;
}

//������ ������Ʈ�� ���� �ٲٴ� �Լ�.
void Player::ChangeState(PLAYERSTATE _State, PLAYERTOOL _Tool)
{
	m_PlayerState = _State;
	if (_Tool != PLAYERTOOL::NONE)
	{
		m_PlayerItem = _Tool;
	}
}

void Player::DirCheck()
{
	std::wstring CheckDir = m_PlayerDir;

	if (true == KEYDOWNSTAY("LEFT"))
	{
		CheckDir = L"Left";
	}
	if (true == KEYDOWNSTAY("RIGHT"))
	{
		CheckDir = L"Right";
	}
	if (true == KEYDOWNSTAY("UP"))
	{
		CheckDir = L"Up";
	}
	if (true == KEYDOWNSTAY("DOWN"))
	{
		CheckDir = L"Down";
	}
	if (CheckDir != m_PlayerDir)
	{
		std::wstring ChangeAniName = CheckDir + m_PlayerAniName[m_PlayerState];
		m_MainPlayerRender->ChangeAni(ChangeAniName.c_str());
		m_PlayerDir = CheckDir;

		if (m_PlayerItem != PLAYERTOOL::NONE)
		{
			std::wstring ChangeItemName = CheckDir + m_ItemAniName[m_PlayerItem];
			m_MainItemRender->ChangeAni(ChangeItemName.c_str());
		}
	}
	
	if (L"Down" == CheckDir)
	{
		m_MainItemRender->Pivot({ 0, 0.1f });
	}
	if (L"Up" == CheckDir)
	{
		m_MainItemRender->Pivot({ 0, -0.1f });
	}
}

void Player::Stay()
{
	if (true == KEYDOWNSTAY("DOWN") 
		|| true == KEYDOWNSTAY("UP") 
		|| true == KEYDOWNSTAY("LEFT") 
		|| true == KEYDOWNSTAY("RIGHT") 
		|| true == KEYDOWN("DOWN") 
		|| true == KEYDOWN("UP") 
		|| true == KEYDOWN("LEFT") 
		|| true == KEYDOWN("RIGHT"))
	{
		if (nullptr != m_MainHandItem->PlayerHandItem())
		{
			ChangeState(PLAYERSTATE::PICKWALK);
			ChangePlayerAni(PLAYERSTATE::PICKWALK);
		}
		else
		{
			ChangeState(PLAYERSTATE::WALK);
			ChangePlayerAni(PLAYERSTATE::WALK);
		}
	}

	//�÷��̾ � �������� ����ٸ� pick������Ʈ�� ����

	//�÷��̾ � ������ ����ٸ� ������ ������Ʈ�� �ִϸ��̼� �ٲ������
	//� ������ Ŭ���ߴٸ� ������Ʈ�� �ٲ�� �ִϸ��̼��� ���������� �ٲ��

	//���� Ű�� ���Ҷ� ������Ʈ ü���� ���ϱ� - � ������ ������ �ٸ� Ű�� ���������� ������Ʈ ��� �����ϱ�

	//���� Ű�� ������ �� ������ ������Ʈ�� ���� ������Ʈ�� �ٲ��.
	if (true == KEYDOWN("Action"))
	{
		switch (m_PlayerItem)
		{
		case Player::NONE:
			ChangeState(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
			ChangePlayerAni(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
			break;
		case Player::AXE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::AXE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::AXE);
			break;
		case Player::HOE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
			break;
		case Player::PICKAXE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::PICKAXE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::PICKAXE);
			break;
		case Player::SICKLE:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::SICKLE);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::SICKLE);
			break;
		case Player::WATERCAN:
			ChangeState(PLAYERSTATE::WATER, PLAYERTOOL::WATERCAN);
			ChangePlayerAni(PLAYERSTATE::WATER, PLAYERTOOL::WATERCAN);
			break;
		case Player::RUSTYSWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::RUSTYSWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::RUSTYSWORD);
			break;
		case Player::RAPIER:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::RAPIER);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::RAPIER);
			break;
		case Player::PIRATESWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::PIRATESWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::PIRATESWORD);
			break;
		case Player::GALAXYSWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::GALAXYSWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::GALAXYSWORD);
			break;
		case Player::CLAYMORE:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::CLAYMORE);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::CLAYMORE);
			break;
		default:
			break;
		}
	}
}

void Player::Pick()
{
	if (true == KEYDOWNSTAY("DOWN")
		|| true == KEYDOWNSTAY("UP")
		|| true == KEYDOWNSTAY("LEFT")
		|| true == KEYDOWNSTAY("RIGHT")
		|| true == KEYDOWN("DOWN")
		|| true == KEYDOWN("UP")
		|| true == KEYDOWN("LEFT")
		|| true == KEYDOWN("RIGHT"))
	{
		if (nullptr != m_MainHandItem->PlayerHandItem())
		{
			ChangeState(PLAYERSTATE::PICKWALK, PLAYERTOOL::NONE);
			ChangePlayerAni(PLAYERSTATE::PICKWALK, PLAYERTOOL::NONE);
		}
		else
		{
			ChangeState(PLAYERSTATE::WALK, PLAYERTOOL::NONE);
			ChangePlayerAni(PLAYERSTATE::WALK, PLAYERTOOL::NONE);
		}
	}
	if (true == KEYDOWN("Action"))
	{
		if (nullptr != MainHandItem()->PlayerHandItem())
		{
			if (true == MainHandItem()->PlayerHandItem()->m_Eat)
			{
				ChangeState(PLAYERSTATE::EAT, PLAYERTOOL::NONE);
				ChangePlayerAni(PLAYERSTATE::EAT);
			}
		}
	}
}

void Player::Walk()
{
	if (false == KEYDOWNSTAY("DOWN") 
		&& false == KEYDOWNSTAY("UP") 
		&& false == KEYDOWNSTAY("LEFT") 
		&& false == KEYDOWNSTAY("RIGHT"))
	{
		ChangeState(PLAYERSTATE::STAY);
		ChangePlayerAni(PLAYERSTATE::STAY);
	}

	if (true == KEYDOWN("Action"))
	{
		switch (m_PlayerItem)
		{
		case Player::NONE:
			ChangeState(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
			ChangePlayerAni(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
			break;
		case Player::AXE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::AXE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::AXE);
			break;
		case Player::HOE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
			break;
		case Player::PICKAXE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::PICKAXE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::PICKAXE);
			break;
		case Player::SICKLE:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::SICKLE);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::SICKLE);
			break;
		case Player::WATERCAN:
			ChangeState(PLAYERSTATE::WATER, PLAYERTOOL::WATERCAN);
			ChangePlayerAni(PLAYERSTATE::WATER, PLAYERTOOL::WATERCAN);
			break;
		case Player::RUSTYSWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::RUSTYSWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::RUSTYSWORD);
			break;
		case Player::RAPIER:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::RAPIER);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::RAPIER);
			break;
		case Player::PIRATESWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::PIRATESWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::PIRATESWORD);
			break;
		case Player::GALAXYSWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::GALAXYSWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::GALAXYSWORD);
			break;
		case Player::CLAYMORE:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::CLAYMORE);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::CLAYMORE);
			break;
		default:
			break;
		}
	}
}

void Player::Pickwalk()
{
	if (false == KEYDOWNSTAY("DOWN")
		&& false == KEYDOWNSTAY("UP")
		&& false == KEYDOWNSTAY("LEFT")
		&& false == KEYDOWNSTAY("RIGHT"))
	{
		if (nullptr != m_MainHandItem->PlayerHandItem())
		{
			ChangeState(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
			ChangePlayerAni(PLAYERSTATE::PICK, PLAYERTOOL::NONE);
		}
		else
		{
			ChangeState(PLAYERSTATE::STAY);
			ChangePlayerAni(PLAYERSTATE::STAY);
		}
	}
}

//������ 100�϶� ���ĸԴ� ��� ���ȳ����� �ϱ�
void Player::Eat()
{
	if (true == m_MainPlayerRender->AniEndCheck())
	{
		ChangePlayerAni(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
	}
	if (true == KEYDOWNSTAY("DOWN")
		|| true == KEYDOWNSTAY("UP")
		|| true == KEYDOWNSTAY("LEFT")
		|| true == KEYDOWNSTAY("RIGHT")
		|| true == KEYDOWN("DOWN")
		|| true == KEYDOWN("UP")
		|| true == KEYDOWN("LEFT")
		|| true == KEYDOWN("RIGHT"))
	{
		ChangeState(PLAYERSTATE::WALK, PLAYERTOOL::NONE);
		ChangePlayerAni(PLAYERSTATE::WALK, PLAYERTOOL::NONE);
	}
	if (true == KEYDOWN("Action"))
	{
		if (nullptr != MainHandItem()->PlayerHandItem())
		{
			if (true == MainHandItem()->PlayerHandItem()->m_Eat)
			{
				ChangeState(PLAYERSTATE::EAT, PLAYERTOOL::NONE);
				ChangePlayerAni(PLAYERSTATE::EAT);
			}
		}
	}
}
void Player::Tool()
{
	if (true == m_MainPlayerRender->AniEndCheck())
	{
		ChangePlayerAni(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
	}
	if (true == KEYDOWNSTAY("DOWN")
		|| true == KEYDOWNSTAY("UP")
		|| true == KEYDOWNSTAY("LEFT")
		|| true == KEYDOWNSTAY("RIGHT")
		|| true == KEYDOWN("DOWN")
		|| true == KEYDOWN("UP")
		|| true == KEYDOWN("LEFT")
		|| true == KEYDOWN("RIGHT"))
	{
		ChangeState(PLAYERSTATE::WALK, PLAYERTOOL::NONE);
		ChangePlayerAni(PLAYERSTATE::WALK, PLAYERTOOL::NONE);
	}
	if (true == KEYDOWN("Action"))
	{
		switch (m_PlayerItem)
		{
		case Player::NONE:
			ChangeState(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
			ChangePlayerAni(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
			break;
		case Player::AXE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::AXE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::AXE);
			break;
		case Player::HOE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
			break;
		case Player::PICKAXE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::PICKAXE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::PICKAXE);
			break;
		case Player::SICKLE:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::SICKLE);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::SICKLE);
			break;
		case Player::WATERCAN:
			ChangeState(PLAYERSTATE::WATER, PLAYERTOOL::WATERCAN);
			ChangePlayerAni(PLAYERSTATE::WATER, PLAYERTOOL::WATERCAN);
			break;
		case Player::RUSTYSWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::RUSTYSWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::RUSTYSWORD);
			break;
		case Player::RAPIER:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::RAPIER);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::RAPIER);
			break;
		case Player::PIRATESWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::PIRATESWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::PIRATESWORD);
			break;
		case Player::GALAXYSWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::GALAXYSWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::GALAXYSWORD);
			break;
		case Player::CLAYMORE:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::CLAYMORE);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::CLAYMORE);
			break;
		default:
			break;
		}
	}
}
void Player::Weapon()
{
	if (true == m_MainPlayerRender->AniEndCheck())
	{
		ChangePlayerAni(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
	}
	if (true == KEYDOWNSTAY("DOWN")
		|| true == KEYDOWNSTAY("UP")
		|| true == KEYDOWNSTAY("LEFT")
		|| true == KEYDOWNSTAY("RIGHT")
		|| true == KEYDOWN("DOWN")
		|| true == KEYDOWN("UP")
		|| true == KEYDOWN("LEFT")
		|| true == KEYDOWN("RIGHT"))
	{
		ChangeState(PLAYERSTATE::WALK, PLAYERTOOL::NONE);
		ChangePlayerAni(PLAYERSTATE::WALK, PLAYERTOOL::NONE);
	}
	if (true == KEYDOWN("Action"))
	{
		switch (m_PlayerItem)
		{
		case Player::NONE:
			ChangeState(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
			ChangePlayerAni(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
			break;
		case Player::AXE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::AXE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::AXE);
			break;
		case Player::HOE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
			break;
		case Player::PICKAXE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::PICKAXE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::PICKAXE);
			break;
		case Player::SICKLE:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::SICKLE);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::SICKLE);
			break;
		case Player::WATERCAN:
			ChangeState(PLAYERSTATE::WATER, PLAYERTOOL::WATERCAN);
			ChangePlayerAni(PLAYERSTATE::WATER, PLAYERTOOL::WATERCAN);
			break;
		case Player::RUSTYSWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::RUSTYSWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::RUSTYSWORD);
			break;
		case Player::RAPIER:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::RAPIER);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::RAPIER);
			break;
		case Player::PIRATESWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::PIRATESWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::PIRATESWORD);
			break;
		case Player::GALAXYSWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::GALAXYSWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::GALAXYSWORD);
			break;
		case Player::CLAYMORE:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::CLAYMORE);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::CLAYMORE);
			break;
		default:
			break;
		}
	}
}
void Player::Water()
{
	if (true == m_MainPlayerRender->AniEndCheck())
	{
		ChangePlayerAni(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
	}
	if (true == KEYDOWNSTAY("DOWN")
		|| true == KEYDOWNSTAY("UP")
		|| true == KEYDOWNSTAY("LEFT")
		|| true == KEYDOWNSTAY("RIGHT")
		|| true == KEYDOWN("DOWN")
		|| true == KEYDOWN("UP")
		|| true == KEYDOWN("LEFT")
		|| true == KEYDOWN("RIGHT"))
	{
		ChangeState(PLAYERSTATE::WALK, PLAYERTOOL::NONE);
		ChangePlayerAni(PLAYERSTATE::WALK, PLAYERTOOL::NONE);
	}
	if (true == KEYDOWN("Action"))
	{
		switch (m_PlayerItem)
		{
		case Player::NONE:
			ChangeState(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
			ChangePlayerAni(PLAYERSTATE::STAY, PLAYERTOOL::NONE);
			break;
		case Player::AXE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::AXE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::AXE);
			break;
		case Player::HOE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::HOE);
			break;
		case Player::PICKAXE:
			ChangeState(PLAYERSTATE::TOOL, PLAYERTOOL::PICKAXE);
			ChangePlayerAni(PLAYERSTATE::TOOL, PLAYERTOOL::PICKAXE);
			break;
		case Player::SICKLE:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::SICKLE);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::SICKLE);
			break;
		case Player::WATERCAN:
			ChangeState(PLAYERSTATE::WATER, PLAYERTOOL::WATERCAN);
			ChangePlayerAni(PLAYERSTATE::WATER, PLAYERTOOL::WATERCAN);
			break;
		case Player::RUSTYSWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::RUSTYSWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::RUSTYSWORD);
			break;
		case Player::RAPIER:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::RAPIER);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::RAPIER);
			break;
		case Player::PIRATESWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::PIRATESWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::PIRATESWORD);
			break;
		case Player::GALAXYSWORD:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::GALAXYSWORD);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::GALAXYSWORD);
			break;
		case Player::CLAYMORE:
			ChangeState(PLAYERSTATE::WEAPON, PLAYERTOOL::CLAYMORE);
			ChangePlayerAni(PLAYERSTATE::WEAPON, PLAYERTOOL::CLAYMORE);
			break;
		default:
			break;
		}
	}
}
void Player::Ride()
{

}
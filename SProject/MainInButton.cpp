#include "stdafx.h"
#include "MainInButton.h"
#include "SingleActorRender.h"
#include "ButtonMgr.h"
#include "EnterMgr.h"
#include "Player.h"
#include "InfoRender.h"
#include <stdio.h>
#include <stdlib.h>

MainInButton* MainInButton::m_FirstSelect = nullptr;
MainInButton* MainInButton::m_SecondSelect = nullptr;
int MainInButton::m_InvenCount = 0;
int MainInButton::m_ChangeInvenCount = 0;
InfoRender* MainInButton::m_InfoRender = nullptr;

ItemMgr::ItemInfo* MainInButton::m_TestItemInfo = nullptr;
int MainInButton::m_TestCount = 0;

IPOS MainInButton::m_MIndex = {};
int MainInButton::m_MCount = 0;

void _stdcall SelectInven(void* _Data)
{
	MainInButton* TempButton = (MainInButton*)_Data;
	IPOS Test[36];
	int Num = 0;
	int Count = 0;

	for (int i = 8; i < 11; ++i)
	{
		for (int j = 2; j < 14; ++j)
		{
			Test[Num] = { j, i };
			++Num;
		}
	}

	//ù��° ��ư�� null�� �ƴϰ�, �ι�° ���� tempbutton�� ù��° ��ư�� ���� ������
	if (nullptr != MainInButton::m_FirstSelect && TempButton != MainInButton::m_FirstSelect)
	{
		MainInButton::m_SecondSelect = TempButton;

		for (int k = 0; k < 36; ++k)
		{
			if (Test[k] == MainInButton::m_SecondSelect->DefaultIndex())
			{
				MainInButton::m_ChangeInvenCount = Count;
			}
			else
			{
				++Count;
			}
		}
		return;
	}
	//ù��° ������ ��ư�� ����, ���� ���� ��ư�� ù��° ������ ��ư�� ������
	if (nullptr == MainInButton::m_FirstSelect || TempButton == MainInButton::m_FirstSelect)
	{
		//ù��°�� ������ ��ư�� FirstSelect�� �ִ´�.
		MainInButton::m_FirstSelect = TempButton;

		for (int k = 0; k < 36; ++k)
		{
			if (Test[k] == MainInButton::m_FirstSelect->DefaultIndex())
			{
				MainInButton::m_InvenCount = Count;
			}
			else
			{
				++Count;
			}
		}
		return;
	}
}

void _stdcall CrashInven(void* _Data)
{
	MainInButton* TempButton = (MainInButton*)_Data;

	//�ٸ� ��ư�� �浹���� �ʾҴٸ�
	if (TempButton == MainInButton::m_FirstSelect && nullptr == MainInButton::m_SecondSelect)
	{
		//�ٽ� ���� �ڸ��� ���ư�
		MainInButton::m_FirstSelect->ResetIndex();
		MainInButton::m_FirstSelect = nullptr;
	}
	else if (TempButton == MainInButton::m_FirstSelect && nullptr != MainInButton::m_SecondSelect)
	{
		MainInButton::m_FirstSelect->ResetIndex();

		IPOS StartIndex = Player::WorldPlayerIndex(MainInButton::m_FirstSelect->Pos());
		IPOS NextIndex = Player::WorldPlayerIndex(MainInButton::m_SecondSelect->Pos());

		//�ڸ� �ٲ��ֱ�
		MainInButton::m_FirstSelect->Pos(Player::IndexWorldPos(NextIndex));
		MainInButton::m_FirstSelect->MainInvenButton()->Pos(Player::IndexWorldPos(NextIndex));
		MainInButton::m_FirstSelect->ResetIndex(NextIndex);
		MainInButton::m_FirstSelect = nullptr;

		MainInButton::m_SecondSelect->Pos(Player::IndexWorldPos(StartIndex));
		MainInButton::m_SecondSelect->MainInvenButton()->Pos(Player::IndexWorldPos(StartIndex));
		MainInButton::m_SecondSelect->ResetIndex(StartIndex);
		MainInButton::m_SecondSelect = nullptr;

		Player::InvenSwapCheck();
	}
}

void _stdcall EnterInven(void* _Data)
{
	IPOS Test[36];
	int Num = 0;
	int Count = 0;

	for (int i = 8; i < 11; ++i)
	{
		for (int j = 2; j < 14; ++j)
		{
			Test[Num] = { j, i };
			++Num;
		}
	}

	for (int k = 0; k < 36; ++k)
	{
		if (Test[k] == MainInButton::m_MIndex)
		{
			MainInButton::m_MCount = Count;
		}
		else
		{
			++Count;
		}
	}

	MainInButton::m_InfoRender->On();

	if (nullptr == Player::CurPlayer->ReturnItemInfo(MainInButton::m_MCount))
	{
		MainInButton::m_InfoRender->Off();
		return;
	}

	int TempType = Player::CurPlayer->ReturnItemInfo(MainInButton::m_MCount)->m_ItemType;
	char TypeNum[256];

	_itoa_s(TempType, TypeNum, 10);
	std::string Name = TypeNum;
	std::wstring WName;
	WName.assign(Name.begin(), Name.end());

	std::wstring TempName = WName;
	std::wstring Bmp = L".bmp";
	TempName += Bmp;

	MainInButton::m_InfoRender->ItemInfoRender()->SetSprite(TempName.c_str(), Player::CurPlayer->ReturnItemInfo(MainInButton::m_MCount)->m_ItemCount);
}

void _stdcall ExitInven(void* _Data)
{
	MainInButton::m_InfoRender->Off();
}

MainInButton::MainInButton() : m_MainItemInfo(nullptr)
{
}

MainInButton::~MainInButton()
{
}

void MainInButton::Init()
{	
	m_MainInRender = MakeRender<SingleActorRender>(100);
	m_MainInRender->SetSprite(L"Select.bmp", 1);
	m_MainInRender->CameraMode(false);
}

void MainInButton::ButtonInit()
{
	m_MainInButton->SetData(this);
	m_MainInButton->SetDownStayFunc(SelectInven);
	m_MainInButton->SetUpFunc(CrashInven);
	m_MainInButton->SetEnterFunc(EnterInven);
	m_MainInButton->SetExitFunc(ExitInven);
	m_DefaultIndex = Player::WorldPlayerIndex(Pos());
}

void MainInButton::PrevUpdate()
{
}

void MainInButton::Update()
{
	if (this == m_FirstSelect)
	{
		//������
		Pos(MOUSEF);
		//��ư
		m_MainInButton->Pos(Pos());
	}

	m_MIndex = Player::WorldPlayerIndex(MOUSEF);
}

void MainInButton::LaterUpdate()
{
}

void MainInButton::ResetIndex()
{
	//������
	Pos(Player::IndexWorldPos(m_DefaultIndex));
	//��ư
	m_MainInButton->Pos(Player::IndexWorldPos(m_DefaultIndex));
}

void MainInButton::ResetIndex(IPOS _Index)
{
	m_DefaultIndex = _Index;
}

bool MainInButton::SetItemInfo(ItemMgr::ItemInfo* _Info)
{
	m_MainItemInfo = _Info;
	if (nullptr == _Info || -1 == _Info->m_ItemCount)
	{
		m_MainInRender->SetSprite(L"Select.bmp", 1);
		return false;
	}
	else
	{
		m_MainInRender->SetSprite(_Info->m_SpriteName.c_str(), _Info->m_SpriteNum);
		return true;
	}
	return false;
}
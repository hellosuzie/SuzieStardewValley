#pragma once
#include "ActorBase.h"
#include "ItemMgr.h"

class InfoRender;
class ButtonMgr;
class SingleActorRender;
class MainInButton :
	public ActorBase
{
public:
	static MainInButton* m_FirstSelect;
	static MainInButton* m_SecondSelect;
	static int m_InvenCount;
	static int m_ChangeInvenCount;

	static IPOS Test[36];
	static int m_Num;
	static int m_Count;

public:
	ButtonMgr* m_MainInButton;

private:
	SingleActorRender* m_MainInRender;
	ItemMgr::ItemInfo* m_MainItemInfo;

	FPOS m_DefaultPos;
	IPOS m_DefaultIndex;

public:
	static IPOS m_MIndex;
	static int m_MCount;

public:
	static InfoRender* m_InfoRender;
	static ItemMgr::ItemInfo* m_TestItemInfo;
	static int m_TestCount;

public:
	MainInButton();
	~MainInButton();

public:
	MainInButton& operator = (const MainInButton& _Button)
	{
		m_MainInRender = _Button.m_MainInRender;
		m_MainItemInfo = _Button.m_MainItemInfo;
		m_DefaultPos = _Button.m_DefaultPos;
		m_DefaultIndex = _Button.m_DefaultIndex;
		m_MainInButton = _Button.m_MainInButton;
	}

public:
	void MainItemInfo(ItemMgr::ItemInfo* _ItemInfo)
	{
		m_MainItemInfo = _ItemInfo;
	}
	ItemMgr::ItemInfo* MainItemInfo()
	{
		return m_MainItemInfo;
	}
	IPOS DefaultIndex()
	{
		return m_DefaultIndex;
	}
	ButtonMgr* MainInvenButton()
	{
		return m_MainInButton;
	}
	SingleActorRender* MainInvenRender()
	{
		return m_MainInRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

public:
	void ButtonInit();

	void ResetIndex();
	void ResetIndex(IPOS _Index);

	bool SetItemInfo(ItemMgr::ItemInfo* _Info);

};


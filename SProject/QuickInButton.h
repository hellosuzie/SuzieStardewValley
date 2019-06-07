#pragma once
#include "ActorBase.h"
#include "ItemMgr.h"

class SingleActorRender;
class ButtonMgr;
class QuickInButton :
	public ActorBase
{
public:
	static QuickInButton* m_SelectButton;
	static int m_QCount;

public:
	ButtonMgr* m_QuickInButton;

private:
	SingleActorRender* m_QuickInRender;
	IPOS m_DefaultIndex;

public:
	QuickInButton();
	~QuickInButton();

public:
	QuickInButton& operator = (const QuickInButton& _Button)
	{
		m_QuickInRender = _Button.m_QuickInRender;
		m_DefaultIndex = _Button.m_DefaultIndex;
		m_QuickInButton = _Button.m_QuickInButton;
	}

public:
	SingleActorRender* QuickInRender()
	{
		return m_QuickInRender;
	}
	ButtonMgr* QuickInvenButton()
	{
		return m_QuickInButton;
	}
	IPOS DefaultIndex()
	{
		return m_DefaultIndex;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

	void ButtonInit();

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


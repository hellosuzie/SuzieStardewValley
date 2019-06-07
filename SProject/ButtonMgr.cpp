#include "stdafx.h"
#include "ButtonMgr.h"
#include "SingleActorRender.h"
#include "ResourceMgr.h"
#include "EnterMgr.h"
#include "ActorCollision.h"

ButtonMgr::ButtonMgr() : m_ClickCheck(false), m_Data(nullptr)
{
}


ButtonMgr::~ButtonMgr()
{
}

void ButtonMgr::Init()
{
}

void ButtonMgr::ButtonInit(const WCHAR * _CollName, const WCHAR * _ButtonName, FPOS _Pos, FSIZE _Size)
{
	m_Pos = _Pos;
	m_ButtonName = _ButtonName;
	
	m_ButtonColl = MakeCollision(_CollName, _Size);
	m_ButtonBack = MakeRender<SingleActorRender>(1000);
	m_ButtonBack->SetSprite(m_BaseImage.m_BName.c_str(), m_BaseImage.m_SpriteIndex);
	m_ButtonBack->Size(_Size);
	m_ButtonSize = m_ButtonBack->Size();
	m_ButtonBack->CameraMode(false);
}

void ButtonMgr::CollButtonInit(const WCHAR * _CollName, const WCHAR * _ButtonName, FPOS _Pos, FSIZE _Size)
{
	m_Pos = _Pos;
	m_ButtonName = _ButtonName;
	m_ButtonColl = MakeCollision(_CollName, _Size);
}

void ButtonMgr::SetBaseImage(const WCHAR * _SpriteName, int _SpriteIndex)
{
	if (nullptr != _SpriteName)
	{
		m_BaseImage.m_BName = _SpriteName;
		m_BaseImage.m_SpriteIndex = _SpriteIndex;
	}
}

void ButtonMgr::SetEnterImage(const WCHAR * _SpriteName, int _SpriteIndex)
{
	if (nullptr != _SpriteName)
	{
		m_EnterImage.m_BName = _SpriteName;
		m_EnterImage.m_SpriteIndex = _SpriteIndex;
	}
}

void ButtonMgr::SetClickImage(const WCHAR * _SpriteName, int _SpriteIndex)
{
	if (nullptr != _SpriteName)
	{
		m_ClickImage.m_BName = _SpriteName;
		m_ClickImage.m_SpriteIndex = _SpriteIndex;
	}
}

void ButtonMgr::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
	Enter();
}

void ButtonMgr::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
	if (KEYDOWNL(m_ButtonName.c_str()))
	{
		m_ClickCheck = true;
		Down();
	}
	else if (KEYDOWNSTAYL(m_ButtonName.c_str()))
	{
		m_ClickCheck = true;
		DownStay();
	}
	else if (KEYUPL(m_ButtonName.c_str()))
	{
		m_ClickCheck = false;
		Up();
		Click();
	}
}

void ButtonMgr::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
	Exit();
}

void ButtonMgr::Enter()
{
	if (nullptr != m_ButtonBack)
	{
		m_ButtonBack->SetSprite(m_EnterImage.m_BName.c_str(), m_EnterImage.m_SpriteIndex);
		m_ButtonBack->Size(m_ButtonSize);
	}
	if (nullptr != m_EnterFunc)
	{
		m_EnterFunc(m_Data);
	}
}

void ButtonMgr::Up()
{
	if (nullptr != m_ButtonBack)
	{
		m_ButtonBack->SetSprite(m_EnterImage.m_BName.c_str(), m_EnterImage.m_SpriteIndex);
		m_ButtonBack->Size(m_ButtonSize);
	}
	if (nullptr != m_UpFunc)
	{
		m_UpFunc(m_Data);
	}
}

void ButtonMgr::Click()
{
	if (nullptr != m_ButtonBack)
	{
		m_ButtonBack->SetSprite(m_ClickImage.m_BName.c_str(), m_ClickImage.m_SpriteIndex);
		m_ButtonBack->Size(m_ButtonSize);
	}
	if (nullptr != m_ClickFunc)
	{
		m_ClickFunc(m_Data);
	}
}

void ButtonMgr::Down()
{
	if (nullptr != m_ButtonBack)
	{
		m_ButtonBack->SetSprite(m_ClickImage.m_BName.c_str(), m_ClickImage.m_SpriteIndex);
		m_ButtonBack->Size(m_ButtonSize);
	}
	if (nullptr != m_DownFunc)
	{
		m_DownFunc(m_Data);
	}
}

void ButtonMgr::DownStay()
{
	if (nullptr != m_DownStayFunc)
	{
		m_DownStayFunc(m_Data);
	}
}

void ButtonMgr::Exit()
{
	if (nullptr != m_ButtonBack)
	{
		m_ButtonBack->SetSprite(m_BaseImage.m_BName.c_str(), m_BaseImage.m_SpriteIndex);
		m_ButtonBack->Size(m_ButtonSize);
	}
	if (nullptr != m_ExitFunc)
	{
		m_ExitFunc(m_Data);
	}
}



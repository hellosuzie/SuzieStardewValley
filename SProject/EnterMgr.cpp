#include "stdafx.h"
#include "EnterMgr.h"
#include "TimeMgr.h"

void EnterMgr::KeyData::Update()
{
	//키가 다 눌렸는지 체크
	bool KeyCheck = AllKeyCheck();
	if (true == KeyCheck)
	{
		if (true == m_UpStay)
		{
			m_PushTime += DELTATIME;
			//키가 눌렸다.
			m_Up = false;
			m_UpStay = false;
			m_Down = true;
			m_DownStay = true;
		}
		else if (false == m_UpStay)
		{
			m_PushTime += DELTATIME;
			m_Up = false;
			m_UpStay = false;
			m_Down = false;
			m_DownStay = true;
		}
	}
	else if (false == KeyCheck)
	{
		if (true == m_DownStay)
		{
			m_PushTime = 0.0f;
			//키가 눌렸다.
			m_Up = true;
			m_UpStay = true;
			m_Down = false;
			m_DownStay = false;
		}
		else if (false == m_DownStay)
		{
			m_Up = false;
			m_UpStay = true;
			m_Down = false;
			m_DownStay = false;
		}
	}

}

bool EnterMgr::KeyData::AllKeyCheck()
{
	for (size_t i = 0; i < m_AllKeyVec.size(); i++)
	{
		if (0 == GetAsyncKeyState(m_AllKeyVec[i]))
		{
			return false;
		}
	}

	return true;	
}



EnterMgr::EnterMgr()
{
}

EnterMgr::~EnterMgr()
{
	StartIter = m_KeyMap.begin();
	EndIter = m_KeyMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}
	m_KeyMap.clear();
}

void EnterMgr::Update()
{
	GetCursorPos(&m_MousePos);
	ScreenToClient(SHWND, &m_MousePos);

	StartIter = m_KeyMap.begin();
	EndIter = m_KeyMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			StartIter->second->Update();
		}
	}
}

bool EnterMgr::UpCondition(const WCHAR* _Name)
{
	KeyData* TempData = FindKey(_Name);
	if (nullptr == TempData)
	{
		Tassert(true);
		return false;
	}
	return TempData->m_Up;
}

bool EnterMgr::UpStayCondition(const WCHAR* _Name)
{
	KeyData* TempData = FindKey(_Name);
	if (nullptr == TempData)
	{
		Tassert(true);
		return false;
	}
	return TempData->m_UpStay;
}

bool EnterMgr::DownCondition(const WCHAR* _Name)
{
	KeyData* TempData = FindKey(_Name);
	if (nullptr == TempData)
	{
		Tassert(true);
		return false;
	}
	return TempData->m_Down;
}

bool EnterMgr::DownStayCondition(const WCHAR* _Name)
{
	KeyData* TempData = FindKey(_Name);
	if (nullptr == TempData)
	{
		Tassert(true);
		return false;
	}
	return TempData->m_DownStay;
}

float EnterMgr::PushTime(WCHAR* _Name)
{
	KeyData* TempData = FindKey(_Name);
	if (nullptr == TempData)
	{
		Tassert(true);
		return false;
	}
	return TempData->m_PushTime;
}

bool EnterMgr::PushTimeReset(WCHAR* _Name, float _Time)
{
	KeyData* TempData = FindKey(_Name);
	if (nullptr == TempData)
	{
		Tassert(true);
		return false;
	}
	if (_Time <= TempData->m_PushTime)
	{
		TempData->m_PushTime = 0.0f;
		return true;
	}
	return false;
}


#include "stdafx.h"
#include "CollisionMgr.h"
#include "ActorCollision.h"

CollisionMgr::CollGroup::CollGroup()
{
}

CollisionMgr::CollGroup::~CollGroup()
{

}

void CollisionMgr::CollGroup::Link(CollGroup * _OtherGroup)
{
	m_OtherSIter = m_OtherGroupList.begin();
	m_OtherEIter = m_OtherGroupList.end();

	for (; m_OtherSIter != m_OtherEIter; ++m_OtherSIter)
	{
		//링크 거는 그룹이 중복되면 리턴
		if (*m_OtherSIter == _OtherGroup)
		{
			return;
		}
	}
	if (nullptr == _OtherGroup)
	{
		Tassert(true);
		return;
	}
	m_OtherGroupList.push_back(_OtherGroup);
}

void CollisionMgr::CollGroup::PushCollision(ActorCollision * _Other)
{
	m_CollList.push_back(_Other);
}

void CollisionMgr::CollGroup::CollCheck(CollGroup * _Group)
{
	//내가 나랑 충돌할때
	if (this == _Group)
	{

	}
	else //아닐때
	{
		m_ThisStartIter = m_CollList.begin();
		m_ThisEndIter = m_CollList.end();

		for (; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
		{
			if (false == (*m_ThisStartIter)->UpdateCheck())
			{
				continue;
			}
			m_OtherStartIter = _Group->m_CollList.begin();
			m_OtherEndIter = _Group->m_CollList.end();

			for (; m_OtherStartIter != m_OtherEndIter; ++m_OtherStartIter)
			{
				if (false == (*m_OtherStartIter)->UpdateCheck())
				{
					continue;
				}
				(*m_ThisStartIter)->CollCheck(*m_OtherStartIter);
			}
		}
	}
}

void CollisionMgr::CollGroup::Collision()
{
	if (0 >= m_OtherGroupList.size())
	{
		return;
	}

	m_OtherSIter = m_OtherGroupList.begin();
	m_OtherEIter = m_OtherGroupList.end();
	for (; m_OtherSIter != m_OtherEIter; ++m_OtherSIter)
	{
		CollCheck((*m_OtherSIter));
	}
}

void CollisionMgr::CollGroup::Release()
{
	m_ThisStartIter = m_CollList.begin();
	m_ThisEndIter = m_CollList.end();

	for (; m_ThisStartIter != m_ThisEndIter;)
	{
		if (true == (*m_ThisStartIter)->DeathCheck())
		{
			m_ThisStartIter = m_CollList.erase(m_ThisStartIter);
		}
		else
		{
			++m_ThisStartIter;
		}
	}
}

void CollisionMgr::CollGroup::CollPosSet()
{
	m_ThisStartIter = m_CollList.begin();
	m_ThisEndIter = m_CollList.end();

	for (; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
	{
		(*m_ThisStartIter)->PivotPosSet();
	}
}

void CollisionMgr::CollGroup::DebugRender()
{
	m_ThisStartIter = m_CollList.begin();
	m_ThisEndIter = m_CollList.end();

	for (; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
	{
		(*m_ThisStartIter)->DebugRender();
	}
}

CollisionMgr::CollisionMgr()
{
}

CollisionMgr::~CollisionMgr()
{
	std::map<std::wstring, CollGroup*>::iterator StartIter = m_CollMap.begin();
	std::map<std::wstring, CollGroup*>::iterator EndIter = m_CollMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}
	m_CollMap.clear();
}

CollisionMgr::CollGroup * CollisionMgr::FindCollGroup(const WCHAR * _GroupName)
{
	m_FindIter = m_CollMap.find(_GroupName);
	if (m_FindIter == m_CollMap.end())
	{
		CollGroup* NewCollGroup = new CollGroup();
		NewCollGroup->Name = _GroupName;
		m_CollMap.insert(std::map<std::wstring, CollGroup*>::value_type(_GroupName, NewCollGroup));
		return NewCollGroup;
	}
	return m_FindIter->second;
}

void CollisionMgr::PushCollision(const WCHAR * _GroupName, ActorCollision * _Other)
{
	CollGroup* TempGroup = FindCollGroup(_GroupName);
	if (nullptr == TempGroup)
	{
		Tassert(true);
		return;
	}
	TempGroup->PushCollision(_Other);
}

void CollisionMgr::Link(const WCHAR * _Left, const WCHAR * _Right)
{
	CollGroup* LeftGroup = FindCollGroup(_Left);
	CollGroup* RightGroup = FindCollGroup(_Right);
	
	Tassert(nullptr == LeftGroup);
	Tassert(nullptr == RightGroup);

	if (nullptr == LeftGroup || nullptr == RightGroup)
	{
		return;
	}

	LeftGroup->Link(RightGroup);
}

void CollisionMgr::Collision()
{
	std::map<std::wstring, CollGroup*>::iterator Start = m_CollMap.begin();
	std::map<std::wstring, CollGroup*>::iterator End = m_CollMap.end();

	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			Start->second->CollPosSet();
			Start->second->Collision();
		}
	}
}

void CollisionMgr::Release()
{
	std::map<std::wstring, CollGroup*>::iterator Start = m_CollMap.begin();
	std::map<std::wstring, CollGroup*>::iterator End = m_CollMap.end();

	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			Start->second->Release();
		}
	}
}

void CollisionMgr::DebugRender()
{
	std::map<std::wstring, CollGroup*>::iterator Start = m_CollMap.begin();
	std::map<std::wstring, CollGroup*>::iterator End = m_CollMap.end();

	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			Start->second->DebugRender();
		}
	}
}


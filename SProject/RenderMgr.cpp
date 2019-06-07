#include "stdafx.h"
#include "RenderMgr.h"
#include "ActorRender.h"
#include "ActorBase.h"


bool YsortFunc(const ActorRender* _Left,  const ActorRender* _Right)
{
	if (_Left->PivotPos().Y < _Right->PivotPos().Y)
	{
		return true;
	}
	return false;
}

RenderMgr::RenderMgr()
{
}


RenderMgr::~RenderMgr()
{
}

void RenderMgr::Ysort(int _Index)
{
	m_YSetIter = m_YSortSet.find(_Index);
	if (m_YSetIter == m_YSortSet.end())
	{
		m_YSortSet.insert(_Index);
	}
}

void RenderMgr::PushRender(int _Order, ActorRender * _Render)
{
	std::map<int, std::list<ActorRender*>>::iterator FindIter = m_RenderMap.find(_Order);
	if (m_RenderMap.end() == FindIter)
	{
		std::list<ActorRender*> TempList;
		TempList.push_back(_Render);
		m_RenderMap.insert(std::map<int, std::list<ActorRender*>>::value_type(_Order, TempList));
		return;
	}
	FindIter->second.push_back(_Render);
}

void RenderMgr::Render()
{
	m_StartMapIter = m_RenderMap.begin();
	m_EndMapIter = m_RenderMap.end();

	for (; m_StartMapIter != m_EndMapIter; ++m_StartMapIter)
	{
		m_YSetIter = m_YSortSet.find(m_StartMapIter->first);
		if (m_YSetIter != m_YSortSet.end())
		{
			m_StartMapIter->second.sort(YsortFunc);
		}
		//¸®½ºÆ®
		m_StartListIter = m_StartMapIter->second.begin();
		m_EndListIter = m_StartMapIter->second.end();

		for (; m_StartListIter != m_EndListIter; ++m_StartListIter)
		{
			if (false == (*m_StartListIter)->UpdateCheck())
			{
				continue;
			}
			(*m_StartListIter)->Render();
		}
	}
}

void RenderMgr::Release()
{
	m_StartMapIter = m_RenderMap.begin();
	m_EndMapIter = m_RenderMap.end();

	for (; m_StartMapIter != m_EndMapIter; ++m_StartMapIter)
	{
		m_StartListIter = m_StartMapIter->second.begin();
		m_EndListIter = m_StartMapIter->second.end();

		for (; m_StartListIter != m_EndListIter;)
		{
			if (false == (*m_StartListIter)->DeathCheck())
			{
				++m_StartListIter;
				continue;
			}
			m_StartListIter = m_StartMapIter->second.erase(m_StartListIter);
		}
	}
}


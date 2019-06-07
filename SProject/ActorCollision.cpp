#include "stdafx.h"
#include "ActorCollision.h"
#include "MathMgr.h"
#include "ActorBase.h"
#include "ResourceMgr.h"

ActorCollision::ActorCollision() : m_CollNum(0)
{
}


ActorCollision::~ActorCollision()
{
	//내가 지워질 때 나와 충돌했던 아더한테 셋에서 나를 삭제해달라고 말해주기
	std::set<ActorCollision*>::iterator Start = m_OtherColSet.begin();
	std::set<ActorCollision*>::iterator End = m_OtherColSet.end();
	for (; Start != End; ++Start)
	{
		(*Start)->OtherErase(this);
	}
}

//콜리전 체크 해주기 위해서 포스 업데이트 해주는것
void ActorCollision::PivotPosSet()
{
	m_RectColl.Pos = PivotPos();
	m_RectColl.Size = m_Size;
}

void ActorCollision::CollCheck(ActorCollision * _OtherColl)
{
	FindIter = m_OtherColSet.find(_OtherColl);
	if (true == RectCheck(_OtherColl))
	{
		if (FindIter != m_OtherColSet.end())
		{
			//충돌중
			Actor()->CollStay(this, _OtherColl);
			_OtherColl->Actor()->OtherCollStay(_OtherColl, this);
		}
		else
		{
			//충돌시작
			Actor()->CollStart(this, _OtherColl);
			_OtherColl->Actor()->OtherCollStart(_OtherColl, this);
			m_OtherColSet.insert(_OtherColl);
			_OtherColl->m_OtherColSet.insert(this);
		}
	}
	else if (FindIter != m_OtherColSet.end())//충돌끝
	{
		Actor()->CollExit(this, _OtherColl);
		_OtherColl->Actor()->OtherCollExit(_OtherColl, this);
		//충돌 다 끝나고 지워줘야 한다.
		this->OtherErase(_OtherColl);
		_OtherColl->OtherErase(this);
	}
}

bool ActorCollision::RectCheck(ActorCollision * _OtherColl)
{
	return MathMgr::RectToRect(m_RectColl, _OtherColl->m_RectColl);
}

void ActorCollision::OtherErase(ActorCollision * _OtherColl)
{
	FindIter = m_OtherColSet.find(_OtherColl);
	if (FindIter != m_OtherColSet.end())
	{
		m_OtherColSet.erase(FindIter);
	}
}

void ActorCollision::DebugRender()
{
	FRECT DebugRect = m_RectColl;
	DebugRect.Pos = ScreenPos();
	Rectangle(BHDC, DebugRect.ILEFT(), DebugRect.ITOP(), DebugRect.IRIGHT(), DebugRect.IBOT());
}

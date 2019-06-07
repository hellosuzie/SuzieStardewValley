#pragma once
#include "ActorPosBase.h"

class ActorCollision :	public ActorPosBase
{
private:
	int m_CollNum;

public:
	std::wstring m_GroupName;

private:
	FRECT m_RectColl;
	std::set<ActorCollision*> m_OtherColSet;
	std::set<ActorCollision*>::iterator FindIter;

public:
	ActorCollision();
	~ActorCollision();

public:
	const WCHAR* GroupName()
	{
		return m_GroupName.c_str();
	}
	void CollNum(int _CollNum)
	{
		m_CollNum = _CollNum;
	}
	int CollNum()
	{
		return m_CollNum;
	}
	void PivotPosSet();
	void CollCheck(ActorCollision* _OtherColl);
	bool RectCheck(ActorCollision* _OtherColl);

	//��밡 ���� �浹�¿��� ���������� �����ִ� �Լ�.
	void OtherErase(ActorCollision* _OtherColl);

	void DebugRender();
};


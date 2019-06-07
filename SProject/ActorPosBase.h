#pragma once
#include "UpdateBase.h"

//랜더하기 위해서 엑터베이스를 상속받아야 하는데
//내가 필요한것은 업데이트 기능만 있으면 되기때문에(네임베이스가 필요없음) 업데이트 베이스만 받고 
//랜더러의 부모의 위치만 가지고 올 수 있는 포스베이스를 만들어서 그것을 상속받게 함.
class ActorPosBase :
	public UpdateBase
{
public:
	friend class ActorBase;

private:
	ActorBase* m_PosActor;

protected:
	FSIZE m_Size;
	FPOS m_Pivot;

public:
	ActorPosBase();
	~ActorPosBase();

public:
	void Actor(ActorBase* _Actor)
	{
		m_PosActor = _Actor;
	}
	ActorBase* Actor() const
	{
		return m_PosActor;
	}
	FSIZE Size()
	{
		return m_Size;
	}
	FPOS Pivot()
	{
		return m_Pivot;
	}
	void Size(FSIZE _Size)
	{
		m_Size = _Size;
	}
	void Pivot(FPOS _Pos)
	{
		m_Pivot = _Pos;
	}

public:
	bool DeathCheck() override;
	bool UpdateCheck() override;
	FPOS PivotPos() const;
	FPOS ScreenPos();
};


#pragma once
#include "UpdateBase.h"

//�����ϱ� ���ؼ� ���ͺ��̽��� ��ӹ޾ƾ� �ϴµ�
//���� �ʿ��Ѱ��� ������Ʈ ��ɸ� ������ �Ǳ⶧����(���Ӻ��̽��� �ʿ����) ������Ʈ ���̽��� �ް� 
//�������� �θ��� ��ġ�� ������ �� �� �ִ� �������̽��� ���� �װ��� ��ӹް� ��.
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


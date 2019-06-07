#pragma once
#include <list>
#include "RenderMgr.h"
#include "CollisionMgr.h"

class ActorRender;
class ActorCollision;
class CameraMgr;
class ActorBase;
class GameState
{
public:
	friend class SCore;
	friend ActorBase;

private:
	static std::list<ActorBase*> m_OverActorList;

public:
	static void EndDestroy();
	bool ActorHaveCheck(ActorBase* _Actor);

private:
	static void PushOver(ActorBase* _Actor)
	{
		m_OverActorList.push_back(_Actor);
	}

private:
	std::list<ActorBase*> m_ActorList;
	std::list<ActorBase*>::iterator m_StartIter;
	std::list<ActorBase*>::iterator m_EndIter;

	bool m_InitCheck;
	static bool m_DebugRenderCheck;

public:
	GameState();
	virtual ~GameState();

public:
	inline int AllActorCount()
	{
		return m_ActorList.size();
	}
	inline bool DebugRender()
	{
		return m_DebugRenderCheck;
	}
	inline void DebugRender(bool _Value)
	{
		m_DebugRenderCheck = _Value;
	}

	////������Ʈ���� ��ӹ޾Ƽ� �ھ�� �����ִ� �ֵ�
private:
	//������Ʈ�� �����ϱ� ���� ��������� �� �Լ�
	virtual void StateInit() = 0;

	//������Ʈ �ٲ�� ���� �ٷ� �ѹ� ����.
	virtual void ChangeBegin() {}
	//�� �����Ӹ��� ����.
	virtual void StateUpdate() {}
	virtual void DebugUpdate() {}
	//������Ʈ �ٲ�� ���� �ѹ� ����.
	virtual void ChangeEnd() {}

	////���͵鿡 �ִ� �Լ� �����ִ� �ֵ�
private:
	void PrevUpdate();
	void Update();
	void LaterUpdate();

	void Render();
	void Release();

public:
	void YsortOn(int _Order);

public:
	template<typename T>
	T* MakeActor()
	{
		T* NewActor = new T();
		NewActor->Parent(this);
		NewActor->Init();
		m_ActorList.push_back(NewActor);
		return (T*)NewActor;
	}

	template<typename T>
	T* MakeActor(int _Num)
	{
		T* NewActor = new T(_Num);
		NewActor->Parent(this);
		NewActor->Init();
		m_ActorList.push_back(NewActor);
		return (T*)NewActor;
	}

//////////////////////////////////////////////////Render
private:
	RenderMgr m_RenderMGR;

public:
	void PushRender(int _Order, ActorRender* _Render);

//////////////////////////////////////////////////Camera
private:
	CameraMgr* m_MainCamera;

public:
	CameraMgr* MainCamera()
	{
		return m_MainCamera;
	}

public:
	void MakeCamera();

//////////////////////////////////////////////////Camera
private:
	CollisionMgr m_CollisionMgr;

public:
	void PushCollision(const WCHAR* _GroupName, ActorCollision* _Collision);
	void Link(const WCHAR* _Left, const WCHAR* _Right);
	void Collision();

private:
	void PushActor(ActorBase* _NewActor);

};


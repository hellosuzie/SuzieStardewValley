#pragma once
#include "NameBase.h"
#include "GameState.h"
#include "TimeHelper.h"
#include <list>
#include "SCore.h"

//class GameState;
//class SCore;
class ActorRender;
class ActorBase : public NameBase
{
public:
	friend GameState;
	//friend SCore;

public:
	TimeHelper m_TimerOne;
	TimeHelper m_TimerTwo;

protected:
	FPOS m_Pos;
	float m_ScaleRatio;
	bool m_CameraMode;

private:
	GameState* m_CurState;

private:
	bool m_StateOver;

public:
	ActorBase();
	virtual ~ActorBase();

	inline void Parent(GameState* _State)
	{
		m_CurState = _State;
	}

public:
	bool StateOverCheck()
	{
		return m_StateOver;
	}

	template<typename... Rest>
	void StateOverOn(Rest ..._Arg)
	{
		if (0 >= sizeof...(_Arg))
		{
			return;
		}
		GameState::PushOver(this);
		m_StateOver = true;
		StateOverPush(_Arg...);
	}

	template<typename... Rest>
	void StateOverPush(ALLSTATE T, Rest ..._Arg)
	{
		CORE.PushActor(T, this);
		StateOverPush(_Arg...);
	}

	void StateOverPush()
	{
	}

public:
	inline float ScaleRatio()
	{
		return m_ScaleRatio;
	}
	inline void ScaleRatio(float _Ratio)
	{
		m_ScaleRatio = _Ratio;
	}
	inline GameState* Parent()
	{
		return m_CurState;
	}
	inline void Pos(FPOS _Pos)
	{
		m_Pos = _Pos;
	}
	inline FPOS Pos()
	{
		return m_Pos;
	}

private:
	virtual void Init() = 0;
	virtual void PrevUpdate();
	virtual void Update();
	virtual void LaterUpdate();

public:
	void Vibration();

public:
	FPOS ScreenPos();

	inline void CameraMode(bool _Value)
	{
		m_CameraMode = _Value;
	}
	virtual bool CameraMode()
	{
		return m_CameraMode;
	}

//////////////////////////////////////////////////Render
private:
	std::list<ActorRender*> m_RenderList;

public:
	template<typename T>
	T* MakeRender(int _Order = 0)
	{
		T* NewRender = new T();
		NewRender->Actor(this);
		NewRender->Order(_Order);
		m_RenderList.push_back(NewRender);
		Parent()->PushRender(_Order, NewRender);
		return NewRender;
	}

//////////////////////////////////////////////////Collision
private:
	//엑터 하나에 여러개의 콜리전을 넣을 수 있어야 하니까 리스트로 관리
	std::list<ActorCollision*> m_CollList;

public:
	ActorCollision* MakeCollision(const WCHAR* _ColGroupName, FSIZE _Size, int _CollNum = 0);

public:
	virtual void CollStart(ActorCollision* _This, ActorCollision* _Other) {}
	virtual void CollStay(ActorCollision* _This, ActorCollision* _Other) {}
	virtual void CollExit(ActorCollision* _This, ActorCollision* _Other) {}

	virtual void OtherCollStart(ActorCollision* _This, ActorCollision* _Other) {}
	virtual void OtherCollStay(ActorCollision* _This, ActorCollision* _Other) {}
	virtual void OtherCollExit(ActorCollision* _This, ActorCollision* _Other) {}

public:
	virtual void DebugRender();
};


#include "stdafx.h"
#include "ActorBase.h"
#include "RenderMgr.h"
#include "ActorRender.h"
#include "ActorCollision.h"

std::list<ActorBase*> GameState::m_OverActorList = std::list<ActorBase*>();

#ifdef _DEBUG
bool GameState::m_DebugRenderCheck = true;
#else
bool GameState::m_DebugRenderCheck = false;
#endif // DEBUG

void GameState::EndDestroy()
{
	std::list<ActorBase*>::iterator StartIter = m_OverActorList.begin();
	std::list<ActorBase*>::iterator EndIter = m_OverActorList.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
	}
}

bool GameState::ActorHaveCheck(ActorBase* _Actor)
{
	m_StartIter = m_ActorList.begin();
	m_EndIter = m_ActorList.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (_Actor == (*m_StartIter))
		{
			return true;
		}
	}
	return false;
}


GameState::GameState() : m_InitCheck(false)
{
	MakeCamera();
} 


GameState::~GameState()
{
	m_StartIter = m_ActorList.begin();
	m_EndIter = m_ActorList.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (nullptr != (*m_StartIter) && false == (*m_StartIter)->StateOverCheck())
		{
			delete (*m_StartIter);
			(*m_StartIter) = nullptr;
		}
	}
	m_ActorList.clear();

	if (nullptr != m_MainCamera)
	{
		delete m_MainCamera;
		m_MainCamera = nullptr;
	}
}


void GameState::PrevUpdate()
{
	m_StartIter = m_ActorList.begin();
	m_EndIter = m_ActorList.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (false == (*m_StartIter)->UpdateCheck())
		{
			continue;
		}
		(*m_StartIter)->PrevUpdate();
	}
}

void GameState::Update()
{
	m_StartIter = m_ActorList.begin();
	m_EndIter = m_ActorList.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (false == (*m_StartIter)->UpdateCheck())
		{
			continue;
		}
		(*m_StartIter)->Update();
	}
}

void GameState::LaterUpdate()
{
	m_StartIter = m_ActorList.begin();
	m_EndIter = m_ActorList.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (false == (*m_StartIter)->UpdateCheck())
		{
			continue;
		}
		(*m_StartIter)->LaterUpdate();
	}
}

void GameState::Render()
{
	m_MainCamera->Update();
	m_RenderMGR.Render();

	if (true == m_DebugRenderCheck)
	{
		m_CollisionMgr.DebugRender();

		m_StartIter = m_ActorList.begin();
		m_EndIter = m_ActorList.end();

		for (; m_StartIter != m_EndIter; ++m_StartIter)
		{
			if (false == (*m_StartIter)->UpdateCheck())
			{
				continue;
			}
			(*m_StartIter)->DebugRender();
		}
	}
}

void GameState::Release()
{

	m_RenderMGR.Release();
	m_CollisionMgr.Release();

	m_StartIter = m_ActorList.begin();
	m_EndIter = m_ActorList.end();

	for (; m_StartIter != m_EndIter;)
	{
		if (false == (*m_StartIter)->DeathCheck())
		{
			++m_StartIter;
			continue;
		}
		delete (*m_StartIter);
		m_StartIter = m_ActorList.erase(m_StartIter);
	}
}

void GameState::YsortOn(int _Order)
{
	m_RenderMGR.Ysort(_Order);
}

void GameState::PushRender(int _Order, ActorRender* _Render)
{
	Tassert(nullptr == _Render);
	m_RenderMGR.PushRender(_Order, _Render);
}

void GameState::MakeCamera()
{
	m_MainCamera = new CameraMgr();
}

void GameState::PushCollision(const WCHAR * _GroupName, ActorCollision * _Collision)
{
	m_CollisionMgr.PushCollision(_GroupName, _Collision);
}

void GameState::Link(const WCHAR * _Left, const WCHAR * _Right)
{
	m_CollisionMgr.Link(_Left, _Right);
}

void GameState::Collision()
{
	m_CollisionMgr.Collision();
}

void GameState::PushActor(ActorBase* _NewActor)
{
	Tassert(nullptr == _NewActor);
	m_ActorList.push_back(_NewActor);

	std::list<ActorCollision*>::iterator CStartIter = _NewActor->m_CollList.begin();
	std::list<ActorCollision*>::iterator CEndIter = _NewActor->m_CollList.end();
	for (; CStartIter != CEndIter; ++CStartIter)
	{
		m_CollisionMgr.PushCollision((*CStartIter)->GroupName(), (*CStartIter));
	}

	std::list<ActorRender*>::iterator RStartIter = _NewActor->m_RenderList.begin();
	std::list<ActorRender*>::iterator REndIter = _NewActor->m_RenderList.end();
	for (; RStartIter != REndIter; ++RStartIter)
	{
		m_RenderMGR.PushRender((*RStartIter)->Order(), (*RStartIter));
	}
}
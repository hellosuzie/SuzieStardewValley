#include "stdafx.h"
#include "ActorBase.h"
#include "SCore.h"

CameraMgr::CameraMgr() : m_Range(false)
{
}


CameraMgr::~CameraMgr()
{
}

void CameraMgr::Update()
{
	//타겟이 없다면 카메라포스는 랜더포스
	if (nullptr == m_Target)
	{
		m_RenderPos = m_Camera;
	}
	else
	{
		m_RenderPos = m_Target->Pos()/* - FPOS{ WINSIZEXH, WINSIZEYH }*/;
	}

	//범위 지정해주는 경우
	if (true == m_Range)
	{
		//배경 시작포스가 랜더포스 x보다 더 왼쪽에 있다면? - 플레이어가 배경보다 왼쪽으로 간다면 못가게 막아야함
		if (m_StartPos.X + WINSIZEXH > m_RenderPos.X)
		{
			m_RenderPos.X = m_StartPos.X + WINSIZEXH;
		}
		if (m_StartPos.Y + WINSIZEYH > m_RenderPos.Y)
		{
			m_RenderPos.Y = m_StartPos.Y + WINSIZEYH;
		}
		if (m_EndPos.X - WINSIZEXH < m_RenderPos.X)
		{
			m_RenderPos.X = m_EndPos.X - WINSIZEXH;
		}
		if (m_EndPos.Y - WINSIZEYH < m_RenderPos.Y)
		{
			m_RenderPos.Y = m_EndPos.Y - WINSIZEYH;
		}
	}
	m_RenderPos.X -= WINSIZEXH;
	m_RenderPos.Y -= WINSIZEYH;
}

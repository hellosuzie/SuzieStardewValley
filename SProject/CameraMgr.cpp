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
	//Ÿ���� ���ٸ� ī�޶������� ��������
	if (nullptr == m_Target)
	{
		m_RenderPos = m_Camera;
	}
	else
	{
		m_RenderPos = m_Target->Pos()/* - FPOS{ WINSIZEXH, WINSIZEYH }*/;
	}

	//���� �������ִ� ���
	if (true == m_Range)
	{
		//��� ���������� �������� x���� �� ���ʿ� �ִٸ�? - �÷��̾ ��溸�� �������� ���ٸ� ������ ���ƾ���
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

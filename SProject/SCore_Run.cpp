#include "stdafx.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "TimeMgr.h"	 
#include "ResourceMgr.h"
#include "ActorBase.h"

void SCore::Run()
{
	//DebugRender �� ���� �������� ������ִ� �ڵ�
	MyBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	OldBrush = (HBRUSH)SelectObject(BHDC, MyBrush);
	MyPen = (HPEN)CreatePen(PS_DOT, 2, RGB(35, 200, 200));
	OldPen = (HPEN)SelectObject(BHDC, MyPen);

	ENTER.Update();
	TIME.Update();

	//������Ʈ�� ������Ʈ �ϴ°�
	m_CurState->StateUpdate();

	//������Ʈ�� ��ӹ��� ���͵��� ������Ʈ
	m_CurState->PrevUpdate();
	m_CurState->Update();
	m_CurState->LaterUpdate();

	//����
	m_CurState->Render();
	m_CurState->Collision();
	m_CurState->Release();

	if (true == DebugRenderCheck())
	{
		m_CurState->DebugUpdate();
	}
	
	//������۸� �׷��ִ°�
	BitBlt(SHDC, 0, 0, WINSIZE.X, WINSIZE.Y, BHDC, 0, 0, SRCCOPY);

	//DebugRender �� ���� �������� ������ִ� �ڵ� - ����
	SelectObject(BHDC, OldBrush);
	DeleteObject(MyBrush);
	SelectObject(BHDC, OldPen);
	DeleteObject(MyPen);

	if (nullptr != m_NextState)
	{
		if (false == m_NextState->m_InitCheck)
		{
			m_NextState->StateInit();
			m_NextState->m_InitCheck = true;
		}
		//������Ʈ �ٲ�� ���� ���������� ȣ���ϴ� �Լ�.
		m_CurState->ChangeEnd();
		//������Ʈ ü����
		m_CurState = m_NextState;

		std::list<ActorBase*>::iterator OverStart = GameState::m_OverActorList.begin();
		std::list<ActorBase*>::iterator OverEnd = GameState::m_OverActorList.end();
		for (; OverStart != OverEnd; ++OverStart)
		{
			(*OverStart)->Parent(m_CurState);
		}

		//������Ʈ �ٲ�� ���� ó�� ȣ���ϴ� �Լ�.
		m_CurState->ChangeBegin();
		m_NextState = nullptr;
	}
}
#include "stdafx.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "TimeMgr.h"	 
#include "ResourceMgr.h"
#include "ActorBase.h"

void SCore::Run()
{
	//DebugRender 선 색과 투명으로 만들어주는 핸들
	MyBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	OldBrush = (HBRUSH)SelectObject(BHDC, MyBrush);
	MyPen = (HPEN)CreatePen(PS_DOT, 2, RGB(35, 200, 200));
	OldPen = (HPEN)SelectObject(BHDC, MyPen);

	ENTER.Update();
	TIME.Update();

	//스테이트가 업데이트 하는것
	m_CurState->StateUpdate();

	//스테이트를 상속받은 엑터들의 업데이트
	m_CurState->PrevUpdate();
	m_CurState->Update();
	m_CurState->LaterUpdate();

	//랜더
	m_CurState->Render();
	m_CurState->Collision();
	m_CurState->Release();

	if (true == DebugRenderCheck())
	{
		m_CurState->DebugUpdate();
	}
	
	//더블버퍼링 그려주는곳
	BitBlt(SHDC, 0, 0, WINSIZE.X, WINSIZE.Y, BHDC, 0, 0, SRCCOPY);

	//DebugRender 선 색과 투명으로 만들어주는 핸들 - 삭제
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
		//스테이트 바뀌기 전에 마지막으로 호출하는 함수.
		m_CurState->ChangeEnd();
		//스테이트 체인지
		m_CurState = m_NextState;

		std::list<ActorBase*>::iterator OverStart = GameState::m_OverActorList.begin();
		std::list<ActorBase*>::iterator OverEnd = GameState::m_OverActorList.end();
		for (; OverStart != OverEnd; ++OverStart)
		{
			(*OverStart)->Parent(m_CurState);
		}

		//스테이트 바뀌고 가장 처음 호출하는 함수.
		m_CurState->ChangeBegin();
		m_NextState = nullptr;
	}
}
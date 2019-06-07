#include "stdafx.h"
#include "resource.h"
#include "SCore.h"
#include "ResourceMgr.h"

#include <locale.h>

//#ifdef _DEBUG

//#else
//bool SCore::m_DebugMode = false;
//#endif

bool SCore::m_DebugMode = true;
bool SCore::m_CoreCheck = true;
HBRUSH SCore::MyBrush;
HBRUSH SCore::OldBrush;
HPEN SCore::MyPen;
HPEN SCore::OldPen;

ALLSTATE SCore::CurState;

void SCore::DebugRenderOn()
{
	m_DebugMode = true;
}

void SCore::DebugRenderOff()
{
	m_DebugMode = false;
}

LRESULT CALLBACK SCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		m_CoreCheck = false;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

SCore::SCore() 
	: m_HINST(nullptr), m_HWND(nullptr), m_HDC(nullptr)
	, m_StateVec(ALLSTATE::STATEMAX), m_CurState(nullptr), m_NextState(nullptr)
	, m_WinSize({ 1024, 768 })
{
}

SCore::~SCore()
{
	for (size_t i = 0; i < m_StateVec.size(); i++)
	{
		if (nullptr != m_StateVec[i])
		{
			delete m_StateVec[i];
			m_StateVec[i] = nullptr;
		}
	}
	GameState::EndDestroy();
}

int SCore::Start(HINSTANCE _hInstance)
{
	if (nullptr == _hInstance)
	{
		Tassert(true);
		return -1;
	}
	
	m_HINST = _hInstance;

	//언어 설정
	_wsetlocale(LC_ALL, L"KOR");
	MyRegisterClass(m_HINST);

	if (!InitInstance(m_HINST))
	{
		return FALSE;
	}

	MSG msg;
	RES.Init();
	UserInit();

	int Count = 0;
	while (true == m_CoreCheck)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Run();
		}
	}

	return (int)msg.wParam;
}

ATOM SCore::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"SClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL SCore::InitInstance(HINSTANCE _hInstance)
{
	m_HWND = CreateWindowW(L"SClass", L"Stardew Valley", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

	if (!m_HWND)
	{
		return FALSE;
	}

	RECT RC = { 0, 0, m_WinSize.X, m_WinSize.Y };
	AdjustWindowRect(&RC, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(SHWND, nullptr, 0, 0, RC.right - RC.left, RC.bottom - RC.top, SWP_NOZORDER | SWP_NOMOVE);

	m_HDC = GetDC(m_HWND);
	
	ShowWindow(m_HWND, SW_SHOWDEFAULT);
	UpdateWindow(m_HWND);

	return TRUE;
}

//////////////////////////////////////////////////State

void SCore::ChangeState(ALLSTATE _State)
{
	if (nullptr == m_StateVec[_State])
	{
		Tassert(true);
		return;
	}

	//curstate가 null 일때 - 제일 처음
	if (nullptr == m_CurState)
	{
		m_CurState = m_StateVec[_State];
		if (false == m_CurState->m_InitCheck)
		{
			//스테이트 만들고 꼭 호출해줘야 한다.
			m_CurState->StateInit();
			m_CurState->m_InitCheck = true;
			m_CurState->ChangeBegin();
		}
		return;
	}
	else
	{
		m_NextState = m_StateVec[_State];
		return;
	}
}

bool SCore::HaveCheck(ALLSTATE _State, ActorBase* _Actor)
{
	Tassert(nullptr == m_StateVec[_State]);
	return m_StateVec[_State]->ActorHaveCheck(_Actor);
}

void SCore::PushActor(ALLSTATE _State, ActorBase* _Actor)
{
	Tassert(nullptr == m_StateVec[_State]);
	m_StateVec[_State]->PushActor(_Actor);
}
 
GameState* SCore::FindState(int _Num)
{
	return m_StateVec[_Num];
}
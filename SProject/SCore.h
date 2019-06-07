#pragma once
#include <vector>

enum ALLSTATE
{
	TITLE1,
	TITLE2,
	TITLE,
	ROOM,
	FARM,
	TOWN,
	MINE,
	MINE1,
	MINE2,
	MINE3,
	MINE4,
	MINE5,
	STORE,
	TOWN2,
	COOP,
	BARN,
	MANI,
	ROBIN,
	EDIT,
	END,
	STATEMAX
};

class ActorBase;
class GameState;
class SCore
{
public:
	static SCore& Inst()
	{
		static SCore NewCore = SCore();
		return NewCore;
	}

private:
	HINSTANCE m_HINST;
	HWND m_HWND;
	HDC m_HDC;
	ISIZE m_WinSize;

private:
	static bool m_CoreCheck;
	static bool m_DebugMode;

	static HBRUSH MyBrush;
	static HBRUSH OldBrush;
	static HPEN MyPen;
	static HPEN OldPen;

public:
	static ALLSTATE CurState;

private:
	SCore();
	~SCore();

public:
	ISIZE WinSize()
	{
		return m_WinSize;
	}
	HINSTANCE WINHINST()
	{
		return m_HINST;
	}
	HDC WINDC()
	{
		return m_HDC;
	}
	HWND WINHWND()
	{
		return m_HWND;
	}

public:
	//디버그랜더 확인하는 함수
	static bool DebugRenderCheck()
	{
		return m_DebugMode;
	}
	//디버그랜더 키고 꺼주는 함수.
	static void DebugRenderOn();
	static void DebugRenderOff();

private:
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	ATOM                MyRegisterClass(HINSTANCE _hInstance);
	BOOL                InitInstance(HINSTANCE);

private:
	void UserInit();
	void Run();

public:
	int Start(HINSTANCE _hInstance);

public:
	template<typename T>
	T* MakeState(ALLSTATE _State)
	{
		m_StateVec[_State] = new T;
		return(T*)m_StateVec[_State];

	}

//////////////////////////////////////////////////State
private:
	std::vector<GameState*> m_StateVec;
	GameState* m_CurState;
	GameState* m_NextState;

public:
	void ChangeState(ALLSTATE _State);

public:
	bool HaveCheck(ALLSTATE _State, ActorBase* _Actor);
	void PushActor(ALLSTATE _State, ActorBase* _Actor);

	GameState* FindState(int _Num);
};


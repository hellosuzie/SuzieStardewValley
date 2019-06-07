#pragma once
#include "ActorBase.h"

class ActorCollision;
class SingleActorRender;
class ButtonMgr :
	public ActorBase
{
private:
	class ButtonData
	{
	public:
		std::wstring m_BName;
		size_t m_SpriteIndex;
	};

private:
	std::wstring m_ButtonName;

	ButtonData m_BaseImage;
	ButtonData m_EnterImage;
	ButtonData m_ClickImage;

	ActorCollision* m_ButtonColl;
	FSIZE m_ButtonSize;

	bool m_ClickCheck;
	
	SingleActorRender* m_ButtonBack;

	void* m_Data;
	void(__stdcall *m_EnterFunc)	(	void*	);
	void(__stdcall *m_UpFunc)		(	void*	);
	void(__stdcall *m_ClickFunc)	(	void*	);
	void(__stdcall *m_DownFunc)		(	void*	);
	void(__stdcall *m_DownStayFunc)	(	void*	);
	void(__stdcall *m_ExitFunc)		(	void*	);


public:
	ButtonMgr();
	~ButtonMgr();

public:
	void SetData(void* _Data)
	{
		m_Data = _Data;
	}

public:
	void Init() override;

	void SetEnterFunc(void(__stdcall* _Func)(void*))	{	m_EnterFunc = _Func;	}
	void SetUpFunc(void(__stdcall* _Func)(void*))		{	m_UpFunc = _Func;		}
	void SetClickFunc(void(__stdcall* _Func)(void*))	{	m_ClickFunc = _Func;	}
	void SetDownStayFunc(void(__stdcall* _Func)(void*)) {	m_DownStayFunc = _Func;	}
	void SetDownFunc(void(__stdcall* _Func)(void*))		{	m_DownFunc = _Func;		}
	void SetExitFunc(void(__stdcall* _Func)(void*))		{	m_ExitFunc = _Func;		}

	void ButtonInit(const WCHAR* _CollName, const WCHAR* _ButtonName, FPOS _Pos, FSIZE _Size);
	void CollButtonInit(const WCHAR* _CollName, const WCHAR* _ButtonName, FPOS _Pos, FSIZE _Size);

	void SetBaseImage(const WCHAR* _SpriteName, int _SpriteIndex);
	void SetEnterImage(const WCHAR* _SpriteName, int _SpriteIndex);
	void SetClickImage(const WCHAR* _SpriteName, int _SpriteIndex);

	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;

	void Enter();
	void Up();
	void Click();
	void Down();
	void DownStay();
	void Exit();

};


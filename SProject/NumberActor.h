#pragma once
#include "ActorBase.h"
#include "SingleActorRender.h"

class NumberActor :
	public ActorBase
{
private:
	int m_Value;
	int m_NumberCount;

	std::wstring m_NumSpriteName;
	std::vector<SingleActorRender*> m_NumRenderVec;
	std::vector<int> m_CutNumberVec;

public:
	NumberActor();
	~NumberActor();

public:
	void Value(size_t _Value)
	{
		m_Value = _Value;
	}

public:
	void NumberInit(size_t _NumberCount, const WCHAR* _Name, FSIZE _Numbersize);

public:
	void Init();
	void PrevUpdate();
	void Update();
	void LaterUpdate();

};


#pragma once
#include "ActorBase.h"

class SingleActorRender;
class StoreBack :	public ActorBase
{
private:
	SingleActorRender* m_StoreBack;

public:
	StoreBack();
	~StoreBack();

public:
	SingleActorRender* GetStoreBack()
	{
		return m_StoreBack;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


#pragma once
#include "ActorBase.h"

class SingleActorRender;
class TownBack :	public ActorBase
{
private:
	SingleActorRender* m_TownBack;

public:
	TownBack();
	~TownBack();

public:
	SingleActorRender* GetTonwBack()
	{
		return m_TownBack;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


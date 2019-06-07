#pragma once
#include "ActorBase.h"

class SingleActorRender;
class MineBack :	public ActorBase
{
private:
	SingleActorRender* m_MineBack;

public:
	MineBack();
	~MineBack();

public:
	SingleActorRender* GetMineBack()
	{
		return m_MineBack;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


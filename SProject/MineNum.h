#pragma once
#include "ActorBase.h"

class SingleActorRender;
class MineNum :
	public ActorBase
{
private:
	SingleActorRender* m_NumRender;

public:
	MineNum();
	~MineNum();

public:
	SingleActorRender* NumRender()
	{
		return m_NumRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


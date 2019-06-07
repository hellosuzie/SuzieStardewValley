#pragma once
#include "ActorBase.h"

class SingleActorRender;
class ManiBack :	public ActorBase
{
private:
	SingleActorRender* m_ManiBack;

public:
	ManiBack();
	~ManiBack();

public:
	SingleActorRender* GetManiBack()
	{
		return m_ManiBack;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


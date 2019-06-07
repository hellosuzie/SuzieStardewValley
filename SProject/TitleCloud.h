#pragma once
#include "ActorBase.h"

class SingleActorRender;
class TitleCloud :	public ActorBase
{
private:
	SingleActorRender* m_CloudOne;

	SingleActorRender* m_CloudThree;

public:
	TitleCloud();
	~TitleCloud();

public:
	SingleActorRender* CloudOne()
	{
		return m_CloudOne;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


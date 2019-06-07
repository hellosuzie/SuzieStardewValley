#pragma once
#include "ActorBase.h"

class SingleActorRender;
class InfoRender :
	public ActorBase
{
private:
	SingleActorRender* m_ItemInfoRender;

public:
	InfoRender();
	~InfoRender();

public:
	SingleActorRender* ItemInfoRender()
	{
		return m_ItemInfoRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

};


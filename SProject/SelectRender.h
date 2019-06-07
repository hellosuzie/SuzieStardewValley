#pragma once
#include "ActorBase.h"

class SingleActorRender;
class SelectRender :
	public ActorBase
{
private:
	SingleActorRender* m_SelectRender;

public:
	SelectRender();
	~SelectRender();

public:
	void Init();
	void PrevUpdate();
	void Update();
	void LaterUpdate();
};


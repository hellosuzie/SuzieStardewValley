#pragma once
#include "ActorBase.h"

class SingleActorRender;
class MainInvenBack :
	public ActorBase
{
private:
	SingleActorRender* m_MainInBack;

public:
	MainInvenBack();
	~MainInvenBack();

public:
	void Init();
	void PrevUpdate();
	void Update();
	void LaterUpdate();
};


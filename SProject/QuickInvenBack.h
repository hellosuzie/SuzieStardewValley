#pragma once
#include "ActorBase.h"

class SingleActorRender;
class QuickInvenBack :
	public ActorBase
{
private:
	SingleActorRender* m_QuickInBack;

public:
	QuickInvenBack();
	~QuickInvenBack();

public:
	void Init();
	void PrevUpdate();
	void Update();
	void LaterUpdate();
};


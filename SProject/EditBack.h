#pragma once
#include "ActorBase.h"

class SingleActorRender;
class EditBack :
	public ActorBase
{
private:
	SingleActorRender* m_EditBack;

public:
	EditBack();
	~EditBack();

public:
	void Init() override;

};


#pragma once
#include "ActorBase.h"

class SingleActorRender;
class EndBack :
	public ActorBase
{
public:
	SingleActorRender* m_EndBack;

public:
	EndBack();
	~EndBack();

public:
	void Init() override;


};


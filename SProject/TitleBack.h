#pragma once
#include "ActorBase.h"

class SingleActorRender;
class TitleBack :
	public ActorBase
{
public:
	SingleActorRender* m_TitleBack;

public:
	TitleBack();
	~TitleBack();

public:
	void Init() override;


};


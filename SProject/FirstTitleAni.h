#pragma once
#include "ActorBase.h"

class AniActorRender;
class FirstTitleAni :
	public ActorBase
{
private:
	AniActorRender* m_FirstTitleAni;

public:
	FirstTitleAni();
	~FirstTitleAni();

public:
	void Init() override;
};


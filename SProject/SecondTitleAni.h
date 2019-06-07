#pragma once
#include "ActorBase.h"

class SingleActorRender;
class AniActorRender;
class SecondTitleAni :
	public ActorBase
{
private:
	AniActorRender* m_SecondTitleAni;
	AniActorRender* m_SecondTitleAni2;

	SingleActorRender* m_NameRender;

public:
	SecondTitleAni();
	~SecondTitleAni();

public:
	void Init() override;
};


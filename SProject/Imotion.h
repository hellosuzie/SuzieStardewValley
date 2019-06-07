#pragma once
#include "ActorBase.h"
#include "TimeHelper.h"

class AniActorRender;
class Imotion :
	public ActorBase
{
private:
	AniActorRender* m_ImoRender;

public:
	Imotion();
	~Imotion();

public:
	AniActorRender* ImoRender()
	{
		return m_ImoRender;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


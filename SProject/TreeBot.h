#pragma once
#include "ActorBase.h"

class AniActorRender;
class TreeBot :
	public ActorBase
{
private:
	AniActorRender* m_TreeAniBot;

public:
	TreeBot();
	~TreeBot();

public:
	AniActorRender* TreeAniBotRnder()
	{
		return m_TreeAniBot;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

private:
	void MakeTreeAni();

};


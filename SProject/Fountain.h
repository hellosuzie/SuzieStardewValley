#pragma once
#include "ActorBase.h"

class SoundPlayer;
class SingleActorRender;
class AniActorRender;
class Fountain :
	public ActorBase
{
private:
	SoundPlayer* FountainSp;

private:
	AniActorRender* m_DownWaterAni;
	AniActorRender* m_LeftWaterAni;
	AniActorRender* m_RightWaterAni;
	AniActorRender* m_RightDWaterAni;
	AniActorRender* m_LeftDWaterAni;

	SingleActorRender* m_Bot;

public:
	Fountain();
	~Fountain();

public:
	void Init() override;
	void Update() override;

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other);
	void CollStay(ActorCollision* _This, ActorCollision* _Other);
	void CollExit(ActorCollision* _This, ActorCollision* _Other);
};


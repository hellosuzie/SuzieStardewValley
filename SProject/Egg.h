#pragma once
#include "ActorBase.h"
#include "TimeHelper.h"

class SoundPlayer;
class ActorCollision;
class SingleActorRender;
class Egg :
	public ActorBase
{
	enum EGGTYPE
	{
		Chicken,
		Duck
	};

private:
	SingleActorRender* m_EggRender;
	ActorCollision* m_EggColl;

	EGGTYPE m_EggType;

private:
	TimeHelper BabyTimer;
	TimeHelper DBabyTimer;
	SoundPlayer* BabyChickenSp;
	SoundPlayer* BabyDuckSp;

public:
	Egg(int _Type);
	~Egg();

public:
	int EggType()
	{
		return m_EggType;
	}

public:
	void Init() override;
	void Update() override;

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other);
	void CollStay(ActorCollision* _This, ActorCollision* _Other);
	void CollExit(ActorCollision* _This, ActorCollision* _Other);
};


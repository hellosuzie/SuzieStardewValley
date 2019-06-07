#pragma once
#include "ActorBase.h"

class SoundPlayer;
class ActorCollision;
class SingleActorRender;
class AnimalStoreMenu :
	public ActorBase
{
private:
	SoundPlayer* AnimalStoreSp;

public:
	static bool AnimalExCheck;
	static bool BAnimalExCheck;

private:
	SingleActorRender* m_StoreFadeRender;
	SingleActorRender* m_AnimalStoreMenuRender;

	SingleActorRender* m_OkRender;
	SingleActorRender* m_CancleRender;
	ActorCollision* m_OkColl;
	ActorCollision* m_CancleColl;

	SingleActorRender* m_0Render;
	SingleActorRender* m_1Render;
	SingleActorRender* m_2Render;
	SingleActorRender* m_3Render;
	SingleActorRender* m_4Render;
	SingleActorRender* m_5Render;
	SingleActorRender* m_6Render;
	
	ActorCollision* m_0Coll;
	ActorCollision* m_1Coll;
	ActorCollision* m_2Coll;
	ActorCollision* m_3Coll;
	ActorCollision* m_4Coll;
	ActorCollision* m_5Coll;
	ActorCollision* m_6Coll;
	
	SingleActorRender* m_NameRender;

public:
	static int StoreNum;

public:
	AnimalStoreMenu();
	~AnimalStoreMenu();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


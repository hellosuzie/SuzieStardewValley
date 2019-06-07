#pragma once
#include "ActorBase.h"

class SoundPlayer;
class FarmBack;
class ActorCollision;
class SingleActorRender;
class CoopStoreMenu :
	public ActorBase
{
private:
	SoundPlayer* CoopStoreSp;

private:
	SingleActorRender* m_StoreFadeRender;
	SingleActorRender* m_CoopStoreMenuRender;

	SingleActorRender* m_OkRender;
	SingleActorRender* m_CancleRender;
	ActorCollision* m_OkColl;
	ActorCollision* m_CancleColl;
	
	SingleActorRender* m_BulidRender;
	ActorCollision* m_BulidColl;

	SingleActorRender* m_HorizenArrow;
	ActorCollision* m_HorizenArrowColl;

public:
	static bool CoopCheck;
	static bool BarnCheck;
	static bool PageCheck;

private:
	static int StoreNum;

public:
	CoopStoreMenu();
	~CoopStoreMenu();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


#pragma once
#include "ActorBase.h"

class ActorCollision;
class SingleActorRender;
class StoreMenu :
	public ActorBase
{
private:
	SingleActorRender* m_StoreFadeRender;
	SingleActorRender* m_StoreMenuRender;

	SingleActorRender* m_FisrtRender;
	SingleActorRender* m_SecondRender;
	SingleActorRender* m_ThirdRender;
	SingleActorRender* m_FourthRender;

	SingleActorRender* m_UpArrowRender;
	SingleActorRender* m_DownArrowRender;

	SingleActorRender* m_OkRender;
	SingleActorRender* m_CancleRender;

	ActorCollision* m_FirstColl;
	ActorCollision* m_SecondColl;
	ActorCollision* m_ThirdColl;
	ActorCollision* m_FourthColl;

	ActorCollision* m_UpArrowColl;
	ActorCollision* m_DownArrowColl;

	ActorCollision* m_OkColl;
	ActorCollision* m_CancleColl;

private:
	static int StoreNum;

	int OneTemp;
	int TwoTemp;
	int ThreeTemp;
	int FourTemp;

public:
	StoreMenu();
	~StoreMenu();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


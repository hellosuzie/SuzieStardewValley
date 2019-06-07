#pragma once
#include "ActorBase.h"

class TownStoreMenu;
class SingleActorRender;
class Marlon :
	public ActorBase
{
private:
	SingleActorRender* m_Marlon;
	TownStoreMenu* m_TownStoreMenu;

public:
	static bool m_StoreOpen;

public:
	Marlon();
	~Marlon();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;
};


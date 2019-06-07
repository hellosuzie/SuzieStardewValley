#pragma once
#include "ActorBase.h"

class SoundPlayer;
class StoreMenu;
class SingleActorRender;
class Haley :
	public ActorBase
{
private:
	SoundPlayer* HaleySp;

private:
	SingleActorRender* m_Haley;
	StoreMenu* m_StoreMenu;

public:
	static bool m_StoreOpen;

public:
	Haley();
	~Haley();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;

private:
	void SellItem(size_t _InvenCount);

};


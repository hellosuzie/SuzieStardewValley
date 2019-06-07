#pragma once
#include "ActorBase.h"

class AnimalStoreMenu;
class Mani :
	public ActorBase
{
private:
	AnimalStoreMenu* m_AStoreMenu;

public:
	static bool m_StoreOpen;

public:
	Mani();
	~Mani();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;


};


#pragma once
#include "ActorBase.h"

class CoopStoreMenu;
class Robin :
	public ActorBase
{
private:
	CoopStoreMenu* m_CStoreMenu;

public:
	static bool m_StoreOpen;

public:
	Robin();
	~Robin();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;


};


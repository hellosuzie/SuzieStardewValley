#pragma once
#include "ActorBase.h"

class ActorCollision;
class AniActorRender;
class TreeTop :
	public ActorBase
{
	enum TREETYPE
	{
		Maple,
		Acron,
		Pine,
		TTypeMax
	};

private:
	AniActorRender* m_TreeAniTop;
	ActorCollision* m_TreeCollLeap;
	ActorCollision* m_TreeColl;

	float m_AlphaTime;
	TREETYPE m_TreeType;

public:
	TreeTop();
	~TreeTop();

public:
	AniActorRender* TreeAniTopRender()
	{
		return m_TreeAniTop;
	}
	void TreeType(int _Num)
	{
		m_TreeType = (TREETYPE)_Num;
	}
	int TreeType()
	{
		return m_TreeType;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

	void CollStart(ActorCollision* _This, ActorCollision* _Other) override;
	void CollStay(ActorCollision* _This, ActorCollision* _Other) override;
	void CollExit(ActorCollision* _This, ActorCollision* _Other) override;

private:
	void MakeTreeAni();
};


#pragma once
#include "ActorBase.h"

class SingleActorRender;
class TileAim :
	public ActorBase
{
public:
	static SingleActorRender* m_Aim;

public:
	TileAim();
	~TileAim();

public:
	void Init();
	void PrevUpdate();
	void Update();
	void LaterUpdate();
};


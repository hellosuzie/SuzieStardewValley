#pragma once
#include "ActorBase.h"
class MouseBaby :
	public ActorBase
{
public:
	MouseBaby();
	~MouseBaby();

public:
	void Init();
	void PrevUpdate();
	void Update();
	void LaterUpdate();
};


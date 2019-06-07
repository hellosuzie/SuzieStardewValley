#pragma once
#include "ActorBase.h"

class SingleActorRender;
class StoreDask :
	public ActorBase
{
private:
	SingleActorRender* m_Dask;

public:
	StoreDask();
	~StoreDask();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


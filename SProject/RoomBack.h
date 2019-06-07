#pragma once
#include "ActorBase.h"

class SingleActorRender;
class RoomBack :	public ActorBase
{
private:
	SingleActorRender* m_RoomBack;

public:
	RoomBack();
	~RoomBack();

public:
	SingleActorRender* GetRoomBack()
	{
		return m_RoomBack;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


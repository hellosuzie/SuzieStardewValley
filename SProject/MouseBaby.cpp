#include "stdafx.h"
#include "MouseBaby.h"
#include "ActorCollision.h"
#include "EnterMgr.h"

MouseBaby::MouseBaby()
{
}


MouseBaby::~MouseBaby()
{
}

void MouseBaby::Init()
{
	CameraMode(false);
	ActorCollision* Baby = MakeCollision(L"Mouse", { 1, 1 });
}

void MouseBaby::PrevUpdate()
{
}

void MouseBaby::Update()
{
	m_Pos = MOUSEF;
}

void MouseBaby::LaterUpdate()
{
}

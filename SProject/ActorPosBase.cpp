#include "stdafx.h"
#include "ActorPosBase.h"
#include "ActorBase.h"

ActorPosBase::ActorPosBase() : m_Size(FSIZE::Zero), m_Pivot(FPOS::Zero)
{
}


ActorPosBase::~ActorPosBase()
{
}

bool ActorPosBase::DeathCheck()
{
	return true == UpdateBase::DeathCheck() || true == Actor()->DeathCheck();
}

bool ActorPosBase::UpdateCheck()
{
	return true == UpdateBase::UpdateCheck() && true == Actor()->UpdateCheck();
}

FPOS ActorPosBase::PivotPos() const
{
	return Actor()->Pos() + m_Pivot;
}

FPOS ActorPosBase::ScreenPos()
{
	return Actor()->ScreenPos() + m_Pivot;
}

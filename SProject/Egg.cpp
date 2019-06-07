#include "stdafx.h"
#include "Egg.h"
#include "SingleActorRender.h"
#include "ActorCollision.h"
#include "ResourceMgr.h"
#include "Animal.h"
#include "SoundPlayer.h"
#include "BoomEffect.h"

Egg::Egg(int _Type) : BabyTimer(10.0f), DBabyTimer(11.0f)
{
	m_EggType = (EGGTYPE)_Type;
}

Egg::~Egg()
{
}

void Egg::Init()
{
	switch (m_EggType)
	{
	case Egg::Chicken:
		m_EggRender = MakeRender<SingleActorRender>();
		m_EggRender->Size({ 54, 54 });
		m_EggRender->SetSprite(L"Egg.bmp", 0);
		break;
	case Egg::Duck:
		m_EggRender = MakeRender<SingleActorRender>();
		m_EggRender->Size({ 54, 54 });
		m_EggRender->SetSprite(L"Egg.bmp", 1);
		break;
	default:
		break;
	}

	m_EggColl = MakeCollision(L"Egg", FSIZE(50, 50));

	BabyChickenSp = GETSOUND;
	BabyDuckSp = GETSOUND;
}

void Egg::Update()
{
	if (Egg::Chicken == m_EggType)
	{
		if (true == BabyTimer.TimeCheck())
		{
			BabyChickenSp->NewSoundPlay(L"BabyChicken.wav");

			Animal* BabyChickenActor = Parent()->MakeActor<Animal>(4);
			BabyChickenActor->SetAnimalTile(Animal::TempCoopTile);
			BabyChickenActor->Pos(m_Pos);

			BoomEffect* CBoom = Parent()->MakeActor<BoomEffect>();
			CBoom->Pos(m_Pos);

			this->Die();
		}
	}	
	if (Egg::Duck == m_EggType)
	{
		if (true == DBabyTimer.TimeCheck())
		{
			BabyDuckSp->NewSoundPlay(L"BabyDuck.wav");

			Animal* BabyDuckActor = Parent()->MakeActor<Animal>(5);
			BabyDuckActor->SetAnimalTile(Animal::TempCoopTile);
			BabyDuckActor->Pos(m_Pos);

			BoomEffect* DBoom = Parent()->MakeActor<BoomEffect>();
			DBoom->Pos(m_Pos);

			this->Die();
		}
	}

}

void Egg::CollStart(ActorCollision * _This, ActorCollision * _Other)
{
}

void Egg::CollStay(ActorCollision * _This, ActorCollision * _Other)
{
}

void Egg::CollExit(ActorCollision * _This, ActorCollision * _Other)
{
}

#pragma once
#include "ActorBase.h"
#include "TimeHelper.h"

class SoundPlayer;
class CoopTile;
class TileActorRender;
class ActorCollision;
class Player;
class AniActorRender;
class Animal :	public ActorBase
{
	enum ANIMALTYPE
	{
		Rabbit = 1,
		Duck,
		Chicken,
		BabyChicken,
		BabyDuck,
		Cow,
		Goet,
		Sheep,
		ATypeMax
	};

	enum ANIMALDIR
	{
		Up,
		Down,
		Left,
		Right,
		ADirMax
	};

	enum ANIMALSTATE
	{
		Stay,
		Move,
		Sit,
		AStateMax
	};

private:
	SoundPlayer* ChickenSp;
	SoundPlayer* DuckSp;
	SoundPlayer* CowSp;
	SoundPlayer* GoetSp;

public:
	static TileActorRender* TempCoopTile;

public:
	static int ChickenCount;
	static int DuckCount;
	static int TempChicken;
	static int TempDuck;

	static int BabyChickenCount;
	static int BabyDuckCount;

	static int BabyEggCount;
	static int DBabyEggCount;

public:
	static bool ChickenEggCheck;
	static bool DuckEggCheck;

	bool Test;

private:
	float m_AnimalSpeed;
	float m_RSpeed;
	float m_DSpeed;
	float m_CSpeed;
	float m_BCSpeed;
	float m_BDSpeed;
	float m_CGSpeed;

	float m_UTemp;
	float m_DTemp;
	float m_RTemp;
	float m_LTemp;

	float TempTime;
	float m_BabyChickenCheck;
	float m_BabyDuckCheck;

	TimeHelper m_StayToMoveTimer;
	TimeHelper m_MoveToSitTimer;
	TimeHelper m_SitToStayTimer;

private:
	AniActorRender* m_AnimalAni;

	ANIMALTYPE m_AnimalType;
	ANIMALDIR m_AnimalDir;
	ANIMALSTATE m_AnimalState;

	std::wstring m_AnimalDirArr[ADirMax];
	std::wstring m_AnimalAniArr[AStateMax];

	ActorCollision* UColl;
	ActorCollision* DColl;
	ActorCollision* LColl;
	ActorCollision* RColl;

private:
	TileActorRender* m_AnimalTile;
	int m_RDir;
	int m_DDir;
	int m_CDir;
	int m_BCDir;
	int m_BDDir;
	float m_Time;

private:
	FPOS m_ChickenEggPos;
	FPOS m_DuckEggPos;

public:
	Animal(int _Type);
	~Animal();

public:
	void SetAnimalTile(TileActorRender* _AnimalTile)
	{
		m_AnimalTile = _AnimalTile;
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

public:
	void ChangeAnimalState(ANIMALDIR _Dir, ANIMALSTATE _State);

private:
	void AStay();
	void AMove();
	void ASit();

public:
	void CollStart(ActorCollision* _This, ActorCollision* _Other);
	void CollStay(ActorCollision* _This, ActorCollision* _Other);
	void CollExit(ActorCollision* _This, ActorCollision* _Other);

};


#pragma once
#include "ActorBase.h"
#include "TimeHelper.h"

class AniActorRender;
class EndCat :
	public ActorBase
{
private:
	AniActorRender* m_EndCatRender;
	TimeHelper CatTime;
	
	static bool CTest;
	static bool LetterCheck;

public:
	EndCat();
	~EndCat();

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


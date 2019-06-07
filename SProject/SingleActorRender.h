#pragma once
#include "ActorRender.h"

class GameSprite;
class SingleActorRender :	public ActorRender
{
private:
	GameSprite* m_Sprite;

public:
	SingleActorRender();
	~SingleActorRender();

public:
	GameSprite* Sprite()
	{
		return m_Sprite;
	}

public:
	void SetSprite(const WCHAR* _ImageName);
	void SetSprite(const WCHAR* _ImageName, size_t _Index);
	void Render() override;
};


#pragma once
#include "ActorBase.h"
#include "ItemMgr.h"

class SingleActorRender;
class HandItem :
	public ActorBase
{
private:
	SingleActorRender* m_HandRender;
	ItemMgr::ItemInfo* m_PlayerHandItem;

public:
	HandItem();
	~HandItem();

public:
	inline ItemMgr::ItemInfo* PlayerHandItem()
	{
		return m_PlayerHandItem;
	}
	inline void PlayerHandItem(ItemMgr::ItemInfo* _Item)
	{
		m_PlayerHandItem = _Item;
	}
	inline SingleActorRender* HandRender()
	{
		return m_HandRender;
	}
	bool HandItemCheck()
	{
		if (nullptr == m_PlayerHandItem)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

public:
	void Init() override;
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;
};


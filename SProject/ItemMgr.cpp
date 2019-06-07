#include "stdafx.h"
#include "ItemMgr.h"
#include "GameMultiSprite.h"
#include "ResourceMgr.h"

//대입연산자재지정해주기

ItemMgr::ItemInfo::ItemInfo(const WCHAR* _SpriteName
	, const WCHAR* _ItemName
	, size_t _Type
	, size_t _SpriteNum
	, size_t _ItemCount
	, size_t _Price
	, bool _Eat
	, size_t _EatCount
	, size_t _Att)
	: m_SpriteName(_SpriteName)
	, m_ItemName(_ItemName)
	, m_ItemType(_Type)
	, m_SpriteNum(_SpriteNum)
	, m_ItemCount(_ItemCount)
	, m_Price(_Price)
	, m_Eat(_Eat)
	, m_EatCount(_EatCount)
	, m_Att(_Att)
{
}

ItemMgr::ItemInfo::~ItemInfo()
{
}

ItemMgr::ItemMgr()
{
	ItemInit();
}


ItemMgr::~ItemMgr()
{
	std::map<std::wstring, ItemInfo*>::iterator StartIter = m_ItemMap.begin();
	std::map<std::wstring, ItemInfo*>::iterator EndIter = m_ItemMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}
}

ItemMgr::ItemInfo* ItemMgr::FindItem(const WCHAR * _ItemName)
{
	std::map<std::wstring, ItemInfo*>::iterator FindIter = m_ItemMap.find(_ItemName);
	if (m_ItemMap.end() == FindIter)
	{
		return nullptr;
	}
	return FindIter->second;
}

ItemMgr::ItemInfo* ItemMgr::MakeItem(const WCHAR * _SpriteName
	, const WCHAR * _ItemName
	, size_t _Type
	, size_t _SpriteNum
	, size_t _ItemCount
	, size_t _Price
	, bool _Eat
	, size_t _EatCount
	, size_t _Att)
{
	ItemInfo* FindItemInfo = FindItem(_ItemName);
	//아이템 있으면 리턴
	if (nullptr != FindItemInfo)
	{
		return FindItemInfo;
	}
 
	GameMultiSprite* Multi = RES.FindMultiSprite(_SpriteName);
	if (nullptr == Multi)
	{
		Tassert(true);
		return nullptr;
	}

	ItemInfo* NewItemInfo = new ItemInfo(_SpriteName, _ItemName, _Type, _SpriteNum, _ItemCount, _Price, _Eat, _EatCount, _Att);
	m_ItemMap.insert(std::map<std::wstring, ItemInfo*>::value_type(_ItemName, NewItemInfo));
	return NewItemInfo;
}

ItemMgr::ItemInfo * ItemMgr::GetItem(const WCHAR * _ItemName)
{
	ItemInfo* FindItemInfo = FindItem(_ItemName);
	if (nullptr == FindItemInfo)
	{
		Tassert(true);
		return nullptr;
	}
	return FindItemInfo;
}

ItemMgr::ItemInfo * ItemMgr::GetItem(int _ItemType, int _ItemCount)
{
	StartIter = m_ItemMap.begin();
	EndIter = m_ItemMap.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (_ItemType == StartIter->second->m_ItemType)
		{
			if (_ItemCount == StartIter->second->m_ItemCount)
			{
				ItemInfo* FindItemInfo = FindItem(StartIter->first.c_str());
				return FindItemInfo;
			}
		}
	}
	Tassert(true);
	return nullptr;
}

void ItemMgr::ItemInit()
{
	//스프라이트이름, 아이템이름, 타입, 스프라이트넘버, 아이템순서, 가격, 먹을수있느냐, 채워지는 에너지, 공격력

	//Seed
	MakeItem(L"Seed.bmp", L"ParsnipSeed", Seed, 0, 0, 20);
	MakeItem(L"Seed.bmp", L"GreenbeanSeed", Seed, 1, 1, 60);
	MakeItem(L"Seed.bmp", L"CauliflowerSeed", Seed, 2, 2, 80);
	MakeItem(L"Seed.bmp", L"PotatoSeed", Seed, 3, 3, 50);
	MakeItem(L"Seed.bmp", L"GarlicSeed", Seed, 4, 4, 40);
	MakeItem(L"Seed.bmp", L"KaleSeed", Seed, 5, 5, 70);
	MakeItem(L"Seed.bmp", L"RhubarbSeed", Seed, 6, 6, 100);
	MakeItem(L"Seed.bmp", L"MelonSeed", Seed, 7, 7, 80);
	MakeItem(L"Seed.bmp", L"TomatoSeed", Seed, 9, 8, 50);
	MakeItem(L"Seed.bmp", L"BlueberrySeed", Seed, 10, 9, 80);
	MakeItem(L"Seed.bmp", L"HotpepperSeed", Seed, 11, 10, 40);
	MakeItem(L"Seed.bmp", L"WheatSeed", Seed, 12, 11, 10);
	MakeItem(L"Seed.bmp", L"RadishSeed", Seed, 13, 12, 40);
	MakeItem(L"Seed.bmp", L"RedcabbageSeed", Seed, 14, 13, 100);
	MakeItem(L"Seed.bmp", L"StarfruitSeed", Seed, 15, 14, 400);
	MakeItem(L"Seed.bmp", L"CornSeed", Seed, 16, 15, 150);
	MakeItem(L"Seed.bmp", L"EggplantSeed", Seed, 18, 16, 20);
	MakeItem(L"Seed.bmp", L"ArtichokeSeed", Seed, 19, 17, 30);
	MakeItem(L"Seed.bmp", L"PumpkinSeed", Seed, 20, 18, 100);
	MakeItem(L"Seed.bmp", L"BokchoySeed", Seed, 21, 19, 50);
	MakeItem(L"Seed.bmp", L"YamSeed", Seed, 22, 20, 60);
	MakeItem(L"Seed.bmp", L"CoffeebeanSeed", Seed, 23, 21, 2500);
	MakeItem(L"Seed.bmp", L"BeetSeed", Seed, 24, 22, 20);
	MakeItem(L"Seed.bmp", L"AncientfruitSeed", Seed, 25, 23, 3000);
	MakeItem(L"Spring.bmp", L"StrawberrySeed", Seed, 496, 24, 100);
	MakeItem(L"Seed.bmp", L"GrapeSeed", Seed, 29, 25, 60);
	MakeItem(L"Seed.bmp", L"HopsSeed", Seed, 30, 26, 60);

	//Crop
	MakeItem(L"Spring.bmp", L"Parsnip", Crop, 24, 0, 35, true, 25);
	MakeItem(L"Spring.bmp", L"Greenbean", Crop, 188, 1, 40, true, 25);
	MakeItem(L"Spring.bmp", L"Cauliflower", Crop, 190, 2, 175, true, 75);
	MakeItem(L"Spring.bmp", L"Potato", Crop, 192, 3, 80, true, 25);
	MakeItem(L"Spring.bmp", L"Garlic", Crop, 248, 4, 60, true, 20);
	MakeItem(L"Spring.bmp", L"Kale", Crop, 250, 5, 110, true, 50);
	MakeItem(L"Spring.bmp", L"Rhubarb", Crop, 252, 6, 220, true, 45);
	MakeItem(L"Spring.bmp", L"Melon", Crop, 254, 7, 250, true, 113);
	MakeItem(L"Spring.bmp", L"Tomato", Crop, 256, 8, 60, true, 20);
	MakeItem(L"Spring.bmp", L"Blueberry", Crop, 258, 9, 50, true, 25);
	MakeItem(L"Spring.bmp", L"Hotpepper", Crop, 260, 10, 40, true, 13);
	MakeItem(L"Spring.bmp", L"Wheat", Crop, 262, 11, 25, false);
	MakeItem(L"Spring.bmp", L"Radish", Crop, 264, 12, 90, true, 45);
	MakeItem(L"Spring.bmp", L"Redcabbage", Crop, 266, 13, 260, true, 75);
	MakeItem(L"Spring.bmp", L"Starfruit", Crop, 268, 14, 750, true, 125);
	MakeItem(L"Spring.bmp", L"Corn", Crop, 270, 15, 50, true, 25);
	MakeItem(L"Spring.bmp", L"Eggplant", Crop, 272, 16, 60, true, 20);
	MakeItem(L"Spring.bmp", L"Artichoke", Crop, 274, 17, 160, true, 30);
	MakeItem(L"Spring.bmp", L"Pumpkin", Crop, 276, 18, 320, true, 60);
	MakeItem(L"Spring.bmp", L"Bokchoy", Crop, 278, 19, 80, true, 25);
	MakeItem(L"Spring.bmp", L"Yam", Crop, 280, 20, 160, true, 45);
	MakeItem(L"Spring.bmp", L"Coffeebean", Crop, 282, 21, 15, true, 15);
	MakeItem(L"Spring.bmp", L"Beet", Crop, 284, 22, 100, true, 30);
	MakeItem(L"Spring.bmp", L"Ancientfruit", Crop, 454, 23, 550, true, 100);
	MakeItem(L"Spring.bmp", L"Strawberry", Crop, 400, 24, 120, true, 50);
	MakeItem(L"Spring.bmp", L"Grape", Crop, 398, 25, 80, true, 38);
	MakeItem(L"Spring.bmp", L"Hops", Crop, 304, 26, 25, true, 45);

	//Tool
	MakeItem(L"MiniTool.bmp", L"Axe", Tool, 2, 0, 10);
	MakeItem(L"MiniTool.bmp", L"Hoe", Tool, 0, 1, 10);
	MakeItem(L"MiniTool.bmp", L"Pick", Tool, 1, 2, 10);
	MakeItem(L"MiniTool.bmp", L"Watercan", Tool, 3, 3, 10);

	//스프라이트이름, 아이템이름, 타입, 스프라이트넘버, 아이템순서, 가격, 먹을수있느냐, 채워지는 에너지, 공격력
	//Weapon
	MakeItem(L"weapons.bmp", L"Sickle", Weapon, 47, 0, 0, false, 0, 1);
	MakeItem(L"weapons.bmp", L"Rustysword", Weapon, 0, 1, 50, false, 0, 5);
	MakeItem(L"weapons.bmp", L"Rapier", Weapon, 49, 2, 750, false, 0, 25);
	MakeItem(L"weapons.bmp", L"Piratesword", Weapon, 43, 3, 850, false, 0, 14);
	MakeItem(L"weapons.bmp", L"Galaxysword", Weapon, 4, 4, 5000, false, 0, 80);
	MakeItem(L"weapons.bmp", L"Claymore", Weapon, 10, 5, 2000, false, 0, 32);

	//Rock
	MakeItem(L"Spring.bmp", L"RockOne", Rock, 390, 0, 10);
	MakeItem(L"Spring.bmp", L"RockTwo", Rock, 390, 1, 10);
	MakeItem(L"Spring.bmp", L"Emerald", Rock, 60, 2, 10);
	MakeItem(L"Spring.bmp", L"Aquamarine", Rock, 62, 3, 10);
	MakeItem(L"Spring.bmp", L"Ruby", Rock, 64, 4, 10);
	MakeItem(L"Spring.bmp", L"Topaz", Rock, 68, 5, 10);
	MakeItem(L"Spring.bmp", L"Diamond", Rock, 72, 6, 10);

	//Wood
	MakeItem(L"Spring.bmp", L"Wood", Woods, 388, 0, 10);

	//Product
	MakeItem(L"Milk.bmp", L"Milk", Product, 0, 0, 125);
	MakeItem(L"Milk.bmp", L"GoetMilk", Product, 1, 1, 225);
	MakeItem(L"Milk.bmp", L"Wool", Product, 2, 2, 340);

}


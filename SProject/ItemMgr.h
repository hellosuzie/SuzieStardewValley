#pragma once

class ItemMgr
{
public:
	static ItemMgr& Inst()
	{
		static ItemMgr Item = ItemMgr();
		return Item;
	}
	
public:
	enum ITEMTYPE
	{
		Seed,
		Crop,
		Tool,
		Weapon,
		Rock,
		Woods,
		Product,
		TypeMax
	};



	class ItemInfo
	{
	public:
		//�̹��� �̸�
		std::wstring m_SpriteName;
		std::wstring m_ItemName;
		//����
		size_t m_ItemType;
		//��������Ʈ�߿� ���° �̹����ΰ�
		size_t m_SpriteNum;
		//�����߿� ���°�ΰ�
		size_t m_ItemCount;
		//����
		size_t m_Price;

		//�������ִ��� ������
		bool m_Eat;
		//��������
		size_t m_EatCount;

		//���ݷ�
		size_t m_Att;

	public:
		ItemInfo(const WCHAR* _SpriteName
			, const WCHAR* _ItemName
			, size_t _Type
			, size_t _SpriteNum
			, size_t _ItemCount
			, size_t _Price
			, bool _Eat
			, size_t _EatCount
			, size_t _Att);
		~ItemInfo();
	};

private:
	std::map<std::wstring, ItemInfo*> m_ItemMap;
	std::map<std::wstring, ItemInfo*>::iterator StartIter;
	std::map<std::wstring, ItemInfo*>::iterator EndIter;

private:
	ItemMgr();
	~ItemMgr();

public:
	void ItemInit();

	ItemInfo* FindItem(const WCHAR* _ItemName);
	ItemInfo* MakeItem(const WCHAR* _SpriteName, const WCHAR* _ItemName
		, size_t _Type, size_t _SpriteNum, size_t _ItemCount, size_t _Price
		, bool _Eat = false, size_t _EatCount = 0, size_t _Att = 0);

	ItemInfo* GetItem(const WCHAR* _ItemName);
	ItemMgr::ItemInfo * GetItem(int _ItemType, int _ItemNum);

public:
	enum ITEM_CROPS_SEED
	{
		ParsnipSeed,
		GreenbeanSeed,
		CauliflowerSeed,
		PotatoSeed,
		GarlicSeed,
		KaleSeed,
		RhubarbSeed,
		MelonSeed,
		TomatoSeed,
		BlueberrySeed,
		HotpepperSeed,
		WheatSeed,
		RadishSeed,
		RedcabbageSeed,
		StarfruitSeed,
		CornSeed,
		EggplantSeed,
		ArtichokeSeed,
		PumpkinSeed,
		BokchoySeed,
		YamSeed,
		CoffeebeanSeed,
		BeetSeed,
		AncientfruitSeed,
		StrawberrySeed,
		GrapeSeed,
		HopsSeed,
		Seedmax
	};

	enum ITEM_CROPS
	{
		Parsnip,
		Greenbean,
		Cauliflower,
		Potato,
		Garlic,
		Kale,
		Rhubarb,
		Melon,
		Tomato,
		Blueberry,
		Hotpepper,
		Wheat,
		Radish,
		Redcabbage,
		Starfruit,
		Corn,
		Eggplant,
		Artichoke,
		Pumpkin,
		Bokchoy,
		Yam,
		Coffeebean,
		Beet,
		Ancientfruit,
		Strawberry,
		Grape,
		Hops,
		Cropmax
	};

	enum ITEM_TOOL
	{
		Axe,
		Hoe,
		Pick,
		Watercan,
		ToolMax
	};

	enum ITEM_WEAPON
	{
		Sickle,
		Rustysword,
		Rapier,
		Piratesword,
		Galaxysword,
		Claymore,
		WeaponMax
	};

	enum ITEM_ROCK
	{
		Rockone,
		Rocktwo,
		Emerald,
		Aquamarine,
		Ruby,
		Topaz,
		Diamond,
		RockMax
	};

	enum ITEM_WOODS
	{
		Wood,
		WoodMax
	};

	enum ITEM_PRODUCT
	{
		Milk,
		GoetMilk,
		Wool,
		ProductMax
	};
};


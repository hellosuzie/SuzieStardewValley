#pragma once
#include "ActorBase.h"
#include "ItemMgr.h"
#include <vector>
#include <map>

class SoundPlayer;
class ActorCollision;
class SecondNumberActor;
class NumberActor;
class HandItem;
class QuickInButton;
class MainInButton;
class SelectRender;
class QuickInvenBack;
class MainInvenBack;
class HPBar;
class Clock;
class SingleActorRender;
class TileActorRender;
class AniActorRender;
class Player :	public ActorBase
{
public:
	static Player* CurPlayer;

public:
	enum PLAYERSTATE
	{
		STAY,
		PICK,
		WALK,
		PICKWALK,
		EAT,
		TOOL,
		WEAPON,
		WATER,
		RIDE,
		MAX
	};

	enum PLAYERTOOL
	{
		NONE,
		AXE,
		HOE,
		PICKAXE,
		SICKLE,
		WATERCAN,
		RUSTYSWORD,
		RAPIER,
		PIRATESWORD,
		GALAXYSWORD,
		CLAYMORE,
		HORSE,
		ITEMMAX
	};

private:
	std::wstring m_PlayerDir;
	std::wstring m_PlayerAniName[MAX];
	std::wstring m_ItemAniName[ITEMMAX];

private:
	int m_Energy;
	int m_Money;
	float m_Speed;

private:
	HandItem* m_MainHandItem;

private:
	AniActorRender* m_MainPlayerRender;
	AniActorRender* m_MainItemRender;

private:
	HPBar* m_HpBar;
	Clock* m_Clock;

private:
	FRECT m_BackGround;

	FPOS m_BackStartPos;
	FPOS m_BackEndPos;

private:
	IPOS m_RectPos;

public:
	NumberActor* m_NActor;
	SecondNumberActor* m_NActor2;

private:
	SelectRender* m_SelectRenderer;
	TileActorRender* m_PlayerTile;

private:
	ActorCollision* m_LColl;
	ActorCollision* m_LSColl;
	ActorCollision* m_RColl;
	ActorCollision* m_RSColl;
	ActorCollision* m_UColl;
	ActorCollision* m_USColl;
	ActorCollision* m_DColl;
	ActorCollision* m_DSColl;

	SoundPlayer* PlayerSp;

public:
	Player();
	~Player();

public:
	inline void MainHandItem(HandItem* _Item)
	{
		m_MainHandItem = _Item;
	}
	inline HandItem* MainHandItem()
	{
		return m_MainHandItem;
	}
	inline const WCHAR* PlayerDir()
	{
		m_PlayerDir.c_str();
	}
	inline void PlayerDir(std::wstring _Dir)
	{
		m_PlayerDir = _Dir;
	}
	inline void SetPlayerTile(TileActorRender* _Tile)
	{
		m_PlayerTile = _Tile;
	}

	inline IPOS RectPos()
	{
		return m_RectPos;
	}
	inline size_t PlayerEnergy()
	{
		return m_Energy;
	}
	inline size_t PlayerMoney()
	{
		return m_Money;
	}
	inline void PlayerEnergy(int _En)
	{
		if (0 >= m_Energy)
		{
			m_Energy = 0;
			return;
		}
		m_Energy = _En;
	}
	inline bool ReducePlayerEnergy(int _En)
	{
		m_Energy -= _En;
		if (0 >= m_Energy)
		{
			m_Energy = 0;
			return false;
		}
		return true;
	}
	inline bool IncreasePlayerEnergy(int _En)
	{
		if (200 == m_Energy)
		{
			m_Energy = 200;
			return false;
		}
		if (200 < m_Energy + _En)
		{
			m_Energy = 200;
			return true;
		}
		m_Energy += _En;
		return true;
	}
	inline void PlayerMoney(int _Money)
	{
		m_Money = _Money;
	}
	inline bool ReducePlayerMoney(int _Money)
	{
		m_Money -= _Money;
		if (0 >= m_Money)
		{
			m_Money = 0;
			return false;
		}
		return true;
	}
	inline bool IncreasePlayerMoney(int _Money)
	{
		m_Money += _Money;
		return true;
	}
	inline AniActorRender* MainPlayerRender()
	{
		return m_MainPlayerRender;
	}
	inline void BackRect(FRECT _Rect)
	{
		m_BackGround = _Rect;
	}
	inline PLAYERSTATE PlayerState()
	{
		return m_PlayerState;
	}
	inline PLAYERTOOL PlayerItem()
	{
		return m_PlayerItem;
	}
	inline void PlayerItem(PLAYERTOOL _Tool)
	{
		m_PlayerItem = _Tool;
	}
	inline AniActorRender* MainItem()
	{
		return m_MainItemRender;
	}

public:
	static IPOS WorldPlayerIndex(FPOS _ScreenPos);
	static FPOS IndexWorldPos(IPOS _Index);
	void Init() override;

private:
	void PrevUpdate() override;
	void Update() override;
	void LaterUpdate() override;

public:
	void DebugRender() override;
	//void CollStart(ActorCollision* _This, ActorCollision* _Other) override;

public:
	void OtherCollStart(ActorCollision* _This, ActorCollision* _Other);
	void OtherCollStay(ActorCollision* _This, ActorCollision* _Other);
	void OtherCollExit(ActorCollision* _This, ActorCollision* _Other);

private:
	void StateUpdate();
	void SelectRect();
	void DirCheck();
	void TimeBooster();

public:
	void SetMainHandItem(ItemMgr::ItemInfo* _Item);

	void EatWork(int _InvenNum);

//////////////////////////////////////////////////FSM
private:
	PLAYERSTATE m_PlayerState;
	PLAYERTOOL m_PlayerItem;

public:
	void ChangePlayerAni(PLAYERSTATE _State);
	void ChangePlayerAni(PLAYERSTATE _State, PLAYERTOOL _Tool);
	void ChangeState(PLAYERSTATE _State);
	void ChangeState(PLAYERSTATE _State, PLAYERTOOL _Tool);
	void MakePlayerAni();
	void PlayerMove();

private:
	void Stay();
	void Pick();
	void Walk();
	void Pickwalk();
	void Eat();
	void Tool();
	void Weapon();
	void Water();
	void Ride();

//////////////////////////////////////////////////Inven
private:
	//배경
	MainInvenBack* m_MainInven;
	QuickInvenBack* m_QuickInven;

	bool m_InvenCheck;

	//인벤토리 버튼 저장하는 벡터 
	std::vector<MainInButton*> m_MainInButtonVec;
	std::vector<QuickInButton*> m_QuickInButtonVec;

	static int m_StartCount;
	static int m_ChangeCount;
	static bool m_SwapCheck;

public:
	size_t ItemVecSize()
	{
		return m_MainInButtonVec.size();
	}

public:
	//static void __stdcall MainInvenZero(void *);

public:
	void OpenMainInven();
	void CloseMainInven();

private:
	void MakeInven();
	void MakeQuick();
	bool InvenSwap(int _Start, int _Next);

public:
	bool PutItem(const WCHAR * _ItemName, int _Num);
	bool PutItem(ItemMgr::ItemInfo* _ItemInfo);
	bool PutItem(const WCHAR* _ItemName);

	bool RemoveItem(size_t _Num);
	ItemMgr::ItemInfo* ReturnItemInfo(size_t _InvenCount);

	void SetItemClickFunc(ItemMgr::ItemInfo* _Item, size_t _Num);
	static void InvenSwapCheck();

	//////////////Products
	static void __stdcall Milk(void *);
	static void __stdcall GoetMilk(void *);
	static void __stdcall Wool(void *);

	//////////////Woods
	static void __stdcall Wood(void *);

	//////////////Rocks
	static void __stdcall Rockone(void *);
	static void __stdcall Rocktwo(void *);
	static void __stdcall Emerald(void *);
	static void __stdcall Aquamarine(void *);
	static void __stdcall Ruby(void *);
	static void __stdcall Topaz(void *);
	static void __stdcall Diamond(void *);

	//////////////Weapons
	static void __stdcall Sickle(void *);
	static void __stdcall Rustysword(void *);
	static void __stdcall Rapier(void *);
	static void __stdcall Piratesword(void *);
	static void __stdcall Galaxysword(void *);
	static void __stdcall Claymore(void *);

	//////////////Tools
	static void __stdcall Axe(void *);
	static void __stdcall Hoe(void *);
	static void __stdcall Pick(void *);
	static void __stdcall Watercan(void *);

	//////////////Crops
	static void __stdcall Parsnip(void *);
	static void __stdcall Greenbean(void *);
	static void __stdcall Cauliflower(void *);
	static void __stdcall Potato(void *);
	static void __stdcall Garlic(void *);
	static void __stdcall Kale(void *);
	static void __stdcall Rhubarb(void *);
	static void __stdcall Melon(void *);
	static void __stdcall Tomato(void *);
	static void __stdcall Blueberry(void *);
	static void __stdcall Hotpepper(void *);
	static void __stdcall Wheat(void *);
	static void __stdcall Radish(void *);
	static void __stdcall Redcabbage(void *);
	static void __stdcall Starfruit(void *);
	static void __stdcall Corn(void *);
	static void __stdcall Eggplant(void *);
	static void __stdcall Artichoke(void *);
	static void __stdcall Pumpkin(void *);
	static void __stdcall Bokchoy(void *);
	static void __stdcall Yam(void *);
	static void __stdcall Coffeebean(void *);
	static void __stdcall Beet(void *);
	static void __stdcall Ancientfruit(void *);
	static void __stdcall Strawberry(void *);
	static void __stdcall Grape(void *);
	static void __stdcall Hops(void *);

	//////////////Seed
	static void __stdcall ParsnipSeed(void*);
	static void __stdcall GreenbeanSeed(void *);
	static void __stdcall CauliflowerSeed(void *);
	static void __stdcall PotatoSeed(void *);
	static void __stdcall GarlicSeed(void *);
	static void __stdcall KaleSeed(void *);
	static void __stdcall RhubarbSeed(void *);
	static void __stdcall MelonSeed(void *);
	static void __stdcall TomatoSeed(void *);
	static void __stdcall BlueberrySeed(void *);
	static void __stdcall HotpepperSeed(void *);
	static void __stdcall WheatSeed(void *);
	static void __stdcall RadishSeed(void *);
	static void __stdcall RedcabbageSeed(void *);
	static void __stdcall StarfruitSeed(void *);
	static void __stdcall CornSeed(void *);
	static void __stdcall EggplantSeed(void *);
	static void __stdcall ArtichokeSeed(void *);
	static void __stdcall PumpkinSeed(void *);
	static void __stdcall BokchoySeed(void *);
	static void __stdcall YamSeed(void *);
	static void __stdcall CoffeebeanSeed(void *);
	static void __stdcall BeetSeed(void *);
	static void __stdcall AncientfruitSeed(void *);
	static void __stdcall StrawberrySeed(void *);
	static void __stdcall GrapeSeed(void *);
	static void __stdcall HopsSeed(void *);
};


#pragma once
#include "GameState.h"
#include "TimeHelper.h"
//나무, 돌, 땅, 식물

class BarnRender;
class SoundPlayer;
class CoopRender;
class Cat;
class ItemMgr;
class HarvEffect;
class Rocks;
class TreeBot;
class TreeTop;
class Crops;
class Soil;
class Player;
class FarmBack;
class FarmTile;
class FarmState :
	public GameState
{
private:
	Player* m_MainPlayer;
	FarmBack* m_FarmBack;
	FarmTile* m_FarmTile;

	HarvEffect* m_HEffect;

	IPOS m_RectPos;
	static int AxeCount;

	Cat* Catt;
	FPOS StartPlayerPos;

	SoundPlayer* FarmSp;
	SoundPlayer* FarmSp2;

public:
	static CoopRender* CRender;
	static BarnRender* BRender;

private:
	std::map<__int64, Soil*> m_SoilMap;
	std::map<__int64, Soil*>::iterator m_SFindIter;

	std::map<__int64, Soil*> m_WaterMap;
	std::map<__int64, Soil*>::iterator m_WFindIter;

	std::map<__int64, Crops*> m_CropsMap;
	std::map<__int64, Crops*>::iterator m_CFindIter;

	std::map<__int64, TreeBot*> m_TreeBotMap;
	std::map<__int64, TreeBot*>::iterator m_TBFindIter;
	std::map<__int64, TreeTop*> m_TreeTopMap;
	std::map<__int64, TreeTop*>::iterator m_TTFindIter;

	std::map<__int64, Rocks*> m_RockMap;
	std::map<__int64, Rocks*>::iterator m_RFindIter;

public:
	FarmState();
	~FarmState();

public:
	void ChangeBegin() override;
	void ChangeEnd() override;

public:
	void StateInit() override;
	void StateUpdate() override;
	void DebugUpdate() override;

private:
	void RockInit();
	void TreeInit();

private:
	void PlayerAction();
	void PlayerDirCheck(IPOS _Pos);

	void ShakeTree(IPOS _Pos);
	void PickAxeWork(IPOS _Pos);
	void AxeWork(IPOS _Pos);
	void HoeWork(IPOS _Pos);
	void WaterWork(IPOS _Pos);
	void CropsWork(IPOS _Pos, int _InvenNum);
	void Harvest(IPOS _Pos);

};


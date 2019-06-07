#include "stdafx.h"
#include "SCore.h"
#include "EnterMgr.h"
#include "ResourceMgr.h"
#include "ItemMgr.h"

#include "FirstTitle.h"
#include "SecondTitle.h"
#include "TitleState.h"
#include "RoomState.h"
#include "FarmState.h"
#include "TownState.h"
#include "MineState.h"
#include "MineState1.h"
#include "MineState2.h"
#include "MineState3.h"
#include "MineState4.h"
#include "MineState5.h"
#include "StoreState.h"
#include "Town2State.h"
#include "CoopState.h"
#include "BarnState.h"
#include "ManiState.h"
#include "RobinState.h"
#include "EditState.h"
#include "EndState.h"
#include "ReadStream.h"

void SCore::UserInit()
{
	//////////////////////////////////////////////////////Key
	ENTER.MakeKey(L"UP", L'W');
	ENTER.MakeKey(L"DOWN", L'S');
	ENTER.MakeKey(L"LEFT", L'A');
	ENTER.MakeKey(L"RIGHT", L'D');

	ENTER.MakeKey(L"Action", L'F');
	ENTER.MakeKey(L"Enter", L'E');
	ENTER.MakeKey(L"Booster", L'B');
	ENTER.MakeKey(L"Reset", L'N');

	ENTER.MakeKey(L"Prev", L'C');
	ENTER.MakeKey(L"Next", L'V');
	ENTER.MakeKey(L"Save", L'Z');
	ENTER.MakeKey(L"Load", L'X');
	ENTER.MakeKey(L"Erase", L'G');

	ENTER.MakeKey(L"CollDebug", L'P');
	ENTER.MakeKey(L"CountDebug", L'O');

	ENTER.MakeKey(L"MouseLeft", VK_LBUTTON);
	ENTER.MakeKey(L"MouseRight", VK_RBUTTON);
	ENTER.MakeKey(L"ChangeState", L'C');

	ENTER.MakeKey(L"Inven", L'R');

	ENTER.MakeKey(L"TitleState", L'1');
	ENTER.MakeKey(L"RoomState", L'2');
	ENTER.MakeKey(L"FarmState", L'3');
	ENTER.MakeKey(L"TownState", L'4');
	ENTER.MakeKey(L"MineState", L'5');
	ENTER.MakeKey(L"StoreState", L'6');
	ENTER.MakeKey(L"Town2State", L'7');
	ENTER.MakeKey(L"CoopState", L'8');
	ENTER.MakeKey(L"ManiState", L'9');
	ENTER.MakeKey(L"RobinState", L'0');
	ENTER.MakeKey(L"EditState", L'Q');

	//////////////////////////////////////////////////////Path
	RES.MakePath(L"Image");
	RES.MakePath(L"MapData");
	RES.MakePath(L"Sound");

	//////////////////////////////////////////////////////Image
	
	FILE* ImageFile;
	_wfopen_s(&ImageFile, FILEPATH("Image", "0. ImageData.txt"), L"rt");

	char buf[256];
	std::vector<std::string> TestV;
	while (NULL != fgets(buf, sizeof(buf), ImageFile))
	{
		std::string T = buf;
		size_t KeyCount = T.find("-");

		std::string FolderKey = T.substr(0, KeyCount);
		std::wstring WFolderKey;
		WFolderKey.assign(FolderKey.begin(), FolderKey.end());

		std::string Re = T.substr(KeyCount + 1);

		size_t NameCount = Re.find("-");
		std::string Name = Re.substr(0, NameCount);
		std::wstring WName;
		WName.assign(Name.begin(), Name.end());

		std::string RRe = Re.substr(NameCount + 1);
		std::string R = RRe.substr(0, 3);
		std::string G = RRe.substr(3, 3);
		std::string B = RRe.substr(6, 3);

		int RR = atoi(R.c_str());
		int GG = atoi(G.c_str());
		int BB = atoi(B.c_str());

		RES.MakeImage(WFolderKey.c_str(), WName.c_str(), RGB(RR, GG, BB));
	}
	fclose(ImageFile);

	//////////////////////////////////////////////////////Sound

	RES.LoadSound(L"Sound", L"TitleScreen.wav"); //
	RES.LoadSound(L"Sound", L"Room.wav"); //
	RES.LoadSound(L"Sound", L"Farm.wav");//
	RES.LoadSound(L"Sound", L"Town.wav");//
	RES.LoadSound(L"Sound", L"Town2.wav");//
	RES.LoadSound(L"Sound", L"Mines.wav");//
	RES.LoadSound(L"Sound", L"store.wav");//
	RES.LoadSound(L"Sound", L"End.wav"); //
	RES.LoadSound(L"Sound", L"open_door.wav");//
	RES.LoadSound(L"Sound", L"open_store_door.wav");//
	
	RES.LoadSound(L"Sound", L"attack.wav"); //
	RES.LoadSound(L"Sound", L"watercan.wav"); //
	RES.LoadSound(L"Sound", L"eat.wav"); //
	RES.LoadSound(L"Sound", L"Crop.wav"); //
	RES.LoadSound(L"Sound", L"Dig_Ground.wav"); //
	RES.LoadSound(L"Sound", L"Dig_stone.wav"); 
	RES.LoadSound(L"Sound", L"take_tree.wav"); //
	RES.LoadSound(L"Sound", L"take_stone.wav");//
	RES.LoadSound(L"Sound", L"take_crop.wav"); //
	RES.LoadSound(L"Sound", L"Money.wav");//
	RES.LoadSound(L"Sound", L"Mon_dead.wav");//
	RES.LoadSound(L"Sound", L"Fountain.wav");//
	RES.LoadSound(L"Sound", L"Animal.wav");//
	RES.LoadSound(L"Sound", L"Build.wav");//
	RES.LoadSound(L"Sound", L"Chicken.wav");
	RES.LoadSound(L"Sound", L"BabyChicken.wav");
	RES.LoadSound(L"Sound", L"Duck.wav");
	RES.LoadSound(L"Sound", L"BabyDuck.wav");
	RES.LoadSound(L"Sound", L"Goet.wav");
	RES.LoadSound(L"Sound", L"Goet2.wav");
	RES.LoadSound(L"Sound", L"Cow.wav");
	RES.LoadSound(L"Sound", L"Cow2.wav");
	RES.LoadSound(L"Sound", L"Sheep.wav");

	//////////////////////////////////////////////////////Sprite

	//------------MapImage
	RES.MakeSingleSprite(L"TitleBack.bmp");
	RES.MakeSingleSprite(L"RoomMap.bmp");
	RES.MakeSingleSprite(L"FarmMap.bmp");
	RES.MakeSingleSprite(L"TownMap.bmp");
	RES.MakeSingleSprite(L"MineMap.bmp");
	RES.MakeSingleSprite(L"StoreMap.bmp");
	RES.MakeSingleSprite(L"TownMap2.bmp");
	RES.MakeSingleSprite(L"CoopMap.bmp");
	RES.MakeSingleSprite(L"BarnMap.bmp");
	RES.MakeSingleSprite(L"ManiMap.bmp");
	RES.MakeSingleSprite(L"RobinMap.bmp");

	//------------PlayerImage
	RES.MakeMultiSprite(L"1farmer_girl_base.bmp", { 6, 21 });
	RES.MakeMultiSprite(L"2farmer_girl_base.bmp", { 6, 21 });
	RES.MakeMultiSprite(L"1farmer_girl_base_Reverse.bmp", { 6, 21 });
	RES.MakeMultiSprite(L"2farmer_girl_base_Reverse.bmp", { 6, 21 });

	RES.MakeMultiSprite(L"1axe_action.bmp", { 5, 4 });
	RES.MakeMultiSprite(L"2hoe_action.bmp", { 5, 4 });
	RES.MakeMultiSprite(L"3pickaxe_action.bmp", { 5, 4 });
	RES.MakeMultiSprite(L"4sickle_action.bmp", { 5, 4 });
	RES.MakeMultiSprite(L"5watercan_action.bmp", { 5, 4 });
	RES.MakeMultiSprite(L"6rustysword_action.bmp", { 5, 4 });
	RES.MakeMultiSprite(L"7Rapier_action.bmp", { 5, 4 });
	RES.MakeMultiSprite(L"8PirateSword_action.bmp", { 5, 4 });
	RES.MakeMultiSprite(L"9galaxysword_action.bmp", { 5, 4 });
	RES.MakeMultiSprite(L"10claymore_action.bmp", { 5, 4 });

	RES.MakeMultiSprite(L"UpToolBody.bmp", { 5, 1 });
	RES.MakeMultiSprite(L"Walk.bmp", { 5, 4 });
	RES.MakeMultiSprite(L"LeftWeaponBody.bmp", { 6, 1 });
	RES.MakeMultiSprite(L"LeftToolBody.bmp", { 5, 1 });
	RES.MakeMultiSprite(L"UpWaterBody.bmp", { 5, 1 });
	RES.MakeMultiSprite(L"RightWaterBody.bmp", { 5, 1 });
	RES.MakeMultiSprite(L"LeftWaterBody.bmp", { 5, 1 });
	RES.MakeMultiSprite(L"DownWaterBody.bmp", { 5, 1 });

	//------------
	RES.MakeMultiSprite(L"Button.bmp", { 4, 2 });

	RES.MakeSingleSprite(L"SmallCloud.bmp");
	RES.MakeSingleSprite(L"BigCloud.bmp");
	RES.MakeSingleSprite(L"Logo.bmp");

	RES.MakeSingleSprite(L"BedTop.bmp");
	RES.MakeSingleSprite(L"BedBot.bmp");

	RES.MakeMultiSprite(L"cat1.bmp", { 4, 8 });
	RES.MakeMultiSprite(L"cat1.bmp", { 4, 8 });
	RES.MakeMultiSprite(L"Duck.bmp", { 4, 7 });
	RES.MakeMultiSprite(L"Chicken.bmp", { 4, 7 });
	RES.MakeMultiSprite(L"Rabbit.bmp", { 4, 7 });
	RES.MakeMultiSprite(L"BabyDuck.bmp", { 4, 7 });
	RES.MakeMultiSprite(L"BabyChicken.bmp", { 4, 7 });
	RES.MakeMultiSprite(L"BabyRabbit.bmp", { 4, 7 });

	RES.MakeMultiSprite(L"Monster.bmp", { 4, 4 });

	RES.MakeSingleSprite(L"Bar.bmp");
	RES.MakeSingleSprite(L"BigMenu.bmp");
	RES.MakeSingleSprite(L"MiniMenu.bmp");
	RES.MakeMultiSprite(L"Clock.bmp", { 6, 1 });

	RES.MakeMultiSprite(L"TileColor.bmp", {2, 3});
	RES.MakeSingleSprite(L"TileAim.bmp");
	RES.MakeSingleSprite(L"EditState.bmp");
	RES.MakeSingleSprite(L"SelectRender.bmp");

	RES.MakeMultiSprite(L"Crops.bmp", { 16, 19 });
	RES.MakeMultiSprite(L"Soil.bmp", { 2, 1 });
	RES.MakeMultiSprite(L"Rock.bmp", { 7, 1 });
	RES.MakeMultiSprite(L"RockEffect.bmp", { 10, 1 });
	RES.MakeMultiSprite(L"DirtEffect.bmp", { 8, 1 });
	RES.MakeMultiSprite(L"WaterEffect.bmp", { 10, 1 });
	RES.MakeMultiSprite(L"RootTree.bmp", { 3, 1 });
	RES.MakeMultiSprite(L"FullTree.bmp", { 3, 1 });

	RES.MakeSingleSprite(L"StateChange.bmp");
	RES.MakeSingleSprite(L"Full.bmp");

	RES.MakeSingleSprite(L"Haley.bmp");
	RES.MakeSingleSprite(L"Marlon.bmp");
	RES.MakeSingleSprite(L"StoreDask.bmp");
	RES.MakeSingleSprite(L"StoreMenu.bmp");
	RES.MakeSingleSprite(L"Ladder.bmp");
	RES.MakeSingleSprite(L"Info.bmp");

	RES.MakeMultiSprite(L"SeedStore.bmp", { 1, 28 });
	RES.MakeMultiSprite(L"SelectSeedStore.bmp", { 1, 28 });
	RES.MakeMultiSprite(L"WeaponStore.bmp", { 1, 4 });
	RES.MakeMultiSprite(L"SelectWeaponStore.bmp", { 1, 4 });

	RES.MakeMultiSprite(L"FirstTitle.bmp", { 2, 1 });
	RES.MakeMultiSprite(L"SecondTitle.bmp", { 2, 1 });
	RES.MakeMultiSprite(L"ThirdTitle.bmp", { 4, 1 });
	RES.MakeMultiSprite(L"Button.bmp", { 4, 2 });
	RES.MakeMultiSprite(L"Select.bmp", { 2, 1 });
	RES.MakeMultiSprite(L"Seed.bmp", { 9, 4 });
	RES.MakeMultiSprite(L"weapons.bmp", { 8, 7 });
	RES.MakeMultiSprite(L"Spring.bmp", { 24, 34 });
	RES.MakeMultiSprite(L"MiniTool.bmp", { 4, 1 });

	RES.MakeMultiSprite(L"SelectArrow.bmp", { 1, 2 });
	RES.MakeMultiSprite(L"Arrow.bmp", { 1, 2 });
	RES.MakeMultiSprite(L"Ok.bmp", { 2, 1 });
	RES.MakeMultiSprite(L"SelectOk.bmp", { 2, 1 });

	RES.MakeMultiSprite(L"MineNum.bmp", { 6, 1 });
	RES.MakeMultiSprite(L"0.bmp", { 13, 3 });                                                     
	RES.MakeMultiSprite(L"1.bmp", { 13, 3 });
	RES.MakeMultiSprite(L"2.bmp", { 4, 1 });
	RES.MakeMultiSprite(L"3.bmp", { 6, 1 });
	RES.MakeMultiSprite(L"4.bmp", { 7, 1 });
	RES.MakeMultiSprite(L"5.bmp", { 1, 1 });
	RES.MakeMultiSprite(L"6.bmp", { 3, 1 });

	RES.MakeMultiSprite(L"Number.bmp", { 10, 1 });
	RES.MakeSingleSprite(L"BloodNum.bmp");
	RES.MakeMultiSprite(L"MonsterNum.bmp", { 5, 1 });
	RES.MakeMultiSprite(L"SmallNum.bmp", { 10, 1 });
	RES.MakeMultiSprite(L"Day.bmp", { 7, 1 });
	RES.MakeMultiSprite(L"TimeNumber.bmp", { 5, 6 });
	RES.MakeMultiSprite(L"SingleTimeNum.bmp", { 10, 1 });
	
	RES.MakeSingleSprite(L"EBar.bmp");
	RES.MakeSingleSprite(L"Colon.bmp");
	RES.MakeSingleSprite(L"Night.bmp");

	RES.MakeSingleSprite(L"Lamp.bmp");
	RES.MakeSingleSprite(L"HeartTree.bmp");
	RES.MakeSingleSprite(L"FountainBot.bmp");

	RES.MakeMultiSprite(L"FountainRight.bmp", { 3, 1 });
	RES.MakeMultiSprite(L"FountainLeft.bmp", { 3, 1 });
	RES.MakeMultiSprite(L"FountainDown.bmp", { 6, 1 });
	RES.MakeMultiSprite(L"FountainWater.bmp", { 6, 1 });

	RES.MakeMultiSprite(L"AnimalSelect.bmp", {3, 3});
	RES.MakeMultiSprite(L"AnimalStoreMenuNum.bmp", {3, 3});
	RES.MakeSingleSprite(L"AnimalStoreMenu.bmp");

	RES.MakeSingleSprite(L"BarBack.bmp");

	RES.MakeSingleSprite(L"CoopStoreMenu.bmp");
	RES.MakeSingleSprite(L"Build.bmp");
	RES.MakeMultiSprite(L"SelectBuild.bmp", {2, 1});
	RES.MakeSingleSprite(L"Coop.bmp");

	RES.MakeMultiSprite(L"Monster.bmp", { 4, 4 });
	RES.MakeMultiSprite(L"Imo.bmp", { 12, 16 });
	RES.MakeMultiSprite(L"AnimalEffect.bmp", { 8, 3 });
	RES.MakeMultiSprite(L"Egg.bmp", { 2, 1 });

	RES.MakeMultiSprite(L"MapleTree.bmp", { 9, 2 });
	RES.MakeMultiSprite(L"AcornTree.bmp", { 9, 2 });
	RES.MakeMultiSprite(L"PineTree.bmp", { 9, 2 });

	RES.MakeMultiSprite(L"Bug.bmp", { 4, 5 });
	
	RES.MakeSingleSprite(L"Suzie.bmp");

	RES.MakeMultiSprite(L"HorizenArrow.bmp", { 1, 2 });
	RES.MakeMultiSprite(L"Cow.bmp", { 4, 6 });
	RES.MakeMultiSprite(L"Goat.bmp", { 4, 6 });
	RES.MakeMultiSprite(L"Sheep.bmp", { 4, 6 });
	RES.MakeSingleSprite(L"Barn.bmp");
	RES.MakeSingleSprite(L"BarnStoreMenu.bmp");

	RES.MakeMultiSprite(L"Milk.bmp", { 3, 1 });
	RES.MakeMultiSprite(L"Effect0.bmp", { 10, 3 });
	RES.MakeMultiSprite(L"Effect1.bmp", { 10, 2 });

	RES.MakeMultiSprite(L"SleepSelect.bmp", { 1, 2 });
	RES.MakeMultiSprite(L"Sleep.bmp", { 1, 2 });
	RES.MakeSingleSprite(L"SleepBack.bmp");
	RES.MakeSingleSprite(L"TheEnd.bmp");
	RES.MakeSingleSprite(L"Outof.bmp");

	//////////////////////////////////////////////////////State
	MakeState<TitleState>(ALLSTATE::TITLE);
	MakeState<FirstTitle>(ALLSTATE::TITLE1);
	MakeState<SecondTitle>(ALLSTATE::TITLE2);
	MakeState<RoomState>(ALLSTATE::ROOM);
	MakeState<FarmState>(ALLSTATE::FARM);
	MakeState<TownState>(ALLSTATE::TOWN);
	MakeState<MineState>(ALLSTATE::MINE);
	MakeState<MineState1>(ALLSTATE::MINE1);
	MakeState<MineState2>(ALLSTATE::MINE2);
	MakeState<MineState3>(ALLSTATE::MINE3);
	MakeState<MineState4>(ALLSTATE::MINE4);
	MakeState<MineState5>(ALLSTATE::MINE5);
	MakeState<StoreState>(ALLSTATE::STORE);
	MakeState<Town2State>(ALLSTATE::TOWN2);
	MakeState<CoopState>(ALLSTATE::COOP);
	MakeState<BarnState>(ALLSTATE::BARN);
	MakeState<ManiState>(ALLSTATE::MANI);
	MakeState<RobinState>(ALLSTATE::ROBIN);
	MakeState<EditState>(ALLSTATE::EDIT);
	MakeState<EndState>(ALLSTATE::END);
	ChangeState(ALLSTATE::TITLE1);
}


#include "stdafx.h"
#include "Crops.h"
#include "AniActorRender.h"

Crops::Crops()
{
}


Crops::~Crops()
{
}

void Crops::Init()
{
	m_CropsAni = MakeRender<AniActorRender>(10);
	m_CropsAni->Size({64, 128});
	m_CropsAni->Pivot({ 0, -38 });

	MakeCropAnimation();
}

void Crops::MakeCropAnimation()
{
	m_CropsAni->MakeAni(L"Crops.bmp", L"Parsnip", 0, 5, 300.0f, false, 0);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Greenbean", 8, 14, 800.0f, false, 1);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Cauliflower", 16, 22, 700.0f, false, 2);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Potato", 24, 30, 600.0f, false, 3);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Garlic", 32, 37, 500.5f, false, 4);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Kale", 40, 45, 400.5f, false, 5);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Rhubarb", 48, 54, 300.5f, false, 6);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Melon", 56, 62, 900.5f, false, 7);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Tomato", 64, 70, 580.5f, false, 8);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Blueberry", 72, 78, 250.5f, false, 9);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Hotpepper", 80, 86, 590.5f, false, 10);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Wheat", 88, 93, 300.5f, false, 11);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Radish", 96, 101, 440.5f, false, 12);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Redcabbage", 104, 110, 1000.5f, false, 13);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Starfruit", 112, 118, 1200.5f, false, 14);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Corn", 120, 126, 600.5f, false, 15);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Eggplant", 128, 134, 340.5f, false, 16);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Artichoke", 136, 142, 550.5f, false, 17);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Pumpkin", 144, 150, 570.5f, false, 18);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Bokchoy", 152, 157, 708.5f, false, 19);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Yam", 160, 165, 390.5f, false, 20);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Coffeebean", 168, 174, 1200.5f, false, 21);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Beet", 176, 181, 720.5f, false, 22);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Ancientfruit", 192, 198, 600.5f, false, 23);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Strawberry", 240, 246, 700.5f, false, 24);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Grape", 256, 262, 990.5f, false, 25);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Hops", 288, 294, 800.5f, false, 26);

	m_CropsAni->MakeAni(L"Crops.bmp", L"Parsnip1", 0, 0, 0.5f, true, 30);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Greenbean1", 8, 8, 0.5f, true, 31);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Cauliflower1", 16, 16, 0.5f, true, 32);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Potato1", 24, 24, 0.5f, true, 33);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Garlic1", 32, 32, 0.5f, true, 34);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Kale1", 40, 40, 0.5f, true, 35);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Rhubarb1", 48, 48, 0.5f, true, 36);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Melon1", 56, 56, 0.5f, true, 37);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Tomato1", 64, 64, 0.5f, true, 38);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Blueberry1", 72, 72, 0.5f, true, 39);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Hotpepper1", 80, 80, 0.5f, true, 40);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Wheat1", 88, 88, 0.5f, true, 41);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Radish1", 96, 96, 0.5f, true, 42);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Redcabbage1", 104, 104, 0.5f, true, 43);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Starfruit1", 112, 112, 0.5f, true, 44);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Corn1", 120, 120, 0.5f, true, 45);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Eggplant1", 128, 128, 0.5f, true, 46);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Artichoke1", 136, 136, 0.5f, true, 47);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Pumpkin1", 144, 144, 0.5f, true, 48);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Bokchoy1", 152, 152, 0.5f, true, 49);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Yam1", 160, 160, 0.5f, true, 50);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Coffeebean1", 168, 168, 0.5f, true, 51);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Beet1", 176, 176, 0.5f, true, 52);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Ancientfruit1", 192, 192, 0.5f, true, 53);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Strawberry1", 240, 240, 0.5f, true, 54);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Grape1", 256, 256, 0.5f, true, 55);
	m_CropsAni->MakeAni(L"Crops.bmp", L"Hops1", 288, 288, 0.5f, true, 56);
}

void Crops::PrevUpdate()
{
}

void Crops::Update()
{
}

void Crops::LaterUpdate()
{
}

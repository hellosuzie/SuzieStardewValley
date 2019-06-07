#include "stdafx.h"
#include "EditState.h"
#include "TileAim.h"
#include "TileMapEdit.h"
#include "TileActorRender.h"
#include "EnterMgr.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "RoomBack.h"
#include "FarmBack.h"
#include "TownBack.h"
#include "MineBack.h"
#include "StoreBack.h"
#include "Town2Back.h"
#include "CoopBack.h"
#include "ManiBack.h"
#include "RobinBack.h"
#include "BarnBack.h"

EditState::EditState()
{
}


EditState::~EditState()
{
}

void EditState::StateInit()
{
	//RoomBack* RBack = MakeActor<RoomBack>();
	//FarmBack* FBack = MakeActor<FarmBack>();
	//TownBack* TBack = MakeActor<TownBack>();
	//MineBack* FBack = MakeActor<MineBack>();
	//StoreBack* FBack = MakeActor<StoreBack>();
	BarnBack* BBack = MakeActor<BarnBack>();
	//CoopBack* CBack = MakeActor<CoopBack>();
	//Town2Back* T2Back = MakeActor<Town2Back>();
	//ManiBack* MBack = MakeActor<ManiBack>();
	//RobinBack* RBack = MakeActor<RobinBack>();

	m_EditAim = MakeActor<TileAim>();
	m_TestTile = MakeActor<TileMapEdit>();
	MainCamera()->Target(m_EditAim);

	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		m_TestTile->m_TestTile->SetTile({ j, i }, 5);
	//	}
	//}
}

void EditState::StateUpdate()
{
	if (true == ENTER.DownCondition(L"RoomState"))
	{
		CORE.ChangeState(ALLSTATE::ROOM);
	}	
	if (true == ENTER.DownCondition(L"FarmState"))
	{
		CORE.ChangeState(ALLSTATE::FARM);
	}
}

void EditState::DebugUpdate()
{
	WCHAR OutText[100]{};
	swprintf_s(OutText, L"EditState");
	TextOutW(BHDC, 5, 0, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"FPS %d", FPSTIME);
	TextOutW(BHDC, 5, 20, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"Mouse X : %d, Y : %d ", MOUSEI.X, MOUSEI.Y);
	TextOutW(BHDC, 5, 40, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"Aim X : %f, Y : %f ", m_EditAim->Pos().X, m_EditAim->Pos().X);
	TextOutW(BHDC, 5, 60, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"Camera X : %f, Y : %f ", MainCamera()->CameraPos().X, MainCamera()->CameraPos().Y);
	TextOutW(BHDC, 5, 80, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"Screen X : %f, Y : %f ", m_EditAim->Pos().X - MainCamera()->CameraPos().X, m_EditAim->Pos().Y - MainCamera()->CameraPos().Y);
	TextOutW(BHDC, 5, 100, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"TileIndex X : %d, Y : %d ", m_TestTile->m_TestTile->TilePosIndex().X, m_TestTile->m_TestTile->TilePosIndex().Y);
	TextOutW(BHDC, 5, 120, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"TileSprite %d ", m_TestTile->m_TileSpriteNum);
	TextOutW(BHDC, 5, 140, OutText, lstrlenW(OutText));

}

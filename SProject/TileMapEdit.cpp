#include "stdafx.h"
#include "TileMapEdit.h"
#include "resource.h"
#include "EnterMgr.h"
#include "SCore.h"
#include "ResourceMgr.h"
#include "TileActorRender.h"
#include "SingleActorRender.h"
#include "WriteStream.h"
#include "ReadStream.h"
#include "TileAim.h"
#include "EnterMgr.h"
#include "Player.h"

#include <Windows.h>

bool TileMapEdit::SaveCheck = false;
WCHAR TileMapEdit::SaveFileName[1024] = { 0 };
std::wstring TileMapEdit::strSaveFileName = L"";

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK TileMapEdit::TileDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			//내가 만든 대화상자에서 받은 문자열 넣어주기.
			GetDlgItemTextW(hDlg, IDC_EDIT1, SaveFileName, 1024);
			strSaveFileName = SaveFileName;
			//저장할때 확장자 추가해서 더해주기.

			strSaveFileName += L".TileData";
			EndDialog(hDlg, LOWORD(wParam));
			SaveCheck = true;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			SaveCheck = false;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

TileMapEdit::TileMapEdit()
{
}


TileMapEdit::~TileMapEdit()
{
}

void TileMapEdit::Init()
{
	m_TestTile = MakeRender<TileActorRender>();
	m_TestTile->SetTileSprite(L"TileColor.bmp", { 64, 64 });
	m_TestTile->CameraMode(true);

	m_PreTileSprite = MakeRender<SingleActorRender>();
	m_PreTileSprite->SetSprite(L"TileColor.bmp", m_TileSpriteNum);
	m_PreTileSprite->Size({ 100, 100 });
	m_PreTileSprite->Pivot({ 960, 70 });
	m_PreTileSprite->CameraMode(false);
}

void TileMapEdit::PrevUpdate()
{

}

void TileMapEdit::Update()
{
	if (true == KEYDOWNSTAY("Action"))
	{
		m_TestTile->WorldPosSetTile(TileAim::m_Aim->Actor()->Pos(), m_TileSpriteNum);
	}
	if (true == KEYDOWN("Erase"))
	{
		m_TestTile->EraseTile(Player::WorldPlayerIndex(TileAim::m_Aim->Actor()->Pos()));
	}

	if (true == KEYDOWN("Prev"))
	{
		--m_TileSpriteNum;
		if (-1 == m_TileSpriteNum)
		{
			m_TileSpriteNum = 5;
		}
		m_PreTileSprite->SetSprite(L"TileColor.bmp", m_TileSpriteNum);
	}
	if (true == KEYDOWN("Next"))
	{
		++m_TileSpriteNum;
		if (6 == m_TileSpriteNum)
		{
			m_TileSpriteNum = 0;
		}
		m_PreTileSprite->SetSprite(L"TileColor.bmp", m_TileSpriteNum);
	}

	if (true == KEYDOWN("Save"))
	{
		SaveCheck = false;
		DialogBox(SINST, MAKEINTRESOURCE(IDD_DIALOG1), SHWND, TileDialogProc);
		if (true == SaveCheck)
		{
			WriteStream NewWrite = WriteStream(FILEPATHNL("MapData", strSaveFileName.c_str()));
			std::vector<TileActorRender::TileData> SaveTileVec = m_TestTile->GetAllTileData();
			
			//사이즈 넣어주기
			NewWrite << SaveTileVec.size();
		
			for (size_t i = 0; i < SaveTileVec.size(); ++i)
			{
				NewWrite << SaveTileVec[i];
			}
		}
	}
	if (true == KEYDOWN("Load"))
	{
		SaveCheck = false;
		DialogBox(SINST, MAKEINTRESOURCE(IDD_DIALOG1), SHWND, TileDialogProc);
		if (true == SaveCheck)
		{
			ReadStream NewRead = ReadStream(FILEPATHNL("MapData", strSaveFileName.c_str()));
			m_TestTile->Clear();

			size_t Size;
			NewRead >> Size;
			TileActorRender::TileData TempTileData;

			for (size_t i = 0; i < Size; ++i)
			{
				NewRead >> TempTileData;
				m_TestTile->SetTile(TempTileData.m_Pos, TempTileData.m_SpriteIndex);
			}
		}
	}
}

void TileMapEdit::LaterUpdate()
{
}

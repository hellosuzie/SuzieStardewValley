#pragma once
#include "ActorBase.h"

class SingleActorRender;
class TileActorRender;
class TileMapEdit :	public ActorBase
{
public:
	TileActorRender* m_TestTile;
	SingleActorRender* m_PreTileSprite;

	size_t m_TileSpriteNum;
	IPOS m_TileIndexPos;

private:
	static WCHAR SaveFileName[1024];
	static std::wstring strSaveFileName;

public:
	static bool SaveCheck;


public:
	TileMapEdit();
	~TileMapEdit();

public:
	static INT_PTR CALLBACK TileDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void Init();
	void PrevUpdate();
	void Update();
	void LaterUpdate();
};


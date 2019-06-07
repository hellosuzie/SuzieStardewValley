// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#include "GameStruct.h"
#include "GameState.h"
#include "CameraMgr.h"
#include "OverPlayer.h"

#define Tassert(VALUE) assert(!(VALUE))
#define TILESIZE 64
#define TILESIZEH 64 * 0.5f

#define PLAYERSIZEX 64
#define PLAYERSIZEXH PLAYERSIZEX * 0.5f
#define PLAYERSIZEY 128
#define PLAYERSIZEYH PLAYERSIZEY * 0.5f

#define HPX 19
#define HPY 128

#define CORE SCore::Inst()
#define SINST SCore::Inst().WINHINST() 
#define SHDC SCore::Inst().WINDC() 
#define SHWND SCore::Inst().WINHWND() 
#define WINSIZE SCore::Inst().WinSize() 
#define WINSIZEX SCore::Inst().WinSize().X
#define WINSIZEY SCore::Inst().WinSize().Y
#define WINSIZEXH (int)(SCore::Inst().WinSize().X * 0.5f)
#define WINSIZEYH (int)(SCore::Inst().WinSize().Y * 0.5f) 

#define ENTER EnterMgr::Inst()
#define MOUSEI EnterMgr::Inst().MousePosI()
#define MOUSEF EnterMgr::Inst().MousePosF()

#define KEYUP(NAME) EnterMgr::Inst().UpCondition( L##NAME )
#define KEYUPSTAY(NAME) EnterMgr::Inst().UpStayCondition( L##NAME )
#define KEYDOWN(NAME) EnterMgr::Inst().DownCondition( L##NAME )
#define KEYDOWNSTAY(NAME) EnterMgr::Inst().DownStayCondition( L##NAME )

#define KEYUPL(NAME) EnterMgr::Inst().UpCondition( NAME )
#define KEYUPSTAYL(NAME) EnterMgr::Inst().UpStayCondition( NAME )
#define KEYDOWNL(NAME) EnterMgr::Inst().DownCondition( NAME )
#define KEYDOWNSTAYL(NAME) EnterMgr::Inst().DownStayCondition( NAME )

#define TIME TimeMgr::Inst()
#define DELTATIME TimeMgr::Inst().DeltaTime()
#define FPSTIME TimeMgr::Inst().FPS()

#define RES ResourceMgr::Inst()
#define BHDC ResourceMgr::Inst().BackDC()
#define FILEPATH(FOLDER, FILE) ResourceMgr::Inst().MakeFilePath( L##FOLDER, L##FILE ).c_str()
#define FILEPATHNL(FOLDER, FILE) ResourceMgr::Inst().MakeFilePath( L##FOLDER, ##FILE ).c_str()
#define GETSOUND RES.GetSoundPlayer()

#define ITEM ItemMgr::Inst()

#define OVERPLAYER OverPlayer::PlayerEnergy

#define DLEFT FPOS::LEFT
#define DRIGHT FPOS::RIGHT
#define DUP FPOS::UP
#define DDOWN FPOS::DOWN
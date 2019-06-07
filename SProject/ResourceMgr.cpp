#include "stdafx.h"
#include "ResourceMgr.h"
#include "GameImage.h"
#include "GameSprite.h"
#include "GameMultiSprite.h"
#include "SCore.h"
#include "GameSound.h"
#include "SoundPlayer.h"

ResourceMgr::ResourceMgr()
{
}


ResourceMgr::~ResourceMgr()
{
	std::map<std::wstring, GameImage*>::iterator StartIter = m_ImageMap.begin();
	std::map<std::wstring, GameImage*>::iterator EndIter = m_ImageMap.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}
	m_ImageMap.clear();

	std::map<std::wstring, GameSprite*>::iterator StartSIter = m_SpriteMap.begin();
	std::map<std::wstring, GameSprite*>::iterator EndSIter = m_SpriteMap.end();
	for (; StartSIter != EndSIter; ++StartSIter)
	{
		if (nullptr != StartSIter->second)
		{
			delete StartSIter->second;
		}
	}
	m_SpriteMap.clear();

	std::map<std::wstring, GameMultiSprite*>::iterator StartMIter = m_MultiMap.begin();
	std::map<std::wstring, GameMultiSprite*>::iterator EndMIter = m_MultiMap.end();
	for (; StartMIter != EndMIter; ++StartMIter)
	{
		if (nullptr != StartMIter->second)
		{
			delete StartMIter->second;
		}
	}
	m_MultiMap.clear();

	if (nullptr != m_Buffer)
	{
		delete m_Buffer;
	}

	std::map<std::wstring, GameSound*>::iterator StartSoundIter = m_SoundMap.begin();
	std::map<std::wstring, GameSound*>::iterator EndSoundIter = m_SoundMap.end();
	for (; StartSoundIter != EndSoundIter; ++StartSoundIter)
	{
		if (nullptr != StartSoundIter->second)
		{
			delete StartSoundIter->second;
		}
	}
	std::set<SoundPlayer*>::iterator StartSPIter = m_RentalSound.begin();
	std::set<SoundPlayer*>::iterator EndSPIter = m_RentalSound.end();
	for (; StartSPIter != EndSPIter; ++StartSPIter)
	{
		if (nullptr != *StartSPIter)
		{
			delete *StartSPIter;
		}
	}
	if (nullptr == m_SoundSystem)
	{
		m_SoundSystem->release();
	}

}

void ResourceMgr::Init()
{
	WCHAR RootArr[256] = {};
	//파일 위치 가져오는 함수
	GetCurrentDirectoryW(sizeof(WCHAR) * 256, RootArr);
	m_Root = RootArr;

	size_t TempCount = m_Root.find_last_of(L'\\', m_Root.size());
	m_Root.replace(TempCount, m_Root.size(), L"\\Bin\\");

	m_Buffer = new GameImage();
	if (nullptr != m_Buffer)
	{
		m_Buffer->CreateImage({ (float)WINSIZE.X, (float)WINSIZE.Y });
	}

	FMOD::System_Create(&m_SoundSystem);
	Tassert(nullptr == m_SoundSystem);
	if (nullptr == m_SoundSystem)
	{
		return;
	}

	FMOD_RESULT Return = m_SoundSystem->init(32, FMOD_DEFAULT, nullptr);
	Tassert(FMOD_OK != Return);
}

HDC ResourceMgr::BackDC()
{
	return m_Buffer->ImageDC();
}

std::wstring ResourceMgr::FindPath(const WCHAR* _Key)
{
	std::map<std::wstring, std::wstring>::iterator FindIter = m_PathMap.find(_Key);
	//내가 이미지 폴더를 찾는데 만약에 그 폴더의 path가 있다면 그 path 리턴
	if (FindIter != m_PathMap.end())
	{
		return FindIter->second;
	}
	//없다면 그냥 리턴
	return L"";
}

bool ResourceMgr::MakePath(const WCHAR* _Key)
{
	return MakePath(_Key, _Key);
}

bool ResourceMgr::MakePath(const WCHAR* _Key, const WCHAR* _NewFolder)
{
	std::map<std::wstring, std::wstring>::iterator FindIter = m_PathMap.find(_Key);

	//내가 키로 찾은 폴더가 있다면 중복이니까 path를 또 만들 필요가 없다
	if (FindIter != m_PathMap.end())
	{
		Tassert(true);
		return false;
	}
	//실행파일 경로 + 내가 붙일 파일 이름 더해서 인서트해주기
	m_PathMap.insert(std::map<std::wstring, std::wstring>::value_type(_Key, m_Root + _NewFolder + L"\\"));
	return true;
}

std::wstring ResourceMgr::MakeFilePath(const WCHAR * _Key, const WCHAR * _FileName)
{
	//폴더 루트 + 파일이름
	std::wstring TempPath = FindPath(_Key);
	return TempPath += _FileName;
}

//////////////////////////////////////////////////Image

GameImage * ResourceMgr::FindImage(const WCHAR * _Key)
{
	std::map<std::wstring, GameImage*>::iterator FindIter = m_ImageMap.find(_Key);

	//내가 찾는 이미지가 있다면 그대로 리턴
	if (FindIter == m_ImageMap.end())
	{
		return nullptr;
	}
	return FindIter->second;
}

GameImage * ResourceMgr::MakeImage(const WCHAR * _FolderKey, const WCHAR * _ImageName, UINT _TransColor)
{
	GameImage* TempImage = FindImage(_ImageName);

	//내가 찾는 이미지가 있다면 그대로 리턴
	if (nullptr != TempImage)
	{
		return TempImage;
	}

	//없다면 경로 찾고 경로 + 이미지 이름으로 path를 만든다.
	std::wstring ImagePath = FindPath(_FolderKey);
	ImagePath += _ImageName;

	GameImage* NewImage = new GameImage();
	NewImage->TransColor(_TransColor);
	if (false == NewImage->ImageLoad(ImagePath.c_str()))
	{
		delete NewImage;
		Tassert(true);
		return nullptr;
	}

	m_ImageMap.insert(std::map<std::wstring, GameImage*>::value_type(_ImageName, NewImage));
	return NewImage;
}

//////////////////////////////////////////////////Sprite

GameSprite * ResourceMgr::FindSprite(const WCHAR * _SpriteName)
{
	std::map<std::wstring, GameSprite*>::iterator FindSpriteIter = m_SpriteMap.find(_SpriteName);

	if (FindSpriteIter == m_SpriteMap.end())
	{
		return nullptr;
	}
	return FindSpriteIter->second;
}

GameSprite * ResourceMgr::MakeSprite(const WCHAR * _ImageName, FPOS _Pos, FSIZE _Size)
{
	return MakeSprite(_ImageName, _ImageName, _Pos, _Size);
}

GameSprite * ResourceMgr::MakeSprite(const WCHAR * _ImageName, const WCHAR * _SpriteName, FPOS _Pos, FSIZE _Size)
{
	GameSprite* TempSprite = FindSprite(_SpriteName);

	//스프라이트가 있으면 그걸 리턴
	if (nullptr != TempSprite)
	{
		return TempSprite;
	}

	//이미지 찾기 없으면 터트리기
	GameImage* TempImage = FindImage(_ImageName);
	if (nullptr == TempImage)
	{
		Tassert(true);
		return nullptr;
	}

	GameSprite* NewSprite = new GameSprite(TempImage, _Pos, _Size);
	m_SpriteMap.insert(std::map<std::wstring, GameSprite*>::value_type(_SpriteName, NewSprite));
	return NewSprite;
}

GameSprite * ResourceMgr::MakeSingleSprite(const WCHAR * _ImageName)
{
	return MakeSingleSprite(_ImageName, _ImageName);
}

GameSprite * ResourceMgr::MakeSingleSprite(const WCHAR * _ImageName, const WCHAR * _SpriteName)
{
	GameSprite* TempSprite = FindSprite(_SpriteName);

	//스프라이트가 있으면 그걸 리턴
	if (nullptr != TempSprite)
	{
		return TempSprite;
	}

	//이미지 찾기 없으면 터트리기
	GameImage* TempImage = FindImage(_ImageName);
	if (nullptr == TempImage)
	{
		Tassert(true);
		return nullptr;
	}

	GameSprite* NewSprite = new GameSprite(TempImage, { 0, 0 }, TempImage->ImageSize());
	m_SpriteMap.insert(std::map<std::wstring, GameSprite*>::value_type(_SpriteName, NewSprite));
	return NewSprite;
}

//////////////////////////////////////////////////MultiSprite

GameMultiSprite * ResourceMgr::FindMultiSprite(const WCHAR * _Key)
{
	std::map<std::wstring, GameMultiSprite*>::iterator FindMSpriteIter = m_MultiMap.find(_Key);

	if (FindMSpriteIter == m_MultiMap.end())
	{
		return nullptr;
	}
	return FindMSpriteIter->second;
}

GameSprite * ResourceMgr::FindMultiSprite(const WCHAR * _Key, size_t _Index)
{
	std::map<std::wstring, GameMultiSprite*>::iterator FindMSpriteIter = m_MultiMap.find(_Key);

	if (FindMSpriteIter == m_MultiMap.end())
	{
		return nullptr;
	}
	return FindMSpriteIter->second->GetSprite(_Index);
}

GameMultiSprite * ResourceMgr::MakeMultiSprite(const WCHAR* _ImageName, const WCHAR* _SpriteName, ISIZE _Size)
{
	Tassert(0 == _Size.X);
	Tassert(0 == _Size.Y);

	GameMultiSprite* TempMSprite = FindMultiSprite(_SpriteName);
	if (nullptr != TempMSprite)
	{
		return TempMSprite;
	}

	GameImage* TempImage = FindImage(_ImageName);
	if (nullptr == TempImage)
	{
		Tassert(true);
		return nullptr;
	}

	FSIZE SpriteSize = FSIZE();
	SpriteSize.X = TempImage->Width() / (float)_Size.X;
	SpriteSize.Y = TempImage->Height() / (float)_Size.Y;

	GameMultiSprite* NewMultiSprite = new GameMultiSprite(_Size.X * _Size.Y);
	FPOS Pos = FPOS();

	for (int y = 0; y < _Size.Y; ++y)
	{
		for (int x = 0; x < _Size.X; ++x)
		{
			GameSprite* NewSprite = new GameSprite(TempImage, Pos, SpriteSize);
			NewMultiSprite->PushMultiSprite(NewSprite);
			Pos.X += SpriteSize.X;
		}
		Pos = { 0, Pos.Y + SpriteSize.Y };
	}

	m_MultiMap.insert(std::map<std::wstring, GameMultiSprite*>::value_type(_SpriteName, NewMultiSprite));
	return NewMultiSprite;
}

GameMultiSprite * ResourceMgr::MakeMultiSprite(const WCHAR * _ImageName, ISIZE _Size)
{
	return MakeMultiSprite(_ImageName, _ImageName, _Size);
}

//////////////////////////////////////////////////Sound

GameSound * ResourceMgr::LoadSound(const WCHAR * _FolderKey, const WCHAR * _SoundName)
{
	GameSound* Sound = FindSound(_SoundName);
	if (nullptr != Sound)
	{
		return Sound;
	}

	Sound = new GameSound();
	std::wstring Path = FindPath(_FolderKey);
	Path += _SoundName;

	if (false == Sound->SoundLoad(Path.c_str()))
	{
		Tassert(true);
		delete Sound;
	}
	m_SoundMap.insert(std::map<std::wstring, GameSound*>::value_type(_SoundName, Sound));
	return Sound;
}

GameSound * ResourceMgr::FindSound(const WCHAR * _SoundName)
{
	std::map<std::wstring, GameSound*>::iterator FindIter = m_SoundMap.find(_SoundName);
	if (FindIter == m_SoundMap.end())
	{
		return nullptr;
	}
	return FindIter->second;
}

void ResourceMgr::PlaySound(const WCHAR * _SoundName)
{
	GameSound* Sound = FindSound(_SoundName);
	Tassert(nullptr == Sound);
	if (nullptr == Sound)
	{
		return;
	}
	m_SoundSystem->playSound(Sound->Sound(), nullptr, false, nullptr);
}

SoundPlayer * ResourceMgr::GetSoundPlayer()
{
	SoundPlayer* NewPlayer = new SoundPlayer();
	m_RentalSound.insert(NewPlayer);
	return NewPlayer;
}

bool ResourceMgr::ReturnSoundPlayer(SoundPlayer * _SoundPlayer)
{
	std::set<SoundPlayer*>::iterator FindIter = m_RentalSound.find(_SoundPlayer);
	if (m_RentalSound.end() == FindIter)
	{
		return false;
	}
	delete *FindIter;
	m_RentalSound.erase(FindIter);
	return true;
}

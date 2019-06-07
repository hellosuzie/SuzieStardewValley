#pragma once
#include <map>
#include <string>
#include <fmod.hpp>

#pragma comment(lib, "fmod_vc")

class SoundPlayer;
class GameSound;
class GameMultiSprite;
class GameSprite;
class GameImage;
class ResourceMgr
{
public:
	static ResourceMgr& Inst()
	{
		static ResourceMgr NewResource = ResourceMgr();
		return NewResource;
	}

private:
	ResourceMgr();
	~ResourceMgr();

//////////////////////////////////////////////////Path
private:
	std::map<std::wstring, std::wstring> m_PathMap;
	//프로그램 실행되는 파일 경로
	std::wstring m_Root;

	GameImage* m_Buffer;

public:
	std::wstring RootPath()
	{
		return m_Root;
	}
	HDC BackDC();

public:
	void Init();
	std::wstring FindPath(const WCHAR* _Key);

	bool MakePath(const WCHAR* _Key);
	bool MakePath(const WCHAR* _Key, const WCHAR* _NewFolder);

	std::wstring MakeFilePath(const WCHAR* _Key, const WCHAR* _FileName);

//////////////////////////////////////////////////Image
private:
	std::map<std::wstring, GameImage*> m_ImageMap;

public:
	GameImage* FindImage(const WCHAR* _Key);
	GameImage* MakeImage(const WCHAR* _FolderKey, const WCHAR* _ImageName, UINT _TransColor = RGB(255, 255, 255));

//////////////////////////////////////////////////Sprite
private:
	std::map<std::wstring, GameSprite*> m_SpriteMap;

public:
	GameSprite* FindSprite(const WCHAR* _SpriteName);

	GameSprite* MakeSprite(const WCHAR* _ImageName, FPOS _Pos, FSIZE _Size);
	GameSprite* MakeSprite(const WCHAR* _ImageName, const WCHAR* _SpriteName, FPOS _Pos, FSIZE _Size);

	//스프라이트 사이즈를 이미지사이즈로 설정해서 만드는 함수
	GameSprite* MakeSingleSprite(const WCHAR * _ImageName);
	GameSprite* MakeSingleSprite(const WCHAR * _ImageName, const WCHAR * _SpriteName);

//////////////////////////////////////////////////MultiSprite
private:
	std::map<std::wstring, GameMultiSprite*> m_MultiMap;

public:
	//멀티스프라이트 찾는 함수
	GameMultiSprite* FindMultiSprite(const WCHAR* _Key);
	//그중에서 인덱스번째 스프라이트 하나만 찾는 함수
	GameSprite* FindMultiSprite(const WCHAR* _Key, size_t _Index);
	GameMultiSprite* MakeMultiSprite(const WCHAR* _ImageName, const WCHAR* _SpriteName, ISIZE _Size);
	GameMultiSprite* MakeMultiSprite(const WCHAR* _ImageName, ISIZE _Size);
	
//////////////////////////////////////////////////Sound
public:
	friend GameSound;
	friend SoundPlayer;

private:
	FMOD::System* m_SoundSystem;
	std::map<std::wstring, GameSound*> m_SoundMap;
	std::set<SoundPlayer*> m_RentalSound;

public:
	SoundPlayer* GetSoundPlayer();
	bool ReturnSoundPlayer(SoundPlayer* _SoundPlayer);

public:
	GameSound* LoadSound(const WCHAR* _FolderKey, const WCHAR* _SoundName);
	GameSound* FindSound(const WCHAR* _SoundName);

	void PlaySound(const WCHAR* _SoundName);

};


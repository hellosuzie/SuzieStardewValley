#pragma once
#include <fmod.hpp>

class GameSound
{
private:
	FMOD::Sound* m_Sound;
	UINT Len;

public:
	FMOD::Sound* Sound()
	{
		return m_Sound;
	}

public:
	GameSound();
	~GameSound();

public:
	bool SoundLoad(const WCHAR* _Path);
};


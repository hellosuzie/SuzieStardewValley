#pragma once
#include <fmod.hpp>

class ResourceMgr;
class GameSound;
class SoundPlayer
{
private:
	friend ResourceMgr;

public:
	GameSound* m_Sound;
	FMOD::Channel* m_Chennel;
	float m_Pitch;

public:
	SoundPlayer();
	~SoundPlayer();

public:
	float Pitch();
	void Pitch(float _Value);
	bool SoundPlayCheck();

	void NewSoundPlay(const WCHAR* _Filename);

	void Stop();
	void Pause();
};


#include "stdafx.h"
#include "GameSound.h"
#include "ResourceMgr.h"
#include <atlstr.h>


GameSound::GameSound() : Len(0)
{
}


GameSound::~GameSound()
{
	m_Sound->release();
}

bool GameSound::SoundLoad(const WCHAR * _Path)
{
	std::string TempPath = CW2A(_Path);
	if (FMOD_OK != RES.m_SoundSystem->createSound(TempPath.c_str(), FMOD_DEFAULT, nullptr, &m_Sound))
	{
		Tassert(true);
		return false;
	}
	if (nullptr == m_Sound)
	{
		Tassert(true);
		return false;	
	}

	m_Sound->getLength(&Len, FMOD_TIMEUNIT_MS);
	return true;
}

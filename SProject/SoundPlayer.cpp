#include "stdafx.h"
#include "SoundPlayer.h"
#include "ResourceMgr.h"
#include "GameSound.h"

SoundPlayer::SoundPlayer() : m_Chennel(nullptr)
{
}


SoundPlayer::~SoundPlayer()
{
}

float SoundPlayer::Pitch()
{
	m_Chennel->getPitch(&m_Pitch);
	return m_Pitch;
}

void SoundPlayer::Pitch(float _Value)
{
	m_Pitch = _Value;
	m_Chennel->setPitch(m_Pitch);
	return;
}

bool SoundPlayer::SoundPlayCheck()
{
	bool SoundPlayingCheck;
	m_Chennel->isPlaying(&SoundPlayingCheck);
	return SoundPlayingCheck;
}

void SoundPlayer::NewSoundPlay(const WCHAR * _Filename)
{
	if (nullptr != m_Chennel)
	{
		m_Chennel->stop();
	}
	GameSound* Sound = RES.FindSound(_Filename);

	if (nullptr == Sound)
	{
		Tassert(true);
		return;
	}

	RES.m_SoundSystem->playSound(Sound->Sound(), nullptr, false, &m_Chennel);
	Pitch();
}

void SoundPlayer::Stop()
{
	if (nullptr == m_Chennel)
	{
		return;
	}
	m_Chennel->stop();
}

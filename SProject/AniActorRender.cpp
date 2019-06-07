#include "stdafx.h"
#include "AniActorRender.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "GameMultiSprite.h"
#include "ActorBase.h"
#include "ClockNumber.h"

AniActorRender::Animation::Animation(GameMultiSprite* _MultiSprite
	, size_t _StartFrame
	, size_t _EndFrame
	, float _FrameTime
	, bool _Loop
	, size_t _AniNum)
	: m_MultiSprite(_MultiSprite)
	, m_StartFrame(_StartFrame)
	, m_EndFrame(_EndFrame)
	, m_CurFrame(0)
	, m_FrameTime(_FrameTime)
	, m_TimeCheck(0.0f)
	, m_Loop(_Loop)
	, m_AniNum(_AniNum)
{
}

AniActorRender::Animation::~Animation()
{
}

bool AniActorRender::Animation::AniEndCheck()
{
	//현재 프레임이 마지막 프레임이고 체크하는 시간이 프레임시간보다 긴 상태라면 애니메이션 끝난것.
	return m_CurFrame == m_EndFrame && m_FrameTime <= m_TimeCheck;
}

bool AniActorRender::Animation::AniStartCheck()
{
	if (m_CurFrame == m_StartFrame && m_FrameTime >= m_TimeCheck)
	{
		return true;
	}
	return false;
}

void AniActorRender::Animation::SetStartFrame(size_t _Start)
{
	m_CurFrame = m_StartFrame + _Start;
	Tassert(m_CurFrame > m_EndFrame);
}

void AniActorRender::Animation::AniUpdate()
{
	if (m_CurFrame != m_EndFrame)
	{
		m_TimeCheck += (DELTATIME * ClockNumber::TimeBoost);
		//그리고 그 델타타임이 쌓여서 프레임타임과 같거나 커진다면
		if (m_FrameTime <= m_TimeCheck)
		{
			//프레임을 더해주고(다음 프레임으로 넘어간다) 현재 시간을 초기화해준다.
			++m_CurFrame;
			m_TimeCheck = 0.0f;
		}
	}
	else //내가 마지막 프레임이라면(애니메이션이 끝났다면)
	{
		//만약에 내가 루프를 도는 애니메이션이라면 
		if (true == m_Loop)
		{
			//똑같이 프레임스피드를 카운트하고 카운트가 프레임시간보다 크거나 같아진다면 
			m_TimeCheck += (DELTATIME * ClockNumber::TimeBoost);
			//만약에 프레임을 더한 숫자가 마지막 프레임보다 크다면
			if (m_FrameTime <= m_TimeCheck)
			{
				m_TimeCheck = 0;
				//현재 프레임은 시작 프레임이 된다.
				m_CurFrame = m_StartFrame;
				m_AniEnd = true;
			}
		}
		else if (false == m_Loop)
		{
			m_TimeCheck += (DELTATIME * ClockNumber::TimeBoost);
			//만약에 프레임을 더한 숫자가 마지막 프레임보다 크다면
			if (m_FrameTime <= m_TimeCheck)
			{
				m_AniEnd = true;
			}
		}
	}
}

GameSprite * AniActorRender::Animation::GetCurSprite()
{
	return m_MultiSprite->GetSprite(m_CurFrame);
}


AniActorRender::AniActorRender() : m_CurAni(nullptr)
{
}


AniActorRender::~AniActorRender()
{
	std::map<std::wstring, Animation*>::iterator StartIter = m_AniMap.begin();
	std::map<std::wstring, Animation*>::iterator EndIter = m_AniMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}
}

bool AniActorRender::CurAniCheck(const WCHAR * _AniName)
{
	if (nullptr != m_CurAni)
	{
		//그냥 m_CurAni == _AniName 을 하면 주소값을 하나하나 비교하는것이 된다.
		//그러니까 함수로 비교해야함
		return m_CurAni->CompareName(_AniName);
	}
	return false;
}

bool AniActorRender::AniEndCheck()
{
	if (nullptr != m_CurAni)
	{
		return m_CurAni->AniEndCheck();
	}
	return false;
}

bool AniActorRender::AniStartCheck()
{
	if (nullptr != m_CurAni)
	{
		if (true == m_CurAni->AniStartCheck())
		{
			return true;
		}
	}
	return false;
}

AniActorRender::Animation * AniActorRender::FindAni(const WCHAR * _AniName)
{
	std::map<std::wstring, Animation*>::iterator FindIter = m_AniMap.find(_AniName);
	if (FindIter == m_AniMap.end())
	{
		return nullptr;
	}
	return FindIter->second;
}

void AniActorRender::MakeAni(const WCHAR * _SpriteName
	, const WCHAR * _AniName
	, size_t _StartFrame
	, size_t _EndFrame
	, float _FrameTime
	, bool _Loop
	, size_t _AniNum)
{
	Animation* FindAnimation = FindAni(_AniName);
	if (nullptr != FindAnimation)
	{
		return;
	}

	GameMultiSprite* MSprite = RES.FindMultiSprite(_SpriteName);
	if (nullptr == MSprite)
	{
		Tassert(true);
		return;
	}

	Animation* NewAni = new Animation(MSprite, _StartFrame, _EndFrame, _FrameTime, _Loop, _AniNum);
	NewAni->Name(_AniName);
	m_AniMap.insert(std::map<std::wstring, Animation*>::value_type(_AniName, NewAni));
}

void AniActorRender::ChangeAni(const WCHAR * _Aniname, size_t _Num/* = 0*/)
{
	//애니메이션 찾아서 바꿔주고 어디서부터 시작할지 지정해줄 수 있다
	m_CurAni = FindAni(_Aniname);
	Tassert(nullptr == m_CurAni);
	m_CurAni->SetStartFrame(_Num);
}

void AniActorRender::Render()
{
	if (true == Debug)
	{
		int a = 0; 
	}

	if (nullptr == m_CurAni)
	{
		return;
	}

	m_CurAni->AniUpdate();
	
	GameSprite* Sprite = m_CurAni->GetCurSprite();

	if (nullptr != Sprite)
	{
		FPOS RenderPos = GetRenderPos();

		if (false == AlphaCheck() || false == Sprite->GetImage()->AlphaCheck())
		{
			TransparentBlt(BHDC
				, RenderPos.IX()	//그려질 위치 X
				, RenderPos.IY()	//그려질 위치 X
				, (int)(m_Size.X * Actor()->ScaleRatio())	//그려질 이미지 크기
				, (int)(m_Size.Y * Actor()->ScaleRatio())
				, Sprite->ImageDC()
				, Sprite->Pos().IX()		//이미지에서 그려질 부분이 시작하는 지점 X
				, Sprite->Pos().IY()		//이미지에서 그려질 부분이 시작하는 지점 Y
				, Sprite->Size().IX()		//시작할 X에서 얼만큼 그려질것인지
				, Sprite->Size().IY()		//시작할 Y에서 얼만큼 그려질것인지
				, Sprite->TransColor());
		}
		else if (true == AlphaCheck() || true == Sprite->GetImage()->AlphaCheck())
		{
			AlphaBlend(BHDC
				, RenderPos.IX()	//그려질 위치 X
				, RenderPos.IY()	//그려질 위치 X
				, (int)(m_Size.X * Actor()->ScaleRatio())	//그려질 이미지 크기
				, (int)(m_Size.Y * Actor()->ScaleRatio())
				, Sprite->ImageDC()
				, Sprite->Pos().IX()		//이미지에서 그려질 부분이 시작하는 지점 X
				, Sprite->Pos().IY()		//이미지에서 그려질 부분이 시작하는 지점 Y
				, Sprite->Size().IX()		//시작할 X에서 얼만큼 그려질것인지
				, Sprite->Size().IY()		//시작할 Y에서 얼만큼 그려질것인지
				, m_BlandFunc);
		}
	}
}

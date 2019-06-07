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
	//���� �������� ������ �������̰� üũ�ϴ� �ð��� �����ӽð����� �� ���¶�� �ִϸ��̼� ������.
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
		//�׸��� �� ��ŸŸ���� �׿��� ������Ÿ�Ӱ� ���ų� Ŀ���ٸ�
		if (m_FrameTime <= m_TimeCheck)
		{
			//�������� �����ְ�(���� ���������� �Ѿ��) ���� �ð��� �ʱ�ȭ���ش�.
			++m_CurFrame;
			m_TimeCheck = 0.0f;
		}
	}
	else //���� ������ �������̶��(�ִϸ��̼��� �����ٸ�)
	{
		//���࿡ ���� ������ ���� �ִϸ��̼��̶�� 
		if (true == m_Loop)
		{
			//�Ȱ��� �����ӽ��ǵ带 ī��Ʈ�ϰ� ī��Ʈ�� �����ӽð����� ũ�ų� �������ٸ� 
			m_TimeCheck += (DELTATIME * ClockNumber::TimeBoost);
			//���࿡ �������� ���� ���ڰ� ������ �����Ӻ��� ũ�ٸ�
			if (m_FrameTime <= m_TimeCheck)
			{
				m_TimeCheck = 0;
				//���� �������� ���� �������� �ȴ�.
				m_CurFrame = m_StartFrame;
				m_AniEnd = true;
			}
		}
		else if (false == m_Loop)
		{
			m_TimeCheck += (DELTATIME * ClockNumber::TimeBoost);
			//���࿡ �������� ���� ���ڰ� ������ �����Ӻ��� ũ�ٸ�
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
		//�׳� m_CurAni == _AniName �� �ϸ� �ּҰ��� �ϳ��ϳ� ���ϴ°��� �ȴ�.
		//�׷��ϱ� �Լ��� ���ؾ���
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
	//�ִϸ��̼� ã�Ƽ� �ٲ��ְ� ��𼭺��� �������� �������� �� �ִ�
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
				, RenderPos.IX()	//�׷��� ��ġ X
				, RenderPos.IY()	//�׷��� ��ġ X
				, (int)(m_Size.X * Actor()->ScaleRatio())	//�׷��� �̹��� ũ��
				, (int)(m_Size.Y * Actor()->ScaleRatio())
				, Sprite->ImageDC()
				, Sprite->Pos().IX()		//�̹������� �׷��� �κ��� �����ϴ� ���� X
				, Sprite->Pos().IY()		//�̹������� �׷��� �κ��� �����ϴ� ���� Y
				, Sprite->Size().IX()		//������ X���� ��ŭ �׷���������
				, Sprite->Size().IY()		//������ Y���� ��ŭ �׷���������
				, Sprite->TransColor());
		}
		else if (true == AlphaCheck() || true == Sprite->GetImage()->AlphaCheck())
		{
			AlphaBlend(BHDC
				, RenderPos.IX()	//�׷��� ��ġ X
				, RenderPos.IY()	//�׷��� ��ġ X
				, (int)(m_Size.X * Actor()->ScaleRatio())	//�׷��� �̹��� ũ��
				, (int)(m_Size.Y * Actor()->ScaleRatio())
				, Sprite->ImageDC()
				, Sprite->Pos().IX()		//�̹������� �׷��� �κ��� �����ϴ� ���� X
				, Sprite->Pos().IY()		//�̹������� �׷��� �κ��� �����ϴ� ���� Y
				, Sprite->Size().IX()		//������ X���� ��ŭ �׷���������
				, Sprite->Size().IY()		//������ Y���� ��ŭ �׷���������
				, m_BlandFunc);
		}
	}
}

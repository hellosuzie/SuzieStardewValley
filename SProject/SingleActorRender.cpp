#include "stdafx.h"
#include "SingleActorRender.h"
#include "ResourceMgr.h"
#include "SCore.h"
#include "ActorBase.h"
#include "GameSprite.h"
#include "ActorRender.h"

#pragma comment(lib, "msimg32.lib")

SingleActorRender::SingleActorRender() : m_Sprite(nullptr)
{
}


SingleActorRender::~SingleActorRender()
{
}

void SingleActorRender::SetSprite(const WCHAR* _ImageName)
{
	m_Sprite = RES.FindSprite(_ImageName);
	if (nullptr == m_Sprite)
	{
		Tassert(true);
	}
}

void SingleActorRender::SetSprite(const WCHAR * _ImageName, size_t _Index)
{
	m_Sprite = RES.FindMultiSprite(_ImageName, _Index);
	if (nullptr == m_Sprite)
	{
		Tassert(true);
	}
}

void SingleActorRender::Render()
{
	Tassert(nullptr == m_Sprite);
	if (nullptr != m_Sprite)
	{
		//엑터의 포스에서 얼만큼 떨어져있는 부분에 랜드할것인지 더해준 값이 랜더포스.
		//거기에 스프라이트가 그려질 때 엑터의 중심부부터 그려지는것이 아니라
		//엑터의 중심 = 스프라이트의 중심이 되게 그리고 싶기 때문에 사이즈 반만큼을 빼준다.
		FPOS RenderPos = GetRenderPos();

		if (false == AlphaCheck() || false == m_Sprite->GetImage()->AlphaCheck())
		{
			TransparentBlt(BHDC
				, RenderPos.IX()	//그려질 위치 X
				, RenderPos.IY()	//그려질 위치 X
				, (int)(m_Size.X * Actor()->ScaleRatio())	//그려질 이미지 크기
				, (int)(m_Size.Y * Actor()->ScaleRatio())
				, m_Sprite->ImageDC()
				, m_Sprite->Pos().IX()		//이미지에서 그려질 부분이 시작하는 지점 X
				, m_Sprite->Pos().IY()		//이미지에서 그려질 부분이 시작하는 지점 Y
				, m_Sprite->Size().IX()		//시작할 X에서 얼만큼 그려질것인지
				, m_Sprite->Size().IY()		//시작할 Y에서 얼만큼 그려질것인지
				, m_Sprite->TransColor());
		}
		else if (true == AlphaCheck() || true == m_Sprite->GetImage()->AlphaCheck())
		{
			AlphaBlend(BHDC
				, RenderPos.IX()	//그려질 위치 X
				, RenderPos.IY()	//그려질 위치 X
				, (int)(m_Size.X * Actor()->ScaleRatio())	//그려질 이미지 크기
				, (int)(m_Size.Y * Actor()->ScaleRatio())
				, m_Sprite->ImageDC()
				, m_Sprite->Pos().IX()		//이미지에서 그려질 부분이 시작하는 지점 X
				, m_Sprite->Pos().IY()		//이미지에서 그려질 부분이 시작하는 지점 Y
				, m_Sprite->Size().IX()		//시작할 X에서 얼만큼 그려질것인지
				, m_Sprite->Size().IY()		//시작할 Y에서 얼만큼 그려질것인지
				, m_BlandFunc);
		}

	}
}



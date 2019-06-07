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
		//������ �������� ��ŭ �������ִ� �κп� �����Ұ����� ������ ���� ��������.
		//�ű⿡ ��������Ʈ�� �׷��� �� ������ �߽ɺκ��� �׷����°��� �ƴ϶�
		//������ �߽� = ��������Ʈ�� �߽��� �ǰ� �׸��� �ͱ� ������ ������ �ݸ�ŭ�� ���ش�.
		FPOS RenderPos = GetRenderPos();

		if (false == AlphaCheck() || false == m_Sprite->GetImage()->AlphaCheck())
		{
			TransparentBlt(BHDC
				, RenderPos.IX()	//�׷��� ��ġ X
				, RenderPos.IY()	//�׷��� ��ġ X
				, (int)(m_Size.X * Actor()->ScaleRatio())	//�׷��� �̹��� ũ��
				, (int)(m_Size.Y * Actor()->ScaleRatio())
				, m_Sprite->ImageDC()
				, m_Sprite->Pos().IX()		//�̹������� �׷��� �κ��� �����ϴ� ���� X
				, m_Sprite->Pos().IY()		//�̹������� �׷��� �κ��� �����ϴ� ���� Y
				, m_Sprite->Size().IX()		//������ X���� ��ŭ �׷���������
				, m_Sprite->Size().IY()		//������ Y���� ��ŭ �׷���������
				, m_Sprite->TransColor());
		}
		else if (true == AlphaCheck() || true == m_Sprite->GetImage()->AlphaCheck())
		{
			AlphaBlend(BHDC
				, RenderPos.IX()	//�׷��� ��ġ X
				, RenderPos.IY()	//�׷��� ��ġ X
				, (int)(m_Size.X * Actor()->ScaleRatio())	//�׷��� �̹��� ũ��
				, (int)(m_Size.Y * Actor()->ScaleRatio())
				, m_Sprite->ImageDC()
				, m_Sprite->Pos().IX()		//�̹������� �׷��� �κ��� �����ϴ� ���� X
				, m_Sprite->Pos().IY()		//�̹������� �׷��� �κ��� �����ϴ� ���� Y
				, m_Sprite->Size().IX()		//������ X���� ��ŭ �׷���������
				, m_Sprite->Size().IY()		//������ Y���� ��ŭ �׷���������
				, m_BlandFunc);
		}

	}
}



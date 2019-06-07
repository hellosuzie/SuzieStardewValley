#include "stdafx.h"
#include "ActorRender.h"
#include "ActorBase.h"

ActorRender::ActorRender() :m_CameraMode(true), Debug(false)
{
	m_BlandFunc.BlendOp = AC_SRC_OVER;
	m_BlandFunc.BlendFlags = 0;
	m_BlandFunc.AlphaFormat = AC_SRC_ALPHA;
	m_BlandFunc.SourceConstantAlpha = 255;
}


ActorRender::~ActorRender()
{
}

FPOS ActorRender::GetRenderPos()
{
	//���������� �÷��̾� ��ġ�������� �Ǻ� ���ϰ� �̹��� ������ �ݸ�ŭ ���ش�(�߽ɿ� �׸��� ���ؼ�)
	FPOS RenderPos = Actor()->Pos() + Pivot() - m_Size.VEC2FH();
	//ī�޶� ���� �޴� ��쿡�� ���� ������������ ī�޶� ������ ���ش�.
	if (true == m_CameraMode)
	{
		RenderPos -= Actor()->Parent()->MainCamera()->CameraPos();
	}
	return RenderPos;

	//CameraRenderPos�� m_Pos - CameraPos�� ���� ���̴�.
	//Ÿ�ټ����������� ī�޶������� 0, 0 �� ������ ������ �ǰ� ������ ������ ���ϸ� ī�޶������� ���Ѵ�
}

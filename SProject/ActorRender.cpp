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
	//랜더포스는 플레이어 위치포스에서 피봇 더하고 이미지 사이즈 반만큼 빼준다(중심에 그리기 위해서)
	FPOS RenderPos = Actor()->Pos() + Pivot() - m_Size.VEC2FH();
	//카메라 영향 받는 경우에는 위의 랜더포스에서 카메라 포스를 빼준다.
	if (true == m_CameraMode)
	{
		RenderPos -= Actor()->Parent()->MainCamera()->CameraPos();
	}
	return RenderPos;

	//CameraRenderPos는 m_Pos - CameraPos를 해준 값이다.
	//타겟설정했을때는 카메라포스의 0, 0 이 엑터의 포스가 되고 엑터의 포스가 변하면 카메라포스도 변한다
}

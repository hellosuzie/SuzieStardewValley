#pragma once

class ActorBase;
class CameraMgr
{
private:
	FPOS m_Camera;
	FPOS m_RenderPos;

	//카메라가 따라다닐 엑터
	ActorBase* m_Target;

	//카메라 범위 지정
	FPOS m_StartPos;
	FPOS m_EndPos;
	//범위가 있는지 없는지 확인하는 변수
	bool m_Range;

public:
	CameraMgr();
	~CameraMgr();

public:
	void SetRange(bool _Value)
	{
		m_Range = _Value;
	}
	void Target(ActorBase* _Target)
	{
		m_Target = _Target;
	}

	void StartPos(FPOS _Pos)
	{
		m_StartPos = _Pos;
	}
	void EndPos(FPOS _Pos)
	{
		m_EndPos = _Pos;
	}
	FPOS StartPos()
	{
		return m_StartPos;
	}
	FPOS EndPos()
	{
		return m_EndPos;
	}

	FPOS CameraPos()
	{
		return m_RenderPos;
	}
	void CameraPos(FPOS _Pos)
	{
		m_Camera = _Pos;
	}
	void MoveCamera(FPOS _Pos)
	{
		m_Camera += _Pos;
	}

public:
	void Update();

};


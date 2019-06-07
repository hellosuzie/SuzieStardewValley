#pragma once

class ActorBase;
class CameraMgr
{
private:
	FPOS m_Camera;
	FPOS m_RenderPos;

	//ī�޶� ����ٴ� ����
	ActorBase* m_Target;

	//ī�޶� ���� ����
	FPOS m_StartPos;
	FPOS m_EndPos;
	//������ �ִ��� ������ Ȯ���ϴ� ����
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


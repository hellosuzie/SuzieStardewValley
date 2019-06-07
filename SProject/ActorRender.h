#pragma once
#include "ActorPosBase.h"

class ActorRender :	public ActorPosBase
{
public:
	friend class ActorMGR;
	friend ActorBase;

private:
	bool m_CameraMode;

public:
	bool Debug;

protected:
	BLENDFUNCTION m_BlandFunc;
	int m_Order;

public:
	ActorRender();
	~ActorRender();

public:
	inline int Order() 
	{
		return m_Order;
	}
	inline void Order(int _Order)
	{
		m_Order = _Order;
	}
	inline bool AlphaCheck()
	{
		return 255 > m_BlandFunc.SourceConstantAlpha;
	}
	void SetAlpha(int _Alpha)
	{
		if (255 <= _Alpha)
		{
			_Alpha = 255;
		}
		m_BlandFunc.SourceConstantAlpha = _Alpha;
	}
	inline int GetAlpha()
	{
		return m_BlandFunc.SourceConstantAlpha;
	}
	//카메라 온오프 기능
	inline void CameraMode(bool _Value)
	{
		m_CameraMode = _Value;
	}
	virtual bool CameraMode()
	{
		return m_CameraMode;
	}

public:
	FPOS GetRenderPos();
	virtual void Render() = 0;

};


#pragma once
class TimeMgr
{
public:
	static TimeMgr& Inst()
	{
		static TimeMgr NewTime = TimeMgr();
		return NewTime;
	}
	
private:
	class Timer
	{
	public:
		friend TimeMgr;

	private:
		LARGE_INTEGER m_OneSecCount;
		LARGE_INTEGER m_CurCount;
		LARGE_INTEGER m_PrevCount;
		float m_DeltaTime;

		int m_FPS;
		int m_FPSAcc;
		float m_FPSTimeAcc;

	public:
		Timer();
		~Timer();

	private:
		void Update();
		void CurFPS();

	};

public:
	friend class SCore;

private:
	Timer m_MainTimer;

public:
	inline float DeltaTime() const
	{
		return m_MainTimer.m_DeltaTime;
	}
	inline int FPS() const
	{
		return m_MainTimer.m_FPS;
	}

private:
	TimeMgr();
	~TimeMgr();

private:
	void Update();

};


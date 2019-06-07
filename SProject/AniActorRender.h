#pragma once
#include "ActorRender.h"
#include "NameBase.h"
#include <map>

class GameSprite;
class GameMultiSprite;
class AniActorRender :	public ActorRender
{
private:
	class Animation : public NameBase
	{
	public:
		friend AniActorRender;

	private:
		GameMultiSprite* m_MultiSprite;
		size_t m_StartFrame;
		size_t m_EndFrame;
		size_t m_CurFrame;
		float m_FrameTime;
		float m_TimeCheck;
		bool m_Loop;
		size_t m_AniNum;

		bool m_AniEnd;

	public:
		Animation(GameMultiSprite* _MultiSprite, size_t _StartFrame, size_t _EndFrame, float _FrameTime, bool _Loop, size_t _AniNum);
		~Animation();

	public:
		bool AniEndCheck();
		bool AniStartCheck();
		void SetStartFrame(size_t _Start);
		void AniUpdate();
		GameSprite* GetCurSprite();
	};

private:
	std::map<std::wstring, Animation*> m_AniMap;
	Animation* m_CurAni;

public:
	AniActorRender();
	~AniActorRender();

public:
	inline size_t AniNum()
	{
		return m_CurAni->m_AniNum;
	}
	inline const WCHAR* AniName()
	{
		return m_CurAni->Name();
	}

public:
	bool CurAniCheck(const WCHAR* _AniName);
	bool AniEndCheck();
	bool AniStartCheck();

	Animation* FindAni(const WCHAR* _AniName);
	//const가 붙는 이유는 ""이걸 쓰기 위해서 (""은 상수인데 상수는 당연히 값을 바꿀 수 없는 상수로 받아야한다)
	void MakeAni(const WCHAR* _SpriteName, const WCHAR* _AniName, size_t _StartFrame, size_t _EndFrame, float _FrameTime = 0.1f, bool _Loop = true, size_t _AniNum = 0);
	void ChangeAni(const WCHAR* _Aniname, size_t _Num = 0);

	void Render() override;
};


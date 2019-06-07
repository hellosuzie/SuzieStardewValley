#pragma once
#include <list>
#include <map>

class ActorCollision;
class CollisionMgr
{
private:
	class CollGroup
	{
	public:
		std::wstring Name;

	private:
		//콜리전들 저장해놓은 리스트
		std::list<ActorCollision*> m_CollList;

		std::list<ActorCollision*>::iterator m_ThisStartIter;
		std::list<ActorCollision*>::iterator m_ThisEndIter;

		std::list<ActorCollision*>::iterator m_OtherStartIter;
		std::list<ActorCollision*>::iterator m_OtherEndIter;

		//내가 충돌할 그룹들(플레이어가 몬스터와도 충돌하고 몬스터 bullet과도 충돌할수 있으니까 그룹은 여러개가 된다)
		std::list<CollGroup*> m_OtherGroupList;

		std::list<CollGroup*>::iterator m_OtherSIter;
		std::list<CollGroup*>::iterator m_OtherEIter;

	public:
		CollGroup();
		~CollGroup();

	public:
		void Link(CollGroup* _OtherGroup);
		//콜리전 push해주는 함수
		void PushCollision(ActorCollision* _Other);
		//other 콜리전 그룹과 콜리전체크 해주는 함수
		void CollCheck(CollGroup* _Group);
		void Collision();
		void Release();

		void CollPosSet();
		void DebugRender();
	};

public:
	CollisionMgr();
	~CollisionMgr();

private:
	//그룹이름이랑 
	std::map<std::wstring, CollGroup*> m_CollMap;
	std::map<std::wstring, CollGroup*>::iterator m_FindIter;

private:
	CollGroup* FindCollGroup(const WCHAR* _GroupName);

public:
	void PushCollision(const WCHAR* _GroupName, ActorCollision* _Other);
	void Link(const WCHAR* _Left, const WCHAR* _Right);

	void Collision();
	void Release();
	void DebugRender();
};


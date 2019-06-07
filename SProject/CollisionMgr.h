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
		//�ݸ����� �����س��� ����Ʈ
		std::list<ActorCollision*> m_CollList;

		std::list<ActorCollision*>::iterator m_ThisStartIter;
		std::list<ActorCollision*>::iterator m_ThisEndIter;

		std::list<ActorCollision*>::iterator m_OtherStartIter;
		std::list<ActorCollision*>::iterator m_OtherEndIter;

		//���� �浹�� �׷��(�÷��̾ ���Ϳ͵� �浹�ϰ� ���� bullet���� �浹�Ҽ� �����ϱ� �׷��� �������� �ȴ�)
		std::list<CollGroup*> m_OtherGroupList;

		std::list<CollGroup*>::iterator m_OtherSIter;
		std::list<CollGroup*>::iterator m_OtherEIter;

	public:
		CollGroup();
		~CollGroup();

	public:
		void Link(CollGroup* _OtherGroup);
		//�ݸ��� push���ִ� �Լ�
		void PushCollision(ActorCollision* _Other);
		//other �ݸ��� �׷�� �ݸ���üũ ���ִ� �Լ�
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
	//�׷��̸��̶� 
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


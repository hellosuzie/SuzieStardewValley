#pragma once
#include <map>
#include <list>
#include <set>

class GameState;
class ActorRender;
class RenderMgr
{
public:
	friend GameState;

private:
	std::map<int, std::list<ActorRender*>> m_RenderMap;

	std::map<int, std::list<ActorRender*>>::iterator m_StartMapIter;
	std::map<int, std::list<ActorRender*>>::iterator m_EndMapIter;

	std::list<ActorRender*>::iterator m_StartListIter;
	std::list<ActorRender*>::iterator m_EndListIter;

	std::set<int> m_YSortSet;
	std::set<int>::iterator m_YSetIter;

public:
	RenderMgr();
	~RenderMgr();

private:
	void Ysort(int _Index);

	void PushRender(int _Order, ActorRender* _Render);
	void Render();
	void Release();
};


#pragma once
#include <vector>
#include <map>
#include "SCore.h"

class EnterMgr
{
public:
	static EnterMgr& Inst()
	{
		static EnterMgr NewEnter = EnterMgr();
		return NewEnter;
	}

private:
	class KeyData
	{
	public:
		friend EnterMgr;

	private:
		std::vector<int> m_AllKeyVec;
		bool m_Up;
		bool m_UpStay;
		bool m_Down;
		bool m_DownStay;
		float m_PushTime;

	public:
		//키 받아서 벡터에 저장하는 함수.
		KeyData(size_t _Count) : m_Up(false), m_UpStay(false), m_Down(false), m_DownStay(false)
		{
			m_AllKeyVec.reserve(_Count);
		}
		~KeyData() {}

	private:
		//키를 int로 받아서 만든다. - ""안에 있는애는 인트로 못받음 ''안에있는애는 인트로 받을수있음.
		template<typename... Rest>
		void PushKeyData(const int _Value, Rest... _Arg)
		{
			m_AllKeyVec.push_back(_Value);
			PushKeyData(_Arg...);
		}

		void PushKeyData()
		{
		}

	public:
		void Update();
		bool AllKeyCheck();

	};

public:
	friend SCore;

private:
	//키 모아놓은 맵.
	std::map<std::wstring, KeyData*> m_KeyMap;
	std::map<std::wstring, KeyData*>::iterator StartIter;
	std::map<std::wstring, KeyData*>::iterator EndIter;

private:
	POINT m_MousePos;

private:
	EnterMgr();
	~EnterMgr();

public:
	IPOS MousePosI()
	{
		return{ m_MousePos.x, m_MousePos.y};
	}
	FPOS MousePosF()
	{
		return{ m_MousePos.x, m_MousePos.y };
	}

private:
	//키 찾아서 리턴해주는 함수.
	KeyData* FindKey(const WCHAR* _Name)
	{
		std::map<std::wstring, KeyData*>::iterator FindIter = m_KeyMap.find(_Name);
		if (FindIter == m_KeyMap.end())
		{
			return nullptr;
		}
		return FindIter->second;
	}

public:
	//키 만들어주는 함수.
	template<typename ... Rest>
	bool MakeKey(const WCHAR* _Name, Rest... _Arg)
	{
		KeyData* NewKey = FindKey(_Name);

		if (nullptr != NewKey)
		{
			Tassert(true);
			return false;
		}

		NewKey = new KeyData(sizeof...(_Arg));
		NewKey->PushKeyData(_Arg...);
		m_KeyMap.insert(std::map<std::wstring, KeyData*>::value_type(_Name, NewKey));
		return true;
	}

private:
	void Update();

public:
	bool UpCondition(const WCHAR* _Name);
	bool UpStayCondition(const WCHAR* _Name);
	bool DownCondition(const WCHAR* _Name);
	bool DownStayCondition(const WCHAR* _Name);

	float PushTime(WCHAR* _Name);
	bool PushTimeReset(WCHAR* _Name, float _Time);

};


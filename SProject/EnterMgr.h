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
		//Ű �޾Ƽ� ���Ϳ� �����ϴ� �Լ�.
		KeyData(size_t _Count) : m_Up(false), m_UpStay(false), m_Down(false), m_DownStay(false)
		{
			m_AllKeyVec.reserve(_Count);
		}
		~KeyData() {}

	private:
		//Ű�� int�� �޾Ƽ� �����. - ""�ȿ� �ִ¾ִ� ��Ʈ�� ������ ''�ȿ��ִ¾ִ� ��Ʈ�� ����������.
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
	//Ű ��Ƴ��� ��.
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
	//Ű ã�Ƽ� �������ִ� �Լ�.
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
	//Ű ������ִ� �Լ�.
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


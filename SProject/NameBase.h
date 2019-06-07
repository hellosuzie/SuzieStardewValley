#pragma once
#include "UpdateBase.h"
#include <string>

class NameBase :	public UpdateBase
{
private:
	std::wstring m_Name;

public:
	NameBase();
	~NameBase();

public:
	inline void Name(const WCHAR* _Name)
	{
		m_Name = _Name;
	}
	inline const WCHAR* Name() const
	{
		return m_Name.c_str();
	}
	inline bool CompareName(const WCHAR* _Name) const
	{
		return m_Name == _Name;
	}
};


#pragma once
#include "FileStream.h"
#include <vector>

class ReadStream : public FileStream
{
public:
	ReadStream(const WCHAR* _FilePath);
	~ReadStream();

public:
	FILE* File()
	{
		return m_File;
	}

	template<typename T>
	void operator >> (T& _Value)
	{
		fread_s(&_Value, sizeof(_Value), sizeof(_Value), 1, m_File);
	}

	template<typename T>
	void Read(void* _Buf, int _Num)
	{
		fread_s(_Buf, sizeof(T) * _Num, sizeof(T) * _Num, 1, m_File);
	}
	
};


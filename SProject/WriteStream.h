#pragma once
#include "FileStream.h"
class WriteStream :
	public FileStream
{
public:
	WriteStream(const WCHAR* _FilePath);
	~WriteStream();

public:
	template<typename T>
	void operator << (const T& _Value)
	{
		fwrite(&_Value, sizeof(_Value), 1, m_File);
	}

	template<typename T>
	void Write(void* _Buf, int _size)
	{
		fwrite(_Buf, sizeof(T) * _size, 1, m_File);
	}
};


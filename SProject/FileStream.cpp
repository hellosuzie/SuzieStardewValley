#include "stdafx.h"
#include "FileStream.h"

FileStream::FileStream(const WCHAR* _FilePath, const WCHAR* _FileMode)
{
	Open(_FilePath, _FileMode);
}


FileStream::~FileStream()
{
	fclose(m_File);
}

void FileStream::Open(const WCHAR * _FilePath, const WCHAR * _FileMode)
{
	_wfopen_s(&m_File, _FilePath, _FileMode);
}

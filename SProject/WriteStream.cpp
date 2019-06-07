#include "stdafx.h"
#include "WriteStream.h"


WriteStream::WriteStream(const WCHAR* _FilePath) : FileStream(_FilePath, L"wb")
{
}


WriteStream::~WriteStream()
{
}

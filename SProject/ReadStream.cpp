#include "stdafx.h"
#include "ReadStream.h"
#include <string>

ReadStream::ReadStream(const WCHAR* _FilePath) : FileStream(_FilePath, L"rb")
{
}


ReadStream::~ReadStream()
{
}

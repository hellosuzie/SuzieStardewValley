#pragma once
class FileStream
{
protected:
	FILE* m_File;

public:
	FileStream(const WCHAR* _FilePath, const WCHAR* _FileMode);
	virtual ~FileStream();

private:
	void Open(const WCHAR* _FilePath, const WCHAR* _FileMode);

};


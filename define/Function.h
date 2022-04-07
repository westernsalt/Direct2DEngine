#ifndef Function_h__
#define Function_h__

inline	wstring		ConvertRelativePath(wstring	szFullPath)
{ 
	TCHAR	szRelativePath[MAX_PATH] = L"";
	TCHAR	szDirectoryPath[MAX_PATH] = L"";

	//vcproj ������ �ִ� ��ġ�� ��� �Լ�...
	GetCurrentDirectory(sizeof(szDirectoryPath), szDirectoryPath);

	//�� ��ο��� �ٸ� ��η� ���� ��� ��θ� �����Ѵ�...
	PathRelativePathTo((LPWSTR)szRelativePath, szDirectoryPath,
		FILE_ATTRIBUTE_DIRECTORY, szFullPath.c_str(),
		FILE_ATTRIBUTE_NORMAL);

	return szRelativePath;
}

class CStringCmp
{
private:
	const TCHAR* m_pString;

public:
	explicit CStringCmp(const TCHAR* pKey)
		: m_pString(pKey){ }
	~CStringCmp() {}

public:
	template <typename T>
	bool	operator () (T data)
	{
		return !lstrcmp(data.first, m_pString);
	}

};

#endif // Function_h__

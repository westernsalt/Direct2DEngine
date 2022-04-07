#pragma once

class CTexture;

class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)
private:
	unordered_map<int, CTexture*>		m_MapTexture;
	//	objkey와 statkey를 int로 관리하겠다

public:
	void InsertTexture(const TCHAR* _filePath, const int _iObjKey,
		eTextureType _type, const int _iStateKey = -1, const int _iCount = 0,
		eReleaseType	eRType = RT_DYNAMIC);

	TEXINFO* GetTexture(const int _iObjKey,
		const int _iStateKey = 0, const int _iCount = 0);
public:
	void	Initialize(void);
	HRESULT	Update(void);
	void	Render(void);
	void	Release(void);
	void	ReleaseDynamicResource(void);

private:
	CTextureMgr(void);

public:
	~CTextureMgr(void);
};

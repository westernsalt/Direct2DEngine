#pragma once

#include "Obj.h"

class CObjMgr
{ 
	DECLARE_SINGLETON(CObjMgr);
private:
	list<CObj*>		m_Objlist[OBJ_END];
	vector<CObj*>	m_vecRender[RENDER_END];

public:	
	static bool	Compare(CObj*	pDest, CObj*	pSour)
	{
		return pDest->GetInfo()->vPos.y < pSour->GetInfo()->vPos.y;
	}

public:
	void	Initialize();
	void	Update();
	void	Render();
	void	Release();
	void	ReleaseDynamicObject();

public:
	list<CObj*>* GetList(void)
	{
		return m_Objlist;
	}

private:
	CObjMgr(void);
public:
	~CObjMgr(void);
};

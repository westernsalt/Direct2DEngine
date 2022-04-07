#include "StdAfx.h"
#include "ObjMgr.h"

#include "Obj.h"
#include "Player.h"
#include "Monster.h"

IMPLEMENT_SINGLETON(CObjMgr);

CObjMgr::CObjMgr(void)
{ 
	
}

CObjMgr::~CObjMgr(void)
{
	Release();
}

void CObjMgr::Initialize(void)
{
	OBJ_ITER iter;
	OBJ_ITER iter_end;

	for(int i = 0; i<OBJ_END; ++i)
	{
		iter = m_Objlist[i].begin();
		iter_end = m_Objlist[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Initialize();
		}
	}
}

void CObjMgr::Update(void)
{
	OBJ_ITER iter;
	OBJ_ITER iter_end;

	for(int i = 0; i<OBJ_END; ++i)
	{
		iter = m_Objlist[i].begin();
		iter_end = m_Objlist[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Update();

			if(i == OBJ_MONSTER)
			{
				if( ((CMonster*)(*iter))->GetbDead() == true)
				{
					iter = m_Objlist[i].erase(iter);

					if(iter == iter_end)
					{
						break;
					}
				}
			}
		}
	}
}

void CObjMgr::Render(void)
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		OBJ_ITER iter = m_Objlist[i].begin();
		OBJ_ITER iter_end = m_Objlist[i].end();
		for(; iter != iter_end; ++iter)
		{
			m_vecRender[(*iter)->GetType()].push_back((*iter));
		}
	}

	//월드obj정렬
	sort(m_vecRender[RENDER_WORDOBJ].begin(), m_vecRender[RENDER_WORDOBJ].end(),
		CObjMgr::Compare);

	for(int i = 0; i < RENDER_END; ++i)
	{
		for(int j = 0, iCnt = m_vecRender[i].size(); j < iCnt ;++j)
		{
			m_vecRender[i][j]->Render();
		}

		m_vecRender[i].clear();
	}
}


void CObjMgr::Release(void)
{
	OBJ_ITER iter;
	OBJ_ITER iter_end;

	for(int i = 0; i<OBJ_END; ++i)
	{
		iter = m_Objlist[i].begin();
		iter_end = m_Objlist[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			SAFE_DELETE(*iter);
		}
		m_Objlist[i].clear();
	}
}

void CObjMgr::ReleaseDynamicObject(void)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_Objlist[i].begin();
		list<CObj*>::iterator iter_end = m_Objlist[i].end();

		for(iter; iter != iter_end;)
		{
			if((*iter)->GetReleaseType() == RT_DYNAMIC)
			{
				SAFE_DELETE (*iter);
				iter = m_Objlist[i].erase(iter);
			}
			else
				++iter;
		}
	}
}
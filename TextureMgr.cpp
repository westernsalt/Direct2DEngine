#include "StdAfx.h"
#include "TextureMgr.h"
#include "Texture.h"
#include "MultiTex.h"
#include "SingleTex.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr(void)
{ 
}

CTextureMgr::~CTextureMgr(void)
{
	Release();
}

void CTextureMgr::Initialize(void)
{

}

HRESULT CTextureMgr::Update(void)
{
	return S_OK;
}

void CTextureMgr::Render(void)
{
}

void CTextureMgr::Release(void)
{
	unordered_map<int, CTexture*>::iterator iter;
	unordered_map<int, CTexture*>::iterator iter_end;

	iter = m_MapTexture.begin();
	iter_end = m_MapTexture.end();

	for(iter; iter!= iter_end; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	m_MapTexture.clear();
}

void CTextureMgr::InsertTexture(const TCHAR* _filePath, const int _iObjKey, eTextureType _type, const int _iStateKey /*= -1*/, const int _iCount /*= 0*/, eReleaseType _eRType)
{
	CTexture* pTexture;

	unordered_map<int, CTexture*>::iterator iter;
	unordered_map<int, CTexture*>::iterator iter_end;

	iter = m_MapTexture.begin();
	iter_end = m_MapTexture.end();

	int i = m_MapTexture.size();

	for(iter; iter!= iter_end;)
	{
		if(iter->first == _iObjKey)
		{
			((CMultiTex*)(iter->second))->InsertTexture(_filePath, (eStateKey)_iStateKey, _iCount, _eRType);
			return;
		}
		else
		{
			++iter;
		}
	}

	if(iter == iter_end)
	{
		switch(_type)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTex;
			break;
		case TEX_MULTI:
			pTexture = new CMultiTex;
			break;
		}

		m_MapTexture.insert(make_pair(_iObjKey, pTexture));

		wstring wstrTemp = _filePath;
		wstrTemp += L"Texture Loading Failed!";

		if(FAILED(pTexture->InsertTexture(_filePath, (eStateKey)_iStateKey, _iCount, _eRType)))
		{
			MessageBox(g_hWnd, wstrTemp.c_str(), L"Warning", MB_OK);
			return;
		}
	}
}

TEXINFO* CTextureMgr::GetTexture(const int _iObjKey, const int _iStateKey, const int _iCount)
{
	unordered_map<int, CTexture*>::iterator iter;
	unordered_map<int, CTexture*>::iterator iter_end;

	iter = m_MapTexture.begin();
	iter_end = m_MapTexture.end();

	for(iter; iter!= iter_end; ++iter)
	{
		if(iter->first == _iObjKey)
		{
			return iter->second->GetTexture((eStateKey)_iStateKey, _iCount);
		}
	}

	if(iter == iter_end)
	{
		MessageBox(g_hWnd, L"매니저가 텍스쳐를 못찾았단다.", L"Warning!", MB_OK);
	}

	return NULL;
}

void CTextureMgr::ReleaseDynamicResource(void)
{
	unordered_map<int, CTexture*>::iterator iter = m_MapTexture.begin();

	for(iter; iter != m_MapTexture.end();)
	{
		if(iter->second->GetReleaseType() == RT_DYNAMIC)
		{
			SAFE_DELETE(iter->second);
			iter = m_MapTexture.erase(iter);
		}
		else
			++iter;
	}
}

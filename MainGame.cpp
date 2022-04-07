#include "StdAfx.h"
#include "MainGame.h"
#include "Device.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "TextureMgr.h"
#include "SoundMgr.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
 
CMainGame::CMainGame(void)
{
	/*AllocConsole();
	freopen("CONOUT$", "wt", stdout);*/
}

CMainGame::~CMainGame(void)
{
	//FreeConsole();
	Release();
}

void CMainGame::Initialize(void)
{
	m_iCount = 0;
	m_dwTime = GetTickCount();
	ZeroMemory(m_szFps, sizeof(TCHAR) * MAX_STR);

	m_pDevice = CDevice::GetInstance();
	m_pDevice->InitD3D();

	CObjMgr::GetInstance();
	CSceneMgr::GetInstance()->SetScene(SCENE_LOGO);
	CTextureMgr::GetInstance();
	CTimeMgr::GetInstance()->InitTime();
	CKeyMgr::GetInstance();
	CSoundMgr::GetInstance()->LoadSoundFile();
}

void CMainGame::Update(void)
{
	CTimeMgr::GetInstance()->SetTime();
	CSceneMgr::GetInstance()->Update();
}

void CMainGame::Render(void)
{
	CDevice::GetInstance()->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);

	m_pDevice->Render_Begin();

	CSceneMgr::GetInstance()->Render();

	if(m_dwTime + 1000 < GetTickCount())
	{
		m_dwTime = GetTickCount();

		wsprintf(m_szFps, L"FPS : %d", m_iCount);

		SetWindowText(g_hWnd, m_szFps);

		m_iCount = 0;
	}

	++m_iCount;

	m_pDevice->Render_End();
}

void CMainGame::Release(void)
{
	CDevice::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CSoundMgr::GetInstance()->StopAll();
	CSoundMgr::GetInstance()->Destroy();
}
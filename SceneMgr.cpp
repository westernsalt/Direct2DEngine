#include "StdAfx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Logo.h"
#include "Stage.h"

IMPLEMENT_SINGLETON(CSceneMgr);

CSceneMgr::CSceneMgr(void)
{ 
	m_pScene		= NULL;
	m_bNextScene	= false;
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

void CSceneMgr::Initialize(void)
{

}

void CSceneMgr::Render(void)
{
	m_pScene->Render();
}

void CSceneMgr::Update(void)
{
	if(m_pScene)
		m_pScene->Update();

	if(m_bNextScene == true)
	{
		delete	m_pScene;
		m_pScene = m_pNextScene;
		m_bNextScene = false;
		m_pScene->Update();
	}
}

void CSceneMgr::Release(void)
{
	if(m_pScene)
	{
		SAFE_DELETE(m_pScene);
	}
}

void CSceneMgr::SetScene(int _scene_state)
{
	CScene* newScene = NULL;

	switch(_scene_state)
	{
	case SCENE_LOGO:
		newScene = new CLogo;
		break;
	case SCENE_STAGE:
		newScene = new CStage;
		break;
	case SCENE_SKILL_EDIT:
		break;
	default:
		break;
	}

	newScene->Initialize();

	if(m_pScene != NULL)
	{
		m_bNextScene = true;
		m_pNextScene = newScene;
	}
	else
	{
		m_pScene = newScene;
	}
}

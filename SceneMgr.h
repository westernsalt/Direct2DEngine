#pragma once

class CScene;

class CSceneMgr
{ 
	DECLARE_SINGLETON(CSceneMgr);

private:
	CScene*		m_pScene;
	CScene*		m_pNextScene;
	bool		m_bNextScene;

public:
	void		SetScene(int _scene_state);

public:
	void Initialize(void);
	void Render(void);
	void Update(void);
	void Release(void);

private:
	CSceneMgr(void);

public:
	~CSceneMgr(void);
};

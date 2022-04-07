#pragma once

class CDevice;

class CMainGame
{
private:
	CDevice*	m_pDevice;

private: 
	int			m_iCount;
	float		m_fTime;
	DWORD		m_dwTime;
	TCHAR		m_szFps[MAX_STR];

public:
	void	Initialize();
	void	Update();
	void	Render();
	void	Release();

public:
	CMainGame(void);
	~CMainGame(void);
};

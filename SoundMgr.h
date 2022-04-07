#pragma once

class CSoundMgr
{ 
private:
	static CSoundMgr* m_Instance;

public:
	static CSoundMgr*	GetInstance(void)
	{
		if(m_Instance == NULL)
			m_Instance = new CSoundMgr;

		return m_Instance;
	}

	void Destroy(void)
	{
		if(m_Instance)
		{
			delete m_Instance;
			m_Instance = NULL;
		}
	}
//	fmod 인터페이스
//	시스템 장치를 초기화해야한다
private:
	FMOD_SYSTEM*		m_pSystem;	//	fmod시스템 포인터

	FMOD_CHANNEL*		m_pEffect;
	FMOD_CHANNEL*		m_pMainBGM;
	FMOD_CHANNEL*		m_pSkill;
	FMOD_CHANNEL*		m_pMonster;
	//	이거를 게임에 맞춰서 하나씩 지정
	//	몬스터 사운드가 종류별로 하나씩이면 한번에 겹치면 안되니까 같이 사운드 출력될 거 고민
	//	효과음 채널

	FMOD_RESULT			m_Result;	//	에러관리용
	unsigned int		m_iVersion;
	map<TCHAR*, FMOD_SOUND*>		m_mapSound;	//	사운드 관리


public:
	void Initialize(void);
	void LoadSoundFile(void);
	void PlaySound(TCHAR* SoundKey);
	void PlayBGM(TCHAR* SoundKey);
	void StopBGM(void);
	void StopAll(void);
	//	BGM은 계속 돌지. 순환루프로 할거고
	//	일반사운드는 한번 들리면 꺼지게 할거야

public:
	map<TCHAR*, FMOD_SOUND*>*	GetSoundMap(void)
	{
		return &m_mapSound;
	}

private:
	void ErrorCheck(FMOD_RESULT _result);

private:
	CSoundMgr(void);
public:
	~CSoundMgr(void);
};

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
//	fmod �������̽�
//	�ý��� ��ġ�� �ʱ�ȭ�ؾ��Ѵ�
private:
	FMOD_SYSTEM*		m_pSystem;	//	fmod�ý��� ������

	FMOD_CHANNEL*		m_pEffect;
	FMOD_CHANNEL*		m_pMainBGM;
	FMOD_CHANNEL*		m_pSkill;
	FMOD_CHANNEL*		m_pMonster;
	//	�̰Ÿ� ���ӿ� ���缭 �ϳ��� ����
	//	���� ���尡 �������� �ϳ����̸� �ѹ��� ��ġ�� �ȵǴϱ� ���� ���� ��µ� �� ���
	//	ȿ���� ä��

	FMOD_RESULT			m_Result;	//	����������
	unsigned int		m_iVersion;
	map<TCHAR*, FMOD_SOUND*>		m_mapSound;	//	���� ����


public:
	void Initialize(void);
	void LoadSoundFile(void);
	void PlaySound(TCHAR* SoundKey);
	void PlayBGM(TCHAR* SoundKey);
	void StopBGM(void);
	void StopAll(void);
	//	BGM�� ��� ����. ��ȯ������ �ҰŰ�
	//	�Ϲݻ���� �ѹ� �鸮�� ������ �Ұž�

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

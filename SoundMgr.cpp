#include "StdAfx.h"
#include "SoundMgr.h"
#include "Function.h"

CSoundMgr*	CSoundMgr::m_Instance = NULL;

CSoundMgr::CSoundMgr(void)
{ 
	m_pSystem = NULL;
	m_iVersion = 0;

	Initialize();
}

CSoundMgr::~CSoundMgr(void)
{
	map<TCHAR* , FMOD_SOUND*> ::iterator iter = m_mapSound.begin();
	map<TCHAR* , FMOD_SOUND*> ::iterator iter_end = m_mapSound.end();

	for(iter; iter != iter_end; ++iter)
	{
		m_Result = FMOD_Sound_Release(iter->second);

		ErrorCheck(m_Result);

		delete [] (iter->first);

		iter = m_mapSound.erase(iter);
		iter_end = m_mapSound.end();

		if(iter == iter_end)
		{
			break;
		}
	}

	m_Result = FMOD_System_Close(m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Release(m_pSystem);
	ErrorCheck(m_Result);
}

void CSoundMgr::Initialize(void)
{
	m_Result = FMOD_System_Create(&m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_GetVersion(m_pSystem, &m_iVersion);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(m_Result);
}

void CSoundMgr::LoadSoundFile(void)
{
	_finddata_t fd;
	long handle;
	int iResult = 1;

	handle = _findfirst("..\\SoundFile\\*.*", &fd);	//	�ش��ο��ִ� ��� �����͸� �ҷ��´�

	if(handle == -1)
		return;

	while(iResult != -1)
	{
		TCHAR	szName[256] = L"";
		ZeroMemory(szName, sizeof(szName));

		//	��Ƽ����Ʈ�� �����ڵ�� ���������� �Ѵ�
		//	�����ڵ� ��Ƽ����Ʈ �ڲ� �ٲٴ°� MFC���� �򰥸��ž�
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fd.name, strlen(fd.name), szName, 256);

		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		lstrcpy(pName, szName);		//	�����ڵ� ���ڿ� ����

		char szFullName[256];
		strcpy_s(szFullName, "..\\SoundFile\\");
		strcat_s(szFullName, fd.name);

		FMOD_SOUND* pSound;
		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName, FMOD_HARDWARE, 0, &pSound);
		
		if(m_Result == FMOD_OK)
		{
			m_mapSound.insert(make_pair(pName,pSound));
		}
		else
		{
			delete [] pName;
		}

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);
	m_Result = FMOD_System_Update(m_pSystem);

	ErrorCheck(m_Result);
}

void CSoundMgr::PlaySound(TCHAR* SoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(SoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect);
}

void CSoundMgr::PlayBGM(TCHAR* SoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(SoundKey));

	if(iter == m_mapSound.end())
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pMainBGM);
}

void CSoundMgr::StopBGM(void)
{
	m_Result = FMOD_Channel_Stop(m_pMainBGM);
	ErrorCheck(m_Result);
}

void CSoundMgr::StopAll(void)
{
	m_Result = FMOD_Channel_Stop(m_pMainBGM);
	ErrorCheck(m_Result);
	
	m_Result = FMOD_Channel_Stop(m_pEffect);
	ErrorCheck(m_Result);
}

void CSoundMgr::ErrorCheck(FMOD_RESULT _result)
{
	if(_result != FMOD_OK)
	{
		cout << "����!" << endl;
		return;
	}
}
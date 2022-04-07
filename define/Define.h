#ifndef DEFINE_H_
#define DEFINE_H_

#define	DECLARE_SINGLETON(ClassName)		\
private:									\
	static	ClassName*	m_pInstance;		\
public:										\
	static	ClassName*	GetInstance(void)	\
	{										\
		if(m_pInstance == NULL)				\
			m_pInstance = new ClassName;	\
		return m_pInstance;					\
	}										\
	void	DestroyInstance(void)			\
	{										\
		if(m_pInstance)						\
		{									\
			delete m_pInstance;				\
			m_pInstance = NULL;				\
		}									\
	}										\

#define IMPLEMENT_SINGLETON(ClassName)		\
ClassName*	ClassName::m_pInstance = NULL;	\


#define GETTIME CTimeMgr::GetInstance()->GetTime()
#define	GETDEV	CDevice::GetInstance()->GetDevice()

#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define SAFE_DELETE_ARRAY(p) if(p) { delete [] p; p = NULL;}

#ifdef __TOOL__
#define MSG_BOX(string) AfxMessageBox(string);
#else
#define MSG_BOX(string) MessageBox(g_hWnd, string, L"Error!!", MB_OK)
#endif

//	SkillMemory MaxGage Define
#define MAX_MEMORY	16

//	TileSetDefine
#define TILESIZEX		130
#define TILESIZEY		68
#define TILECNTX		75
#define TILECNTY		75

#define PASS			0
#define BLOCKED			1

//	LoadingBar Scale once Define
#define SCALE_NUM		0.000089f
#define TURN_DELAY		0.008f

//	Default bearing Measure Define
#define DEFAULT_BEARING	32

//	For catch degree between Two Keydown Msg
#define CUR_KEYDOWN		0
#define PREV_KEYDOWN	1

//	Key Degree Define
#define KEY_RIGHT		0
#define KEY_RUP			45
#define	KEY_UP			90
#define KEY_LUP			135
#define KEY_LEFT		180
#define KEY_LDOWN		225
#define KEY_DOWN		270
#define KEY_RDOWN		315

class CObj;

typedef list<CObj*>				OBJ_LIST;
typedef list<CObj*>::iterator	OBJ_ITER;



#endif // Define_h__

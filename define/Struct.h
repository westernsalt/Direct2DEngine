#ifndef STRUCT_H_
#define STRUCT_H_


typedef struct tagTexInfo
{ 
	LPDIRECT3DTEXTURE9	pTexture;		//	texture infomation
	D3DXIMAGE_INFO		ImgInfo;		//	ImgInfomation Data
}TEXINFO;


typedef struct tagStrCompare			//	functor that used in map()
{
	template<typename T>
	bool	operator()(T data)
	{
		return !lstrcmp(data.first, m_pString);
	}
	const TCHAR*	m_pString;
	tagStrCompare(const TCHAR* pKey)
		:m_pString(pKey){;}
}STRCOMPARE;

typedef	struct tagTile
{
	D3DXVECTOR3	vPos;			//	tile center position
	D3DXVECTOR3	vSize;			//	tile size
	BYTE		byOption;		//	tile option byte
	BYTE		byDrawID;		//	tile ID
}TILE;

typedef struct tagInfo
{
	D3DXVECTOR3	vPos;
	D3DXVECTOR3	vDir;
	D3DXVECTOR3	vLook;
	D3DXMATRIX	matWorld;
}INFO;

typedef struct tagMonster
{
	int m_iMaxHP;
	int m_iHP;
	int m_iAttk;
	int m_iMonType;
	int	m_iState;
	//D3DXVECTOR3 vPos;
	//	D3DXVECTOR3 vSize;
	//����� ���ؼ��� ��Ʈ�ڽ��� ���� �������� Ȥ�� �ؽ����� ������� ��������� ����
	//����� �� �޼��尡 ������ �ʾ����Ƿ� �ּ�ó���Ѵ�.

}MONSTER;

typedef struct tagPlayer
{
	int m_iMaxHP;
	int m_iHP;
	int m_iAttk;
	int	m_iLevel;
	int	m_iExp;
	int	m_iMemory;
	int	m_iState;

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vDir;
	//	D3DXVECTOR3 vSize;
	//	����� ���װ� ����
}PLAYER;


//PathFind
typedef struct tagTexturePath
{
	wstring		wstrObjKey;
	wstring		wstrStateKey;	
	wstring		wstrPath;		
	int			iCount;			

	tagTexturePath(void)
		:wstrObjKey(L""), wstrStateKey(L""), wstrPath(L""), iCount(0){;}
}IMGPATH;

typedef struct	tagSPath
{
	wstring		wstrObjKey;
	wstring		wstrImagePath;
}SPATH;

typedef	struct tagFrame
{
	float	fFrame;
	float	fCount;
	float	fMax;
	tagFrame(void){}
	tagFrame(float _fFrame, float _fCount, float _fMax)
		:fFrame(_fFrame), fCount(_fCount), fMax(_fMax){}
}FRAME;

typedef struct tagAStarNode
{
	float	fCost;
	int		iIndex;
	tagAStarNode*	pParent;
}NODE;

typedef struct tagPathInfo
{
	POINT	ptPos;
	float	fAngle;
}PATHINFO;

#include <queue>

typedef struct tagAction
{
	int		iPressNum;		//	���� ��ȣ�� ���� (��ų�� ������ ���ؼ�)
	float	fAngle;			//	���� ����
	
	D3DXVECTOR3	vDest;		//	Astar bool�� true�� ���

	bool	bSkill;			//	��ų�� ����ϳ� ���ϳ�
	bool	bAStarMove;		//	���̽�Ÿ ���긦 �ߴ��� ���ߴ���

	//	bool �� �Ѵ� false�϶�
	//	pathInfo���� ���ͼ� �ϵ��� �Ѵ�.
	queue<PATHINFO>	quePathSave;

	tagAction()
		: iPressNum(0), bAStarMove(false), bSkill(false), vDest(0.f, 0.f, 0.f),
		fAngle(0) { }
}ACTION;

#endif // Struct_h__

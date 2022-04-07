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
	//사이즈에 대해서는 히트박스를 따로 지정할지 혹은 텍스쳐의 사이즈로 사용할지에 대해
	//제대로 된 메서드가 나오지 않았으므로 주석처리한다.

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
	//	상기의 사항과 동일
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
	int		iPressNum;		//	누른 번호를 저장 (스킬의 실행을 위해서)
	float	fAngle;			//	각도 저장
	
	D3DXVECTOR3	vDest;		//	Astar bool이 true인 경우

	bool	bSkill;			//	스킬을 사용하냐 안하냐
	bool	bAStarMove;		//	에이스타 무브를 했는지 안했는지

	//	bool 이 둘다 false일때
	//	pathInfo에서 빼와서 하도록 한다.
	queue<PATHINFO>	quePathSave;

	tagAction()
		: iPressNum(0), bAStarMove(false), bSkill(false), vDest(0.f, 0.f, 0.f),
		fAngle(0) { }
}ACTION;

#endif // Struct_h__

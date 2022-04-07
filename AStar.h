#pragma once

class CBackGround;
class CAStar
{ 
	DECLARE_SINGLETON(CAStar)
private:
	vector<TILE*>*	m_pVecTile;

public:
	void	SetTile(vector<TILE*>* _vecTile)
	{
		m_pVecTile = _vecTile;
	}

	vector<TILE*>*	GetTile(void)
	{
		return m_pVecTile;
	}

private:
	int				m_iStartIndex;
	int				m_iGoalIndex;

public:
	D3DXVECTOR3		GetGoalPos(void)
	{
		return (*m_pVecTile)[m_iGoalIndex]->vPos;
	}

private:
	list<NODE*>		m_OpenList;		//내가 방문해야 할 대상..
	list<NODE*>		m_CloseList;	//이미 조사한 대상(방문할 필요가 없음)
	list<int>		m_BestList;		//경로를 찾았을 때 이동할 인덱스를 모아둔 리스트...
public:
	list<int>*		GetBestList(void);
public:
	void	AStarStart(const int& iStartIndex, const int& iGoalIndex);
	CBackGround*	m_pBackGround;
	void	MakeRoute(void);
	void	Release(void);
	bool	CheckList(const int& iIndex);
	NODE*	MakeNode(int _iIndex, NODE* _pCurNode, const vector<TILE*>* _pVecTile);
	static bool	ComPare(const NODE*	pNode1, const NODE*	pNode2);

	bool	Picking(const D3DXVECTOR3&	vPos, const int& iIndex);
	int		GetTileIndex(const D3DXVECTOR3&	vPos);
	void	AStarStartPos(const D3DXVECTOR3& vStartPos,
		const D3DXVECTOR3& vGoalPos);
public:
	CAStar(void);
	~CAStar(void);
};

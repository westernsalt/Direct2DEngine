#include "StdAfx.h"
#include "AStar.h"
#include "ObjMgr.h"

IMPLEMENT_SINGLETON(CAStar)

CAStar::CAStar(void)
{ 
	m_iGoalIndex = 0;
	m_iStartIndex = 0;
}

CAStar::~CAStar(void)
{
}

void CAStar::AStarStart(const int& iStartIndex, const int& iGoalIndex)
{
	if(iStartIndex == iGoalIndex)
		return;

	if(m_pVecTile == NULL)
		return;

	//가야할 타일이 이동 불가 타일이라면 그냥 나가라...

	if((*m_pVecTile)[iGoalIndex]->byOption == 1)
		return;

	Release();

	m_iStartIndex = iStartIndex;
	m_iGoalIndex = iGoalIndex;

	MakeRoute();

}

void CAStar::Release(void)
{
	for(list<NODE*>::iterator iter = m_OpenList.begin();
		iter != m_OpenList.end(); ++iter)
	{
		delete *iter;
	}
	m_OpenList.clear();

	for(list<NODE*>::iterator iter = m_CloseList.begin();
		iter != m_CloseList.end(); ++iter)
	{
		delete *iter;
	}
	m_CloseList.clear();

	m_BestList.clear();

}

void CAStar::MakeRoute(void)
{
	//경로를 완성해 나가는 함수...
	NODE*	pCurNode = new NODE;
	pCurNode->iIndex = m_iStartIndex;

	//최초 생성된 놈은 부모 노드가 없다..
	pCurNode->pParent = NULL;
	//이동 비용 또한 존재할 수 없음...
	pCurNode->fCost = 0.f;

	//스타트 인덱스는 더 방문할 필요가 없으므로... closelist 에 추가한다..
	m_CloseList.push_back(pCurNode);

	if(m_pVecTile == NULL)
		return;

	NODE*	pNode = NULL;
	int		iIndex = 0;

	while(true)
	{
		//1.맵상에 존재하는 인덱스의 노드인가?
		//2.옵션 값이 0이여서 갈 수 있는 노드인가?
		//3.오픈 리스트 안에 없고 클로즈 리스트 안에 없는 노드인가?

		//위쪽 타일하고 아래쪽 타일하고 비교를 해 봤을 때...

		//위쪽 방향...체크....
		iIndex = pCurNode->iIndex - TILECNTX * 2;

		if(iIndex < 0 || iIndex >= ((int)(m_pVecTile->size())))
		{
			return;
		}

		if(pCurNode->iIndex >= TILECNTX * 2 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//아래쪽 방향 체크...
		iIndex = pCurNode->iIndex + TILECNTX * 2;
		if( (pCurNode->iIndex < (TILECNTX * TILECNTY) - (TILECNTX * 2)) &&
			((*m_pVecTile)[iIndex]->byOption == 0 ) &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//왼쪽 방향 체크...
		iIndex = pCurNode->iIndex - 1;
		if(pCurNode->iIndex % TILECNTX != 0 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//오른쪽 방향 체크...
		iIndex = pCurNode->iIndex + 1;
		if(pCurNode->iIndex % TILECNTX != TILECNTX - 1 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//오른쪽 위 방향 체크...
		iIndex = pCurNode->iIndex - (TILECNTX - (pCurNode->iIndex / TILECNTX) % 2);

		if(pCurNode->iIndex >= TILECNTX &&
			pCurNode->iIndex % (TILECNTX * 2) != (TILECNTX * 2) - 1 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//오른쪽 아래 방향 체크...
		iIndex = pCurNode->iIndex + (TILECNTX + (pCurNode->iIndex / TILECNTX) % 2);

		if(pCurNode->iIndex < (TILECNTX * TILECNTY) - TILECNTX &&
			pCurNode->iIndex % (TILECNTX * 2) != TILECNTX * 2 - 1 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//왼쪽 아래 방향 체크...
		iIndex = pCurNode->iIndex + (TILECNTX + (pCurNode->iIndex / TILECNTX) % 2) - 1;

		if(pCurNode->iIndex < (TILECNTX * TILECNTY) - TILECNTX &&
			pCurNode->iIndex % (TILECNTX * 2) != 0 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//왼쪽 위 방향 체크...
		iIndex = pCurNode->iIndex - (TILECNTX - (pCurNode->iIndex / TILECNTX) % 2) - 1;

		if(pCurNode->iIndex >= TILECNTX &&
			pCurNode->iIndex % (TILECNTX * 2) != 0 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		m_OpenList.sort(ComPare);

		list<NODE*>::iterator iter = m_OpenList.begin();



		//	******************************************************
		//	iter뻑나길래 한번 추가해본 코드
		if(iter == m_OpenList.end())
		{
			return;
		}
		//	******************************************************



		pCurNode = *iter;

		m_CloseList.push_back(*iter);
		m_OpenList.erase(iter);

		if(pCurNode->iIndex == m_iGoalIndex)
		{
			while(true)
			{
				m_BestList.push_back(pCurNode->iIndex);

				//부모 노드를 계속 역추적 하면서 베스트 리스트에 저장한다...
				pCurNode = pCurNode->pParent;

				if(pCurNode->iIndex == m_iStartIndex)
					break;	
			}
			m_BestList.reverse();
			break;
		}

	}
}

bool CAStar::CheckList(const int& iIndex)
{
	for(list<NODE*>::iterator iter = m_OpenList.begin();
		iter != m_OpenList.end(); ++iter)
	{
		if((*iter)->iIndex == iIndex)
			return false;
	}

	for(list<NODE*>::iterator iter = m_CloseList.begin();
		iter != m_CloseList.end(); ++iter)
	{
		if((*iter)->iIndex == iIndex)
			return false;
	}

	return true;
}

NODE* CAStar::MakeNode(int _iIndex, NODE* _pCurNode, const vector<TILE*>* _m_pVecTile)
{
	NODE*	pNode = new NODE;
	pNode->iIndex = _iIndex;
	pNode->pParent = _pCurNode;

	//한칸을 이동하기 위한 벡터...
	D3DXVECTOR3	vDistance = (*_m_pVecTile)[_iIndex]->vPos - (*_m_pVecTile)[_pCurNode->iIndex]->vPos;

	//실제 거리 스칼라 값..
	float fPCost = D3DXVec3Length(&vDistance);

	//현재 위치에서 도착위치까지 가는 벡터...
	vDistance = (*_m_pVecTile)[_iIndex]->vPos - (*_m_pVecTile)[m_iGoalIndex]->vPos;

	//위의 인접 노드에서 부터 목표지점까지의 거리..
	float fGCost = D3DXVec3Length(&vDistance);

	//플레이어 위치에서 목표지점까지의 거리..
	pNode->fCost = fPCost + fGCost;

	return pNode;
}

bool CAStar::ComPare(const NODE* pNode1, const NODE* pNode2)
{
	return pNode1->fCost < pNode2->fCost;
}

bool CAStar::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
{
	float fGradient = (TILESIZEY / 2.f) / (TILESIZEX / 2.f);

	D3DXVECTOR3	vPoint[4] = 
	{
		D3DXVECTOR3((*m_pVecTile)[iIndex]->vPos.x, (*m_pVecTile)[iIndex]->vPos.y - TILESIZEY / 2.f, 0),

		D3DXVECTOR3((*m_pVecTile)[iIndex]->vPos.x + TILESIZEX / 2.f, (*m_pVecTile)[iIndex]->vPos.y, 0.f),

		D3DXVECTOR3((*m_pVecTile)[iIndex]->vPos.x, (*m_pVecTile)[iIndex]->vPos.y + TILESIZEY / 2.f, 0.f),

		D3DXVECTOR3((*m_pVecTile)[iIndex]->vPos.x - TILESIZEX / 2.f, (*m_pVecTile)[iIndex]->vPos.y, 0.f)
	};


	D3DXVECTOR3	vDirection[4] = 
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	//법선 벡터를 만들어 보자...
	D3DXVECTOR3 vNormal[4] = 
	{
		D3DXVECTOR3(vDirection[0].y, -vDirection[0].x, 0.f),
		D3DXVECTOR3(vDirection[1].y, -vDirection[1].x, 0.f),
		D3DXVECTOR3(vDirection[2].y, -vDirection[2].x, 0.f),
		D3DXVECTOR3(vDirection[3].y, -vDirection[3].x, 0.f),
	};

	//단위 벡터 만들기
	for(int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
	}

	for(int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3	vDestDir = vPos - vPoint[i];

		float fDotResult = D3DXVec3Dot(&vDestDir, &vNormal[i]);

		if(fDotResult > 0.f)
			return false;
	}

	return true;
}

int CAStar::GetTileIndex(const D3DXVECTOR3& vPos)
{
	for(size_t i = 0; i != m_pVecTile->size(); ++i)
	{
		if(Picking(vPos, i))
		{
			return i;
		}
	}
	return -1;
}

void CAStar::AStarStartPos(const D3DXVECTOR3& vStartPos, const D3DXVECTOR3& vGoalPos)
{
	m_iStartIndex = GetTileIndex(vStartPos);
	m_iGoalIndex = GetTileIndex(vGoalPos);

	AStarStart(m_iStartIndex, m_iGoalIndex);
}

list<int>* CAStar::GetBestList(void)
{
	return &m_BestList;
}

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

	//������ Ÿ���� �̵� �Ұ� Ÿ���̶�� �׳� ������...

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
	//��θ� �ϼ��� ������ �Լ�...
	NODE*	pCurNode = new NODE;
	pCurNode->iIndex = m_iStartIndex;

	//���� ������ ���� �θ� ��尡 ����..
	pCurNode->pParent = NULL;
	//�̵� ��� ���� ������ �� ����...
	pCurNode->fCost = 0.f;

	//��ŸƮ �ε����� �� �湮�� �ʿ䰡 �����Ƿ�... closelist �� �߰��Ѵ�..
	m_CloseList.push_back(pCurNode);

	if(m_pVecTile == NULL)
		return;

	NODE*	pNode = NULL;
	int		iIndex = 0;

	while(true)
	{
		//1.�ʻ� �����ϴ� �ε����� ����ΰ�?
		//2.�ɼ� ���� 0�̿��� �� �� �ִ� ����ΰ�?
		//3.���� ����Ʈ �ȿ� ���� Ŭ���� ����Ʈ �ȿ� ���� ����ΰ�?

		//���� Ÿ���ϰ� �Ʒ��� Ÿ���ϰ� �񱳸� �� ���� ��...

		//���� ����...üũ....
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

		//�Ʒ��� ���� üũ...
		iIndex = pCurNode->iIndex + TILECNTX * 2;
		if( (pCurNode->iIndex < (TILECNTX * TILECNTY) - (TILECNTX * 2)) &&
			((*m_pVecTile)[iIndex]->byOption == 0 ) &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//���� ���� üũ...
		iIndex = pCurNode->iIndex - 1;
		if(pCurNode->iIndex % TILECNTX != 0 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//������ ���� üũ...
		iIndex = pCurNode->iIndex + 1;
		if(pCurNode->iIndex % TILECNTX != TILECNTX - 1 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//������ �� ���� üũ...
		iIndex = pCurNode->iIndex - (TILECNTX - (pCurNode->iIndex / TILECNTX) % 2);

		if(pCurNode->iIndex >= TILECNTX &&
			pCurNode->iIndex % (TILECNTX * 2) != (TILECNTX * 2) - 1 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//������ �Ʒ� ���� üũ...
		iIndex = pCurNode->iIndex + (TILECNTX + (pCurNode->iIndex / TILECNTX) % 2);

		if(pCurNode->iIndex < (TILECNTX * TILECNTY) - TILECNTX &&
			pCurNode->iIndex % (TILECNTX * 2) != TILECNTX * 2 - 1 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//���� �Ʒ� ���� üũ...
		iIndex = pCurNode->iIndex + (TILECNTX + (pCurNode->iIndex / TILECNTX) % 2) - 1;

		if(pCurNode->iIndex < (TILECNTX * TILECNTY) - TILECNTX &&
			pCurNode->iIndex % (TILECNTX * 2) != 0 &&
			(*m_pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pCurNode, m_pVecTile);
			m_OpenList.push_back(pNode);
		}

		//���� �� ���� üũ...
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
		//	iter�����淡 �ѹ� �߰��غ� �ڵ�
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

				//�θ� ��带 ��� ������ �ϸ鼭 ����Ʈ ����Ʈ�� �����Ѵ�...
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

	//��ĭ�� �̵��ϱ� ���� ����...
	D3DXVECTOR3	vDistance = (*_m_pVecTile)[_iIndex]->vPos - (*_m_pVecTile)[_pCurNode->iIndex]->vPos;

	//���� �Ÿ� ��Į�� ��..
	float fPCost = D3DXVec3Length(&vDistance);

	//���� ��ġ���� ������ġ���� ���� ����...
	vDistance = (*_m_pVecTile)[_iIndex]->vPos - (*_m_pVecTile)[m_iGoalIndex]->vPos;

	//���� ���� ��忡�� ���� ��ǥ���������� �Ÿ�..
	float fGCost = D3DXVec3Length(&vDistance);

	//�÷��̾� ��ġ���� ��ǥ���������� �Ÿ�..
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

	//���� ���͸� ����� ����...
	D3DXVECTOR3 vNormal[4] = 
	{
		D3DXVECTOR3(vDirection[0].y, -vDirection[0].x, 0.f),
		D3DXVECTOR3(vDirection[1].y, -vDirection[1].x, 0.f),
		D3DXVECTOR3(vDirection[2].y, -vDirection[2].x, 0.f),
		D3DXVECTOR3(vDirection[3].y, -vDirection[3].x, 0.f),
	};

	//���� ���� �����
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

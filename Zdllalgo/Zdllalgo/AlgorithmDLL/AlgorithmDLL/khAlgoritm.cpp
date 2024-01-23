#include "pch.h"
#include "khAlgoritm.h"

using namespace std;

//���� �������� ��Ʈ�� ���� �׷��� ���� ������ �޾Ƽ�
//�����ϱ� ���ϵ��� �з��ؼ� ��� �Լ�
vector<vector<GraphInfo>*>* GraphInfoSetting(void* _ptr, int _iArrCount)
{
    //Input GraphInfo
    GraphInfo* pGraphInfoArry = reinterpret_cast<GraphInfo*>(_ptr);

    vector<vector<GraphInfo>*>* vecNodeNearnodeGraphInfoPtrPtr;

    int iNodeCount = 0;
    int iNodeTemp = -1;
    //1. �̾��� ��尡 �ִ� �� ��� ���� ���ϱ� (������ ��尰�� �߰������� �̾����� ��尡 ������ ���� ī��Ʈ x)
    for (int i = 0; i < _iArrCount; ++i)
    {
        if (iNodeTemp != pGraphInfoArry[i].iNode)
        {
            iNodeTemp = pGraphInfoArry[i].iNode;
            iNodeCount++;
        }
    }
    //2. ��� ���� �������� ���ֱ�
    vecNodeNearnodeGraphInfoPtrPtr = new vector<vector<GraphInfo>*>(iNodeCount, nullptr);
    //3. �� ��帶�� vector<GraphInfo>�� ������ֱ�
    iNodeCount = 0;
    iNodeTemp = -1;
    int iNearnodeCount = 0;
    int iIndexTemp = 0;

    vector<GraphInfo>* vecGraphInfoPtr = nullptr;
    //���� ������ŭ �����ش�.
    for (int i = 0; i < _iArrCount; ++i)
    {
        //���ο� ����� �����̶��
        if (iNodeTemp != pGraphInfoArry[i].iNode)
        {
            //���ο� ����� �˷��ش�.
            iNodeTemp = pGraphInfoArry[i].iNode;
            //����ϰ� ����
            if (vecGraphInfoPtr != nullptr)
            {
                vecGraphInfoPtr->shrink_to_fit();
            }
            //���� �������ش�
            vecGraphInfoPtr = new vector<GraphInfo>();
            //ù ��� �־��ֱ�
            vecGraphInfoPtr->push_back(pGraphInfoArry[i]);
            (*vecNodeNearnodeGraphInfoPtrPtr)[iNodeCount++] = vecGraphInfoPtr;
        }
        else
        {
            //������ ���� ����ڵ�
            if (vecGraphInfoPtr != nullptr)
            {
                vecGraphInfoPtr->push_back(pGraphInfoArry[i]);
            }
        }
    }

    return vecNodeNearnodeGraphInfoPtrPtr;
}

vector<GraphInfo>* GraphInfoSetting_SingleVector(void* _ptr, int _iArrCount)
{
    GraphInfo* pGraphInfoArry = reinterpret_cast<GraphInfo*>(_ptr);
    vector<GraphInfo>* vecGraphInfoPtr = new vector<GraphInfo>();

    for (int i = 0; i < _iArrCount; ++i)
    {
        vecGraphInfoPtr->push_back(pGraphInfoArry[i]);
    }

    return vecGraphInfoPtr;
}

void DeleteNodeNearnodeGraphInfoPtrPtr(vector<vector<GraphInfo>*>* _vecNodeNearnodeGraphInfoPtrPtr)
{
    int iNodeCount = _vecNodeNearnodeGraphInfoPtrPtr->size();
    for (int i = 0; i < iNodeCount; ++i)
    {
        delete (*_vecNodeNearnodeGraphInfoPtrPtr)[i];
        (*_vecNodeNearnodeGraphInfoPtrPtr)[i] = nullptr;
    }

    delete _vecNodeNearnodeGraphInfoPtrPtr;
    _vecNodeNearnodeGraphInfoPtrPtr = nullptr;
}

void DeleteNodeGraphInfoPtr(vector<GraphInfo>* _vecNodeGraphInfoPtr)
{
    delete _vecNodeGraphInfoPtr;
    _vecNodeGraphInfoPtr = nullptr;
}


int GetNodeCount(vector<vector<GraphInfo>*>* _vecNodeNearnodeGraphInfoPtrPtr, bool _bPlus1 = false)
{
    unordered_set<int> Nodes;

    int iSize = _vecNodeNearnodeGraphInfoPtrPtr->size();
    int iSize2;
    vector<GraphInfo>* vecGraphInfoTemp;
    for (int i = 0; i < iSize; ++i)
    {
        vecGraphInfoTemp = (*_vecNodeNearnodeGraphInfoPtrPtr)[i];
        iSize2 = (*_vecNodeNearnodeGraphInfoPtrPtr)[i]->size();
        for (int j = 0; j < iSize2; ++j)
        {
            if (Nodes.find((*vecGraphInfoTemp)[j].iNode) == Nodes.end())
            {
                Nodes.insert((*vecGraphInfoTemp)[j].iNode);
            }
            if (Nodes.find((*vecGraphInfoTemp)[j].iNearNode) == Nodes.end())
            {
                Nodes.insert((*vecGraphInfoTemp)[j].iNearNode);
            }
        }
    }

    //�ε��� ��ȣ = ����ȣ ���� ��
    if (_bPlus1)
    {
        return (Nodes.size() + 1);
    }
    return Nodes.size();
}

int GetNodeCount(vector<GraphInfo>* _vecGraphInfoPtr, bool _bPlus1 = false)
{
    unordered_set<int> Nodes;

    int iSize = _vecGraphInfoPtr->size();
    for (int i = 0; i < iSize; ++i)
    {
        if (Nodes.find((*_vecGraphInfoPtr)[i].iNode) == Nodes.end())
        {
            Nodes.insert((*_vecGraphInfoPtr)[i].iNode);
        }
        if (Nodes.find((*_vecGraphInfoPtr)[i].iNearNode) == Nodes.end())
        {
            Nodes.insert((*_vecGraphInfoPtr)[i].iNearNode);
        }
    }

    //�ε��� ��ȣ = ����ȣ ���� ��
    if (_bPlus1)
    {
        return (Nodes.size() + 1);
    }
    return Nodes.size();
}

//_vecNodeNearnodeGraphInfoPtrPtr�� 0������ �迭�̰� ��� ��ȣ�� �ε����� �ƴϹǷ� ��� ��ȣ�� �´� �ε�����
//vector<GraphInfo>*�� ã�Ƽ� �Ѱ��ش�.
vector<GraphInfo>* FindNodevecGraphInfo(vector<vector<GraphInfo>*>* _vecNodeNearnodeGraphInfoPtrPtr, int _iNode)
{
    int iSize = (*_vecNodeNearnodeGraphInfoPtrPtr).size();
    for (int i = 0; i < iSize; ++i)
    {
        if ((*(*_vecNodeNearnodeGraphInfoPtrPtr)[i])[0].iNode == _iNode)
        {
            return (*_vecNodeNearnodeGraphInfoPtrPtr)[i];
        }
    }

    return nullptr;
}

GraphInfo* ChangeGraphInfoVectorPtrToArryPtr(vector<GraphInfo>* _vecGraphInfoPtr, bool _bBack = false)
{
    _vecGraphInfoPtr->shrink_to_fit();
    int iSize = _vecGraphInfoPtr->size();
    GraphInfo* pGraphInfoArry = new GraphInfo[iSize];
    if (_bBack) //���� ������ �� ���� �ִ´�
    {
        int iIndex = 0;
        for (int i = iSize - 1; i >= 0; --i)
        {
            pGraphInfoArry[iIndex++] = (*_vecGraphInfoPtr)[i];
        }
    }
    else
    {
        for (int i = 0; i < iSize; ++i)
        {
            pGraphInfoArry[i] = (*_vecGraphInfoPtr)[i];
        }
    }

    return pGraphInfoArry;
}

int* ChangeIntVectorPtrToArryPtr(vector<int>* _vecNodePtr, bool _bBack = false)
{
    _vecNodePtr->shrink_to_fit();
    int iSize = _vecNodePtr->size();
    int* pNodeArry = new int[iSize];
    if (_bBack) //���� ������ �� ���� �ִ´�
    {
        int iIndex = 0;
        for (int i = iSize - 1; i >= 0; --i)
        {
            pNodeArry[iIndex++] = (*_vecNodePtr)[i];
        }
    }
    else
    {
        for (int i = 0; i < iSize; ++i)
        {
            pNodeArry[i] = (*_vecNodePtr)[i];
        }
    }

    return pNodeArry;
}

GraphInfo FindGraphInfo(vector<vector<GraphInfo>*>* _vecNodeNearnodeGraphInfoPtrPtr, int _iNode, int _iNearNode)
{
    vector<GraphInfo>* vecGraphInfo = FindNodevecGraphInfo(_vecNodeNearnodeGraphInfoPtrPtr, _iNode);
    int iDebugTestTemp = 0;
    for (int i = 0; i < vecGraphInfo->size(); i++)
    {
        if ((*vecGraphInfo)[i].iNearNode == _iNearNode)
        {
            return (*vecGraphInfo)[i];
        }
    }

    return GraphInfo();
}

//Dijkstra
//ù ������ �� �� �ִ� Ư�� ������ ���� �Ÿ����� ��� �����ϸ�
//���� ���� ���� �Ÿ��� �i�� ���� �˰���
GraphInfo* Dijkstra(void* _ptr, int _iArrCount, int* _iOutArrCount, int _iStartNode, int _iEndNode)
{
    vector<vector<GraphInfo>*>* vecNodeNearnodeGraphInfoPtrPtr = GraphInfoSetting(_ptr, _iArrCount);

    int iINF = INTMAX; //����
    int iNodeCount = (*vecNodeNearnodeGraphInfoPtrPtr).size();// ������ ��尡 �ִ� ��� ��

    //��� ���� �� �Ÿ� ���� ���� �� ��Ƶ� map
    map<int, pair<int,int>> mapNodeDisNearnode;

	//�켱���� ť, pair<�Ÿ�,����ȣ>
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	//������ �߰�
	pq.push({ 0, _iStartNode });
    mapNodeDisNearnode.emplace(_iStartNode,make_pair(0,-1)); //ù ���� �Ÿ��� 0
    //vecDis[_iStartNode] = 0; 

    vector<GraphInfo>* vecGraphInfoTempPtr; //Ư�� ����� ���� ��� ��ȯ�� ���� ��� ��� ���� ����
    int ivectorSizeTemp; //�� ������ ����� ���� ����
    while (!pq.empty()) 
    {
        int iTopNode = pq.top().second; //���� ���
        int iDis = pq.top().first; // ���������� ���� ������ �ִܰŸ�
        pq.pop();

        //���� ���ٸ�
        if (mapNodeDisNearnode.find(iTopNode) == mapNodeDisNearnode.end())
        {
            mapNodeDisNearnode.emplace(iTopNode, make_pair(iINF, -1));
        }
        if (iDis > mapNodeDisNearnode[iTopNode].first) //�̹� ó����? ����� �н�
        {
            continue;
        }

        if (iTopNode == _iEndNode)
        {
            break;
        }

        vecGraphInfoTempPtr = FindNodevecGraphInfo(vecNodeNearnodeGraphInfoPtrPtr, iTopNode);//���� ���� Ȯ���� ���� ��Ƴ���
        ivectorSizeTemp = vecGraphInfoTempPtr->size(); //�� ������ ������(���� ��� ����)
        for (int i = 0; i < ivectorSizeTemp; ++i) //���� �ִܰŸ��� ª�� ����� ���� ������ ��ȯ
        {
            GraphInfo graphInfo = (*vecGraphInfoTempPtr)[i];
            int iNextNode = graphInfo.iNearNode;
            int iNextDis = iDis + graphInfo.iDistance; //���������� Top ������ �Ÿ� + Top ������ ���� ������ �Ÿ�
            if (mapNodeDisNearnode.find(iNextNode) == mapNodeDisNearnode.end())
            {
                mapNodeDisNearnode.emplace(iNextNode, make_pair(iINF, -1));
            }
            if (iNextDis < mapNodeDisNearnode[iNextNode].first)//�ִܰŸ� ����
            {
                mapNodeDisNearnode[iNextNode].first = iNextDis;
                mapNodeDisNearnode[iNextNode].second = iTopNode;
                pq.push(make_pair(iNextDis, iNextNode));
            }
        }
    }

    map<int, pair<int, int>>::iterator iter = mapNodeDisNearnode.begin();
    int iPreEndNode = 0;
    int iEndNode = _iEndNode;

    vector<GraphInfo> vecGraphInfoLoad;

    while (true)
    {
        iPreEndNode = mapNodeDisNearnode[iEndNode].second;
        vecGraphInfoLoad.push_back(FindGraphInfo(vecNodeNearnodeGraphInfoPtrPtr, iPreEndNode, iEndNode));
        iEndNode = iPreEndNode;
        if (iEndNode == _iStartNode)
        {
            break;
        }
    }
    DeleteNodeNearnodeGraphInfoPtrPtr(vecNodeNearnodeGraphInfoPtrPtr);
    *_iOutArrCount = vecGraphInfoLoad.size();
    return ChangeGraphInfoVectorPtrToArryPtr(&vecGraphInfoLoad,true);
}
//Dijkstra

//BFS
int* BFS(void* _ptr, int _iArrCount, int* _iOutArrCount, int _iStartNode)
{
    vector<vector<GraphInfo>*>* vecNodeNearnodeGraphInfoPtrPtr = GraphInfoSetting(_ptr, _iArrCount);

    // �湮 ����, +1�� 10���� 0~9�� �ε��� ���� �����µ�, ����� ���� ���� 0�� ���� ��� ��ȣ = �ε��� �ϱ�����
    //��� 1���� ��� ���� ���� �� ���� (ex 12 456������ �ƴ�) ������� ���� �ִٴ� ���� �Ͽ� ��.
    vector<bool> vecbVisited(GetNodeCount(vecNodeNearnodeGraphInfoPtrPtr, true), false); // �湮 ����
    queue<int> q; // ť
    vector<GraphInfo>* vecGraphInfoTempPtr; //Ư�� ����� ���� ��� ��ȯ�� ���� ��� ��� ���� ����
    vector<int> vecNode;

    vecbVisited[_iStartNode] = true; //ù ��� ���� (�湮)
    q.push(_iStartNode);

    int iTopNode;
    int ivecNearNodeSize;
    while (!q.empty())
    {
        iTopNode = q.front();
        q.pop();
        vecNode.push_back(iTopNode);

        vecGraphInfoTempPtr = FindNodevecGraphInfo(vecNodeNearnodeGraphInfoPtrPtr, iTopNode);
        ivecNearNodeSize = vecGraphInfoTempPtr->size();
        for (int i = 0; i < ivecNearNodeSize; i++)
        {
            int next = (*vecGraphInfoTempPtr)[i].iNearNode;
            if (!vecbVisited[next])
            {
                vecbVisited[next] = true;
                q.push(next);
            }
        }
    }

    DeleteNodeNearnodeGraphInfoPtrPtr(vecNodeNearnodeGraphInfoPtrPtr);
    *_iOutArrCount = vecNode.size();
    return ChangeIntVectorPtrToArryPtr(&vecNode);
}
//BFS

//DFS 
//����Լ�
void DFSCheckVisited(int _iVisitedNode, vector<vector<GraphInfo>*>* _vecNodeNearnodeGraphInfoPtrPtr, vector<bool>* _vecbVisitedPtr,vector<int>* _OutvecNode)
{
    (*_vecbVisitedPtr)[_iVisitedNode] = true;
    _OutvecNode->push_back(_iVisitedNode);

    vector<GraphInfo>* vecGraphInfoTempPtr; //Ư�� ����� ���� ��� ��ȯ�� ���� ��� ��� ���� ����
    vecGraphInfoTempPtr = FindNodevecGraphInfo(_vecNodeNearnodeGraphInfoPtrPtr, _iVisitedNode);
    int iSize = vecGraphInfoTempPtr->size();
    int iNearNodeTemp;
    for (int i = 0; i < iSize; ++i)
    {
        iNearNodeTemp = (*vecGraphInfoTempPtr)[i].iNearNode;
        if (!(*_vecbVisitedPtr)[iNearNodeTemp])
        {
            DFSCheckVisited(iNearNodeTemp, _vecNodeNearnodeGraphInfoPtrPtr, _vecbVisitedPtr, _OutvecNode);
        }
    }
}

int* DFS(void* _ptr, int _iArrCount, int* _iOutArrCount, int _iStartNode)
{
    vector<vector<GraphInfo>*>* vecNodeNearnodeGraphInfoPtrPtr = GraphInfoSetting(_ptr, _iArrCount);

    // �湮 ����, +1�� 10���� 0~9�� �ε��� ���� �����µ�, ����� ���� ���� 0�� ���� ��� ��ȣ = �ε��� �ϱ�����
    //��� 1���� ��� ���� ���� �� ���� (ex 12 456������ �ƴ�) ������� ���� �ִٴ� ���� �Ͽ� ��.
    vector<bool> vecbVisited(GetNodeCount(vecNodeNearnodeGraphInfoPtrPtr,true), false); 
    vector<int> vecNode;
    DFSCheckVisited(_iStartNode, vecNodeNearnodeGraphInfoPtrPtr , &vecbVisited , &vecNode);

    DeleteNodeNearnodeGraphInfoPtrPtr(vecNodeNearnodeGraphInfoPtrPtr);
    *_iOutArrCount = vecNode.size();
    return ChangeIntVectorPtrToArryPtr(&vecNode);
}
//DFS

//Kruskal
// �θ� ��带 ã�� �Լ�
int KruskalFindParentNode(int _iNode, vector<int>& _vecNodeParent)
{
    if (_iNode == _vecNodeParent[_iNode])
    {
        return _iNode;
    }
    int iLastParentsNode = KruskalFindParentNode(_vecNodeParent[_iNode], _vecNodeParent);
    return iLastParentsNode;
}

//// �� ��带 ������ ��, ���� �ݴ� ���⿡�� �ڽ��� Ÿ�� �������� ���� ���̹Ƿ�, �ϳ��� ��� Ʈ���� �ڽ� �θ� ������ �����ش�.
//void KruskalInvertParentNodes(int _iNode, vector<int>& _vecNodeParent)
//{
//    int iNode = _iNode;
//    int iParentNode;
//    int iNextParentNode;
//    while(true)
//    {
//        //�ٷ� �� �θ� ��带 ã�´�
//        iParentNode = _vecNodeParent[iNode];
//        //�θ� ����� �θ� ��� ������ ���´�.
//        iNextParentNode = _vecNodeParent[iParentNode];
//        //�θ� ��忡 �ڽ��� ��带 �θ�� �ִ´�.
//        _vecNodeParent[iParentNode] = iNode;
//        //�θ� ��带 �ٽ� iNode�� �����Ѵ�
//        iParentNode = iNode;
//
//        //���� �θ��� �θ� ���� �θ� ��尡 ���ٸ� ������.
//        if (iParentNode == iNextParentNode)
//        {
//            break;
//        }
//
//        //�θ��� �θ� ��带 �θ� ���� �����Ѵ�.
//        iParentNode = iNextParentNode;
//    }
//}

int* Kruskal(void* _ptr, int _iArrCount, int* _iOutArrCount)
{
    vector<GraphInfo>* vecGraphInfoPtr = GraphInfoSetting_SingleVector(_ptr, _iArrCount);
    
    //¦����°(+0) - Ȧ����°�� �̾��� ����
    vector<int> vecConnectedNode;

    //������ ����ġ ������ ����
    sort(vecGraphInfoPtr->begin(), vecGraphInfoPtr->end(), [](GraphInfo _A, GraphInfo _B) {return _A.iDistance < _B.iDistance; });

    //����� �θ� ��� �ʱ�ȭ
    vector<int> vecNodeParent(GetNodeCount(vecGraphInfoPtr,true));
    int ivecNodeParentSize = vecNodeParent.size();
    for (int i = 0; i < ivecNodeParentSize; ++i)
    {
        vecNodeParent[i] = i;
    }

    // �ּ� ���� Ʈ���� ����ġ ��, �ʿ��ϴٸ� �� ��. ���ظ� ����
    int iCost = 0;
    // ������ �ϳ��� �߰��ϸ� �ּ� ���� Ʈ�� ����
    for (int i = 0; i < _iArrCount; ++i)
    {
        int iNode1 = (*vecGraphInfoPtr)[i].iNode;
        int iNode2 = (*vecGraphInfoPtr)[i].iNearNode;
        int iWeight = (*vecGraphInfoPtr)[i].iDistance;

        //�� ��带 ��ġ�� �κ�
        int iNode1Parent = KruskalFindParentNode(iNode1, vecNodeParent);
        int iNode2Parent = KruskalFindParentNode(iNode2, vecNodeParent);
        if (iNode1Parent != iNode2Parent)
        {
            //�̾��� ��� �߰�
            vecConnectedNode.push_back(iNode1);
            vecConnectedNode.push_back(iNode2);

            //KruskalInvertParentNodes(iNode2,vecNodeParent);
            vecNodeParent[iNode2Parent] = iNode1Parent;
            iCost += iWeight;
        }
    }

    //vector<int> vecNode;
    //int iNodeTemp = (*vecGraphInfoPtr)[0].iNode;
    //for (int i = 0; i < ivecNodeParentSize; ++i)
    //{
    //    if (iNodeTemp == vecNodeParent[iNodeTemp])
    //    {
    //        break;
    //    }
    //    vecNode.push_back(iNodeTemp);
    //    iNodeTemp = vecNodeParent[iNodeTemp];
    //}

    //DeleteNodeGraphInfoPtr(vecGraphInfoPtr);
    //*_iOutArrCount = vecNode.size();
    //return ChangeIntVectorPtrToArryPtr(&vecNode);

    //�������� ����ġ ���� �߰�
    vecConnectedNode.push_back(iCost);
    * _iOutArrCount = vecConnectedNode.size();
    return ChangeIntVectorPtrToArryPtr(&vecConnectedNode);
}
//Kruskal

//AABB
bool AABB(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D)
{
    if (_ABoxPos2D.fRight < _BBoxPos2D.fLeft || _ABoxPos2D.fLeft > _BBoxPos2D.fRight
        || _ABoxPos2D.fBottom > _BBoxPos2D.fTop || _ABoxPos2D.fTop < _BBoxPos2D.fBottom) 
    {
        return false; // ��ġ�� ������ ����
    }
    return true; // ��ġ�� ������ �ִ�
}
bool AABB_ArryPtr(void* _ptr, int _iBox1Index, int _iBox2Index)
{
    BoxPos2D* pBoxPos2DArry = reinterpret_cast<BoxPos2D*>(_ptr);

    if(pBoxPos2DArry[_iBox1Index].fRight < pBoxPos2DArry[_iBox2Index].fLeft || pBoxPos2DArry[_iBox1Index].fLeft > pBoxPos2DArry[_iBox2Index].fRight
        || pBoxPos2DArry[_iBox1Index].fBottom > pBoxPos2DArry[_iBox2Index].fTop || pBoxPos2DArry[_iBox1Index].fTop < pBoxPos2DArry[_iBox2Index].fBottom)
    {
        return false; // ��ġ�� ������ ����
    }
    return true; // ��ġ�� ������ �ִ�
}
bool AABB_Overlap(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D)
{
    //x�࿡�� ��ġ�� ����
    float fOverlapX = max(0.0f, min(_ABoxPos2D.fRight, _BBoxPos2D.fRight) - max(_ABoxPos2D.fLeft, _BBoxPos2D.fLeft));

    //y�࿡�� ��ġ�� ����
    float fOverlapY = max(0.0f, min(_ABoxPos2D.fTop, _BBoxPos2D.fTop) - max(_ABoxPos2D.fBottom, _BBoxPos2D.fBottom));

    // x��� y�࿡�� ��ġ�� ������ ������ �浹�� �����մϴ�.
    if (fOverlapX > 0 && fOverlapY > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//AABB

void FreeGraphInfoArryPtr(void* _ptr)
{
    delete[] static_cast<GraphInfo*>(_ptr);
    _ptr = nullptr;
}
void FreeIntArryPtr(void* _ptr)
{
    delete[] static_cast<int*>(_ptr);
    _ptr = nullptr;
}

#include "pch.h"
#include "khAlgoritm.h"

using namespace std;

//구글 스프레드 시트에 적힌 그래프 인포 형식을 받아서
//가공하기 편하도록 분류해서 담는 함수
vector<vector<GraphInfo>*>* GraphInfoSetting(void* _ptr, int _iArrCount)
{
    //Input GraphInfo
    GraphInfo* pGraphInfoArry = reinterpret_cast<GraphInfo*>(_ptr);

    vector<vector<GraphInfo>*>* vecNodeNearnodeGraphInfoPtrPtr;

    int iNodeCount = 0;
    int iNodeTemp = -1;
    //1. 이어진 노드가 있는 총 노드 갯수 구하기 (마지막 노드같이 추가적으로 이어지는 노드가 없으면 갯수 카운트 x)
    for (int i = 0; i < _iArrCount; ++i)
    {
        if (iNodeTemp != pGraphInfoArry[i].iNode)
        {
            iNodeTemp = pGraphInfoArry[i].iNode;
            iNodeCount++;
        }
    }
    //2. 노드 수로 리사이즈 해주기
    vecNodeNearnodeGraphInfoPtrPtr = new vector<vector<GraphInfo>*>(iNodeCount, nullptr);
    //3. 각 노드마다 vector<GraphInfo>를 만들어주기
    iNodeCount = 0;
    iNodeTemp = -1;
    int iNearnodeCount = 0;
    int iIndexTemp = 0;

    vector<GraphInfo>* vecGraphInfoPtr = nullptr;
    //들어온 갯수만큼 돌려준다.
    for (int i = 0; i < _iArrCount; ++i)
    {
        //새로운 노드의 시작이라면
        if (iNodeTemp != pGraphInfoArry[i].iNode)
        {
            //새로운 노드라고 알려준다.
            iNodeTemp = pGraphInfoArry[i].iNode;
            //깔쌈하게 정리
            if (vecGraphInfoPtr != nullptr)
            {
                vecGraphInfoPtr->shrink_to_fit();
            }
            //새로 생성해준다
            vecGraphInfoPtr = new vector<GraphInfo>();
            //첫 노드 넣어주기
            vecGraphInfoPtr->push_back(pGraphInfoArry[i]);
            (*vecNodeNearnodeGraphInfoPtrPtr)[iNodeCount++] = vecGraphInfoPtr;
        }
        else
        {
            //만약을 위해 방어코딩
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

    //인덱스 번호 = 노드번호 해줄 때
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

    //인덱스 번호 = 노드번호 해줄 때
    if (_bPlus1)
    {
        return (Nodes.size() + 1);
    }
    return Nodes.size();
}

//_vecNodeNearnodeGraphInfoPtrPtr는 0번부터 배열이고 노드 번호가 인덱스가 아니므로 노드 번호에 맞는 인덱스의
//vector<GraphInfo>*를 찾아서 넘겨준다.
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
    if (_bBack) //들어온 벡터의 뒤 부터 넣는다
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
    if (_bBack) //들어온 벡터의 뒤 부터 넣는다
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
//첫 노드부터 갈 수 있는 특정 노드까지 가는 거리들을 계속 갱신하며
//가장 값이 작은 거리를 쫒아 가는 알고리즘
GraphInfo* Dijkstra(void* _ptr, int _iArrCount, int* _iOutArrCount, int _iStartNode, int _iEndNode)
{
    vector<vector<GraphInfo>*>* vecNodeNearnodeGraphInfoPtrPtr = GraphInfoSetting(_ptr, _iArrCount);

    int iINF = INTMAX; //무한
    int iNodeCount = (*vecNodeNearnodeGraphInfoPtrPtr).size();// 인접한 노드가 있는 노드 수

    //경로 정보 및 거리 최저 값을 를 담아둘 map
    map<int, pair<int,int>> mapNodeDisNearnode;

	//우선순위 큐, pair<거리,노드번호>
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	//시작점 추가
	pq.push({ 0, _iStartNode });
    mapNodeDisNearnode.emplace(_iStartNode,make_pair(0,-1)); //첫 시작 거리는 0
    //vecDis[_iStartNode] = 0; 

    vector<GraphInfo>* vecGraphInfoTempPtr; //특정 노드의 인접 노드 순환을 위해 잠시 담아 놓을 공간
    int ivectorSizeTemp; //위 벡터의 사이즈를 담을 공간
    while (!pq.empty()) 
    {
        int iTopNode = pq.top().second; //현재 노드
        int iDis = pq.top().first; // 시작점부터 현재 노드까지 최단거리
        pq.pop();

        //만약 없다면
        if (mapNodeDisNearnode.find(iTopNode) == mapNodeDisNearnode.end())
        {
            mapNodeDisNearnode.emplace(iTopNode, make_pair(iINF, -1));
        }
        if (iDis > mapNodeDisNearnode[iTopNode].first) //이미 처리된? 노드라면 패스
        {
            continue;
        }

        if (iTopNode == _iEndNode)
        {
            break;
        }

        vecGraphInfoTempPtr = FindNodevecGraphInfo(vecNodeNearnodeGraphInfoPtrPtr, iTopNode);//인접 노드들 확인을 위해 담아놓음
        ivectorSizeTemp = vecGraphInfoTempPtr->size(); //위 벡터의 사이즈(인접 노드 갯수)
        for (int i = 0; i < ivectorSizeTemp; ++i) //제일 최단거리가 짧은 노드의 인접 노드들을 순환
        {
            GraphInfo graphInfo = (*vecGraphInfoTempPtr)[i];
            int iNextNode = graphInfo.iNearNode;
            int iNextDis = iDis + graphInfo.iDistance; //시작점부터 Top 노드까지 거리 + Top 노드부터 인접 노드까지 거리
            if (mapNodeDisNearnode.find(iNextNode) == mapNodeDisNearnode.end())
            {
                mapNodeDisNearnode.emplace(iNextNode, make_pair(iINF, -1));
            }
            if (iNextDis < mapNodeDisNearnode[iNextNode].first)//최단거리 갱신
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

    // 방문 여부, +1은 10개면 0~9번 인덱스 까지 나오는데, 계산의 편리를 위해 0은 빼고 노드 번호 = 인덱스 하기위해
    //사실 1부터 노드 수가 빠진 게 없이 (ex 12 456같은게 아닌) 순서대로 전부 있다는 가정 하에 함.
    vector<bool> vecbVisited(GetNodeCount(vecNodeNearnodeGraphInfoPtrPtr, true), false); // 방문 여부
    queue<int> q; // 큐
    vector<GraphInfo>* vecGraphInfoTempPtr; //특정 노드의 인접 노드 순환을 위해 잠시 담아 놓을 공간
    vector<int> vecNode;

    vecbVisited[_iStartNode] = true; //첫 노드 시작 (방문)
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
//재귀함수
void DFSCheckVisited(int _iVisitedNode, vector<vector<GraphInfo>*>* _vecNodeNearnodeGraphInfoPtrPtr, vector<bool>* _vecbVisitedPtr,vector<int>* _OutvecNode)
{
    (*_vecbVisitedPtr)[_iVisitedNode] = true;
    _OutvecNode->push_back(_iVisitedNode);

    vector<GraphInfo>* vecGraphInfoTempPtr; //특정 노드의 인접 노드 순환을 위해 잠시 담아 놓을 공간
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

    // 방문 여부, +1은 10개면 0~9번 인덱스 까지 나오는데, 계산의 편리를 위해 0은 빼고 노드 번호 = 인덱스 하기위해
    //사실 1부터 노드 수가 빠진 게 없이 (ex 12 456같은게 아닌) 순서대로 전부 있다는 가정 하에 함.
    vector<bool> vecbVisited(GetNodeCount(vecNodeNearnodeGraphInfoPtrPtr,true), false); 
    vector<int> vecNode;
    DFSCheckVisited(_iStartNode, vecNodeNearnodeGraphInfoPtrPtr , &vecbVisited , &vecNode);

    DeleteNodeNearnodeGraphInfoPtrPtr(vecNodeNearnodeGraphInfoPtrPtr);
    *_iOutArrCount = vecNode.size();
    return ChangeIntVectorPtrToArryPtr(&vecNode);
}
//DFS

//Kruskal
// 부모 노드를 찾는 함수
int KruskalFindParentNode(int _iNode, vector<int>& _vecNodeParent)
{
    if (_iNode == _vecNodeParent[_iNode])
    {
        return _iNode;
    }
    int iLastParentsNode = KruskalFindParentNode(_vecNodeParent[_iNode], _vecNodeParent);
    return iLastParentsNode;
}

//// 두 노드를 합쳤을 때, 서로 반대 방향에서 자식을 타고 내려오다 만난 것이므로, 하나의 노드 트리를 자식 부모 반전을 시켜준다.
//void KruskalInvertParentNodes(int _iNode, vector<int>& _vecNodeParent)
//{
//    int iNode = _iNode;
//    int iParentNode;
//    int iNextParentNode;
//    while(true)
//    {
//        //바로 위 부모 노드를 찾는다
//        iParentNode = _vecNodeParent[iNode];
//        //부모 노드의 부모를 잠시 저장해 놓는다.
//        iNextParentNode = _vecNodeParent[iParentNode];
//        //부모 노드에 자신의 노드를 부모로 넣는다.
//        _vecNodeParent[iParentNode] = iNode;
//        //부모 노드를 다시 iNode로 지정한다
//        iParentNode = iNode;
//
//        //만약 부모의 부모 노드와 부모 노드가 같다면 끝낸다.
//        if (iParentNode == iNextParentNode)
//        {
//            break;
//        }
//
//        //부모의 부모 노드를 부모 노드로 지정한다.
//        iParentNode = iNextParentNode;
//    }
//}

int* Kruskal(void* _ptr, int _iArrCount, int* _iOutArrCount)
{
    vector<GraphInfo>* vecGraphInfoPtr = GraphInfoSetting_SingleVector(_ptr, _iArrCount);
    
    //짝수번째(+0) - 홀수번째는 이어진 노드다
    vector<int> vecConnectedNode;

    //간선을 가중치 순으로 정렬
    sort(vecGraphInfoPtr->begin(), vecGraphInfoPtr->end(), [](GraphInfo _A, GraphInfo _B) {return _A.iDistance < _B.iDistance; });

    //노드의 부모 노드 초기화
    vector<int> vecNodeParent(GetNodeCount(vecGraphInfoPtr,true));
    int ivecNodeParentSize = vecNodeParent.size();
    for (int i = 0; i < ivecNodeParentSize; ++i)
    {
        vecNodeParent[i] = i;
    }

    // 최소 신장 트리의 가중치 합, 필요하다면 쓸 것. 구해만 놨음
    int iCost = 0;
    // 간선을 하나씩 추가하며 최소 신장 트리 구성
    for (int i = 0; i < _iArrCount; ++i)
    {
        int iNode1 = (*vecGraphInfoPtr)[i].iNode;
        int iNode2 = (*vecGraphInfoPtr)[i].iNearNode;
        int iWeight = (*vecGraphInfoPtr)[i].iDistance;

        //두 노드를 합치는 부분
        int iNode1Parent = KruskalFindParentNode(iNode1, vecNodeParent);
        int iNode2Parent = KruskalFindParentNode(iNode2, vecNodeParent);
        if (iNode1Parent != iNode2Parent)
        {
            //이어진 노드 추가
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

    //마지막에 가중치 총합 추가
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
        return false; // 겹치는 영역이 없다
    }
    return true; // 겹치는 영역이 있다
}
bool AABB_ArryPtr(void* _ptr, int _iBox1Index, int _iBox2Index)
{
    BoxPos2D* pBoxPos2DArry = reinterpret_cast<BoxPos2D*>(_ptr);

    if(pBoxPos2DArry[_iBox1Index].fRight < pBoxPos2DArry[_iBox2Index].fLeft || pBoxPos2DArry[_iBox1Index].fLeft > pBoxPos2DArry[_iBox2Index].fRight
        || pBoxPos2DArry[_iBox1Index].fBottom > pBoxPos2DArry[_iBox2Index].fTop || pBoxPos2DArry[_iBox1Index].fTop < pBoxPos2DArry[_iBox2Index].fBottom)
    {
        return false; // 겹치는 영역이 없다
    }
    return true; // 겹치는 영역이 있다
}
bool AABB_Overlap(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D)
{
    //x축에서 겹치는 범위
    float fOverlapX = max(0.0f, min(_ABoxPos2D.fRight, _BBoxPos2D.fRight) - max(_ABoxPos2D.fLeft, _BBoxPos2D.fLeft));

    //y축에서 겹치는 범위
    float fOverlapY = max(0.0f, min(_ABoxPos2D.fTop, _BBoxPos2D.fTop) - max(_ABoxPos2D.fBottom, _BBoxPos2D.fBottom));

    // x축과 y축에서 겹치는 범위가 있으면 충돌로 간주합니다.
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

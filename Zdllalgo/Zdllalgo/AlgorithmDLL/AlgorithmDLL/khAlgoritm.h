#pragma once

#ifndef KH
#define KH

#ifdef KH_ALGORITHM
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

#include <vector>
#include <queue>
#include <map>
#include <unordered_set>
#include <algorithm>

#define INTMAX 2147483647

typedef struct stGraphInfo
{
	int iNode;
	int iNearNode;
	int iDistance;

	////혹시나 쓸 일 있을까 해서 만든 대소 비교용
	//bool operator()(const stGraphInfo& _stSrc, const stGraphInfo& _stDst) const
	//{
	//	return _stSrc.iDistance < _stDst.iDistance;
	//}
}GraphInfo;

typedef struct stBoxPos2D
{
	float fLeft;
	float fRight;
	float fTop;
	float fBottom;
}BoxPos2D;

//출발 노드와 다른 모든 노드 간의 최단 경로를 찾는 알고리즘
//너비 우선 탐색(BFS)와 유사한 구조를 가짐, 차이는 각 경로에 가중치가 있을 때 (다익스트라를) 사용한다는 것
//가중치가 음수일 경우 최단 경로를 찾을 수 없다는 단점이 있음
extern "C" DLLIMPORT GraphInfo* Dijkstra(void* _ptr,int _iArrCount,int * _iOutArrCount, int _iStartNode, int _iEndNode);

//Breadth-First Search
//임의의 노드에서 시작해서 인접한 노드를 먼저 탐색하는 방법
//시작 노드부터 가까운 노드들을 먼저 방문하고, 멀리 떨어져 있는 노드를 나중에 방문하는 순회 방법
//깊게 탐색하기 전에 넓게 탐색하는 방법
//두 노드 사이의 최단 경로(모든 가중치가 같을 때) 혹은 임의의 경로를 찾고 싶을 때 사용한다
//시작 노드로부터 거리가 가까운 순으로 방문하는 것이 특징이므로 특정 숫자를 넣었을 때, 가까운 순서대로 노드 출력하도록 제작
extern "C" DLLIMPORT int* BFS(void* _ptr, int _iArrCount, int* _iOutArrCount, int _iStartNode);

//Depth-First Search
//깊이 우선 탐색
//임의의 노드에서 시작해서 최대한 깊게 (이어진 노드를 끝까지) 탐색하는 방식
//한 방향으로 끝까지 탐색 후 더 이상 탐색할 수 없을 때 다시 돌아와 다른 방향으로 탐색 진행
//재귀 함수를 이용하여 구현
extern "C" DLLIMPORT int* DFS(void* _ptr, int _iArrCount, int* _iOutArrCount, int _iStartNode);

//크루스칼 알고리즘 - 그리디 알고리즘의 일종
//최소 신장 트리(Minimum Spanning Tree)를 구하는 알고리즘
//최소 신장 트리란? 가중치 그래프에서 모든 노드를 포함하면서 가장 적은 비용으로 모든 노드를 연결하는 부분 그래프
extern "C" DLLIMPORT int* Kruskal(void* _ptr, int _iArrCount, int* _iOutArrCount);

//AABB 충돌 알고리즘
//2D 버전으로 구현
//두 물체가 충돌했는지 확인하는 알고리즘 (해당 물체를 감싸는 가작 작은 사각형으로)
//빈 공간이 생기기 쉽기 때문에 정확하지 않아, 추가적인 충돌 검사 기법이 같이 활용되어야 한다.
//하지만 내가 구현한 간단한 방법은 두 사각형이 겹치거나 포함되는 상황에서는 제대로 작동 안 할 수도 있다.
//정확하게 하려면 두 사각형 간에 겹치는 부분이 있나 확인해보는 것이 좋다.
extern "C" DLLIMPORT bool AABB(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D);
extern "C" DLLIMPORT bool AABB_ArryPtr(void* _ptr, int _iBox1Index, int _iBox2Index);
extern "C" DLLIMPORT bool AABB_Overlap(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D);

extern "C" DLLIMPORT void FreeGraphInfoArryPtr(void* _ptr);
extern "C" DLLIMPORT void FreeIntArryPtr(void* _ptr);
#endif //KH
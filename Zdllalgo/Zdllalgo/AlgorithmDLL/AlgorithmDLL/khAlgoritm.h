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

	////Ȥ�ó� �� �� ������ �ؼ� ���� ��� �񱳿�
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

//��� ���� �ٸ� ��� ��� ���� �ִ� ��θ� ã�� �˰���
//�ʺ� �켱 Ž��(BFS)�� ������ ������ ����, ���̴� �� ��ο� ����ġ�� ���� �� (���ͽ�Ʈ��) ����Ѵٴ� ��
//����ġ�� ������ ��� �ִ� ��θ� ã�� �� ���ٴ� ������ ����
extern "C" DLLIMPORT GraphInfo* Dijkstra(void* _ptr,int _iArrCount,int * _iOutArrCount, int _iStartNode, int _iEndNode);

//Breadth-First Search
//������ ��忡�� �����ؼ� ������ ��带 ���� Ž���ϴ� ���
//���� ������ ����� ������ ���� �湮�ϰ�, �ָ� ������ �ִ� ��带 ���߿� �湮�ϴ� ��ȸ ���
//��� Ž���ϱ� ���� �а� Ž���ϴ� ���
//�� ��� ������ �ִ� ���(��� ����ġ�� ���� ��) Ȥ�� ������ ��θ� ã�� ���� �� ����Ѵ�
//���� ���κ��� �Ÿ��� ����� ������ �湮�ϴ� ���� Ư¡�̹Ƿ� Ư�� ���ڸ� �־��� ��, ����� ������� ��� ����ϵ��� ����
extern "C" DLLIMPORT int* BFS(void* _ptr, int _iArrCount, int* _iOutArrCount, int _iStartNode);

//Depth-First Search
//���� �켱 Ž��
//������ ��忡�� �����ؼ� �ִ��� ��� (�̾��� ��带 ������) Ž���ϴ� ���
//�� �������� ������ Ž�� �� �� �̻� Ž���� �� ���� �� �ٽ� ���ƿ� �ٸ� �������� Ž�� ����
//��� �Լ��� �̿��Ͽ� ����
extern "C" DLLIMPORT int* DFS(void* _ptr, int _iArrCount, int* _iOutArrCount, int _iStartNode);

//ũ�罺Į �˰��� - �׸��� �˰����� ����
//�ּ� ���� Ʈ��(Minimum Spanning Tree)�� ���ϴ� �˰���
//�ּ� ���� Ʈ����? ����ġ �׷������� ��� ��带 �����ϸ鼭 ���� ���� ������� ��� ��带 �����ϴ� �κ� �׷���
extern "C" DLLIMPORT int* Kruskal(void* _ptr, int _iArrCount, int* _iOutArrCount);

//AABB �浹 �˰���
//2D �������� ����
//�� ��ü�� �浹�ߴ��� Ȯ���ϴ� �˰��� (�ش� ��ü�� ���δ� ���� ���� �簢������)
//�� ������ ����� ���� ������ ��Ȯ���� �ʾ�, �߰����� �浹 �˻� ����� ���� Ȱ��Ǿ�� �Ѵ�.
//������ ���� ������ ������ ����� �� �簢���� ��ġ�ų� ���ԵǴ� ��Ȳ������ ����� �۵� �� �� ���� �ִ�.
//��Ȯ�ϰ� �Ϸ��� �� �簢�� ���� ��ġ�� �κ��� �ֳ� Ȯ���غ��� ���� ����.
extern "C" DLLIMPORT bool AABB(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D);
extern "C" DLLIMPORT bool AABB_ArryPtr(void* _ptr, int _iBox1Index, int _iBox2Index);
extern "C" DLLIMPORT bool AABB_Overlap(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D);

extern "C" DLLIMPORT void FreeGraphInfoArryPtr(void* _ptr);
extern "C" DLLIMPORT void FreeIntArryPtr(void* _ptr);
#endif //KH
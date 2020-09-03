/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 12/10/2019, 18:09
*@Last Modify: 12/19/2019, 18:17
*@Desc: A* pathfinding algorithm.
*********************************************************/
#pragma once
#include <queue>
#include <unordered_set>

#ifndef INF
#define INF 0x7FFFFFFF
#endif
#define MAXSIZE 100

namespace Bur {
	// �����Ͻ�Ϊ����ԭ��
	struct Point2D {
		Point2D(int _1 = 0, int _2 = 0) :v(_1), h(_2) {};
		int v; // vertical
		int h; // horizontal
		int weight; // weight = g + h

		bool operator()(Point2D* lhs, Point2D* rhs) {
			return lhs->weight > rhs->weight; // little top heap
		}
	};

	// �������ߵ�Ϊ0�������ߵĴ���0����б����·������0�ڵ㣬���б����ڵ㲻�ɴ
	void AStar(int** matrix, int size, Point2D* start, Point2D* end) {
		//std::priority_queue<Point2D*> reachable;
		//std::unordered_set<Point2D*> explored;
		//openQueue.push(start);
		//Point2D* cur;
		//Point2D* temp;
		//int tempV, tempH;
		//int manhattan, landform;
		//while (!openQueue.empty()) {
		//	cur = openQueue.top();
		//	openQueue.pop();
		//	closeSet.insert(cur);
		//	for (int i = -1; i <= 1; i++) {
		//		for (int j = -1; j <= 1; j++) {
		//			tempV = cur->v + i;
		//			tempH = cur->h + j;
		//			if (tempV >= 0 && tempV < size && tempH >= 0 && tempH < size && matrix[tempV][tempH] > 0) {
		//				temp = new Point2D(tempV, tempH);
		//				// ������Ѵ�ֱˮƽ��б����ƶ�������뿼�ǣ���
		//				// first Heuristic Factor. Manhattan Distance. ��Լ��������ѡ�������ھ����յ�����Ľڵ㡣
		//				manhattan = abs(temp->v - end->v) + abs(temp->h - end->h);
		//				// second Heuristic Factor. Moving cost. ��Լ��������ѡ�������ڸ����״����Ľڵ㡣
		//				landform = matrix[temp->v][temp->h];
		//				// �ڵ������Ȩ�أ�ֵԽСԽ���㣬ԽӦ�ñ�ѡ��
		//				temp->weight = manhattan + landform;
		//				openQueue.push(temp);
		//			}
		//		}
		//	}
		//}
	}
}

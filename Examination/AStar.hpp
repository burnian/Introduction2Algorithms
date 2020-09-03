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
	// 以左上角为坐标原点
	struct Point2D {
		Point2D(int _1 = 0, int _2 = 0) :v(_1), h(_2) {};
		int v; // vertical
		int h; // horizontal
		int weight; // weight = g + h

		bool operator()(Point2D* lhs, Point2D* rhs) {
			return lhs->weight > rhs->weight; // little top heap
		}
	};

	// 不可行走的为0，可行走的大于0，若斜方向路径上有0节点，则该斜方向节点不可达。
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
		//				// 如果不把垂直水平和斜向的移动情况纳入考虑，则
		//				// first Heuristic Factor. Manhattan Distance. 该约束总是让选择倾向于距离终点更近的节点。
		//				manhattan = abs(temp->v - end->v) + abs(temp->h - end->h);
		//				// second Heuristic Factor. Moving cost. 该约束总是让选择倾向于更容易穿过的节点。
		//				landform = matrix[temp->v][temp->h];
		//				// 节点的行走权重，值越小越优秀，越应该被选择
		//				temp->weight = manhattan + landform;
		//				openQueue.push(temp);
		//			}
		//		}
		//	}
		//}
	}
}

/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/26/2019, 17:02
*@Last Modify: 12/19/2019, 18:52
*@Desc: 各种寻路算法
*********************************************************/
#pragma once
#include <list>
#include <stack>
#include <assert.h>
#include <iostream>
#include "Graph.h"

#ifndef INF
#define INF 0x7FFFFFFF
#endif

namespace Bur {
	class PathNode {
	public:
		PathNode(char _1, const int& _2) :pathLen(_2) {
			name[0] = _1;
			name[1] = '\0';
		};
		PathNode(const char* _1, const int& _2) :pathLen(_2) {
			strcpy_s(name, _1);
		};

		friend std::ostream& operator<<(std::ostream &out, const PathNode &node) {
			out << node.name;
			return out;
		};
		friend std::ostream& operator<<(std::ostream &out, const PathNode *node) {
			out << node->name;
			return out;
		};

	public:
		char name[4];
		int pathLen;
		PathNode* prev = nullptr; // 保存前一个节点
	};

	using PNode = Digraph<PathNode*>::Node*;
	using PEdge = Digraph<PathNode*>::Edge*;

	// 打印起点到各节点的路径和路径长度
	void PathPirnt(Digraph<PathNode*>* g) {
		std::stack<char*> stk;
		for (auto &v : g->nodes) {
			std::cout << v->data->name << " " << v->data->pathLen << std::endl;
			PathNode* p = v->data;
			while (p) {
				stk.push(p->name);
				p = p->prev;
			}
			std::cout << stk.top();
			stk.pop();
			while (!stk.empty()) {
				std::cout << "->" << stk.top();
				stk.pop();
			}
			std::cout << "\n\n";
		}
	}

	// 起点的下标都是0，路径权值要为正
	//@param g 有向图
	//@param startIdx 起点下标
	void Dijkstra(Digraph<PathNode*>* g, int startIdx) {
		assert(g->nodes.size() > 1);

		std::list<PNode> lst;
		for (auto &v : g->nodes) {
			v->data->pathLen = INF;
			lst.push_back(v);
		}

		PNode pn = g->nodes[startIdx];
		pn->data->pathLen = 0; // 初始化起点路径长度
		lst.pop_front();

		PEdge pe;
		PNode pMin;
		int temp;
		while (!lst.empty()) {
			pMin = lst.front();
			// 更新 pn 节点的所有出度节点
			pe = pn->firstOutEdge;
			while (pe) {
				// 特例：pn会尝试更新已经确定最短路径的出度节点，之所以不需要把这些确定点剔除出去是因为已确定的出度点
				// 其路径长度已经是最小了，那么pn->data + pe->weight就一定不小于该确定点的路径值，该点也就不会被更新。
				temp = pn->data->pathLen + pe->weight;
				if (temp < pe->inNode->data->pathLen) {
					pe->inNode->data->pathLen = temp;
					// 经过 pn 的路径比该节点的历史路径更短，所以该节点应该经过 pn 到达。
					pe->inNode->data->prev = pn->data;
				}
				pe = pe->outNext;
			}
			// 找到被更新的节点中路径长度最小的那个节点
			for (auto &v : lst) {
				if (v->data->pathLen < pMin->data->pathLen) {
					pMin = v;
				}
			}
			pn = pMin;
			lst.remove(pn);
		}
	}
	// test case:
	//auto g = new Bur::Digraph<Bur::PathNode*>();
	//for (int i = 0; i < 5; i++) {
	//	g->AddNode(new Bur::PathNode('A' + i, INF));
	//}
	//g->AddEdge(0, 1, 10);
	//g->AddEdge(0, 2, 3);
	//g->AddEdge(1, 2, 1);
	//g->AddEdge(1, 3, 2);
	//g->AddEdge(2, 1, 4);
	//g->AddEdge(2, 3, 8);
	//g->AddEdge(2, 4, 2);
	//g->AddEdge(3, 4, 7);
	//g->AddEdge(4, 3, 9);
	//std::cout << *g << std::endl;
	//Bur::Dijkstra(g, 0);
	//Bur::PathPirnt(g);
	//for (auto &v : g->nodes) {
	//	delete v->data;
	//}
	//delete g;

	// 路径权值可以为负
	//@param g 有向图
	//@param startIdx 起点下标，从0开始
	void BellmanFord(Digraph<PathNode*>* g, int startIdx) {
		// 初始化各点路径长度
		for (auto &v : g->nodes) {
			v->data->pathLen = INF;
		}
		g->nodes[startIdx]->data->pathLen = 0;
		// relaxation 做 n-1 次
		for (int i = 0; i < g->nodes.size() - 1; i++) {
			for (auto &v : g->edges) {
				if (v->outNode->data->pathLen != INF && v->outNode->data->pathLen + v->weight < v->inNode->data->pathLen) {
					v->inNode->data->pathLen = v->outNode->data->pathLen + v->weight;
					v->inNode->data->prev = v->outNode->data;
				}
			}
		}
		// 第 n 遍目的是判断图中是否有负环，若还能relax，则必存在负环
		for (auto &v : g->edges)
			if (v->outNode->data->pathLen != INF && v->outNode->data->pathLen + v->weight < v->inNode->data->pathLen)
				std::cout << "Negative-weight cycle exists in the graph." << std::endl;
	}
	// test case1:
	//auto g = new Bur::Digraph<Bur::PathNode*>();
	//for (int i = 0; i < 5; i++) {
	//	g->AddNode(new Bur::PathNode('A' + i, INF));
	//}
	//g->AddEdge(0, 1, -1);
	//g->AddEdge(0, 2, 4);
	//g->AddEdge(1, 2, 3);
	//g->AddEdge(1, 3, 2);
	//g->AddEdge(1, 4, 2);
	//g->AddEdge(3, 1, 1);
	//g->AddEdge(3, 2, 5);
	//g->AddEdge(4, 3, -3);
	//Bur::BellmanFord(g, 0);
	//Bur::PathPirnt(g);
	// test case2:
	//int n = 16;
	//int** g = new int*[n] {
	//	new int[n] {0, 5, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
	//		new int[n] {5, 0, INF, 1, 3, 6, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
	//		new int[n] {3, INF, 0, INF, 8, 7, 6, INF, INF, INF, INF, INF, INF, INF, INF, INF},
	//		new int[n] {INF, 1, INF, 0, INF, INF, INF, 6, 8, INF, INF, INF, INF, INF, INF, INF},
	//		new int[n] {INF, 3, 8, INF, 0, INF, INF, 3, 5, INF, INF, INF, INF, INF, INF, INF},
	//		new int[n] {INF, 6, 7, INF, INF, 0, INF, INF, 3, 3, INF, INF, INF, INF, INF, INF},
	//		new int[n] {INF, INF, 6, INF, INF, INF, 0, INF, 8, 4, INF, INF, INF, INF, INF, INF},
	//		new int[n] {INF, INF, INF, 6, 3, INF, INF, 0, INF, INF, 2, 2, INF, INF, INF, INF},
	//		new int[n] {INF, INF, INF, 8, 5, 3, 8, INF, 0, INF, INF, 1, 2, INF, INF, INF},
	//		new int[n] {INF, INF, INF, INF, INF, 3, 4, INF, INF, 0, INF, 3, 3, INF, INF, INF},
	//		new int[n] {INF, INF, INF, INF, INF, INF, INF, 2, INF, INF, 0, INF, INF, 3, 5, INF},
	//		new int[n] {INF, INF, INF, INF, INF, INF, INF, 2, 1, 3, INF, 0, INF, 5, 2, INF},
	//		new int[n] {INF, INF, INF, INF, INF, INF, INF, INF, 2, 3, INF, INF, 0, 6, 6, INF},
	//		new int[n] {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 3, 5, 6, 0, INF, 4},
	//		new int[n] {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 5, 2, 6, INF, 0, 3},
	//		new int[n] {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, 3, 0},
	//};
	//auto g2 = new Bur::Digraph<Bur::PathNode*>();
	//char name[4];
	//for (int i = 0; i < n; i++) {
	//	if (i > 9) {
	//		name[0] = '1';
	//		name[1] = '0' + i % 10;
	//		name[2] = '\0';
	//	}
	//	else {
	//		name[0] = '0' + i;
	//		name[1] = '\0';
	//	}
	//	g2->AddNode(new Bur::PathNode(name, INF));
	//}
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		if (g[i][j] != 0 && g[i][j] != INF) {
	//			g2->AddEdge(i, j, g[i][j]);
	//		}
	//	}
	//}
	//Bur::BellmanFord(g2, 0);

	// 又名十字交叉算法，路径权值可以为负
	//@param g 邻接矩阵
	//@param n 节点数
	void FloydWarshall(int** g, int n) {
		// 注意对邻点的遍历一定要放最外层
		for (int k = 0; k < n; k++) {
			// 表格放内层，每更换一个邻点刷一遍表格
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					int temp = g[i][k] == INF || g[k][j] == INF ? INF : g[i][k] + g[k][j];
					if (temp < g[i][j])
						g[i][j] = temp;
				}
			}
		}
	}
	// test case:
	//int** g2 = new int*[5]{
	//new int[5]{0, -1, 4, INF, INF},
	//new int[5]{INF, 0, 3, 2, 2},
	//new int[5]{INF, INF, 0, INF, INF},
	//new int[5]{INF, 1, 5, 0, INF},
	//new int[5]{INF, INF, INF, -3, 0},
	//};
	//Bur::FloydWarshall(g2, 5);
	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		std::cout << g2[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
}

/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/26/2019, 17:02
*@Last Modify: 12/06/2019, 18:24
*@Desc: 迪杰斯特拉寻路算法
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
	struct DijNode {
		char name;
		int pathLen;
		DijNode* prev = nullptr; // 保存前一个节点

		DijNode(const char& _1, const int& _2) :name(_1), pathLen(_2) {};

		friend std::ostream& operator<<(std::ostream &out, const DijNode &node) {
			out << node.name;
			return out;
		};

		friend std::ostream& operator<<(std::ostream &out, const DijNode *node) {
			out << node->name;
			return out;
		};
	};

	using PNode = Digraph<DijNode*>::Node*;
	using PEdge = Digraph<DijNode*>::Edge*;

	struct cmp {
		bool operator()(PNode lhs, PNode rhs) {
			return lhs->data->pathLen > rhs->data->pathLen; // 小顶堆
		};
	};

	// 起点的下标都是0
	//@param g 有向图
	//@param startIdx 起点下标
	void Dijkstra(Digraph<DijNode*>* g, int startIdx) {
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

	void PathPirnt(Digraph<DijNode*>* g) {
		std::stack<char> stk;
		for (auto &v : g->nodes) {
			std::cout << v->data->name << " " << v->data->pathLen << std::endl;
			DijNode* p = v->data;
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
}

// test case:
//auto g = new Bur::Digraph<Bur::DijNode*>();
//for (int i = 0; i < 5; i++) {
//	g->AddNode(new Bur::DijNode('A' + i, INF));
//}
//
//g->AddEdge(0, 1, 10);
//g->AddEdge(0, 2, 3);
//g->AddEdge(1, 2, 1);
//g->AddEdge(1, 3, 2);
//g->AddEdge(2, 1, 4);
//g->AddEdge(2, 3, 8);
//g->AddEdge(2, 4, 2);
//g->AddEdge(3, 4, 7);
//g->AddEdge(4, 3, 9);
//
//std::cout << *g << std::endl;
//
//Bur::Dijkstra(g, 0);
//Bur::PathPirnt(g);
//
//for (auto &v : g->nodes) {
//	delete v->data;
//}
//delete g;

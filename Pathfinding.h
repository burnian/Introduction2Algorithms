/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/26/2019, 17:02
*@Last Modify: 12/19/2019, 18:52
*@Desc: ����Ѱ·�㷨
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
		PathNode* prev = nullptr; // ����ǰһ���ڵ�
	};

	using PNode = Digraph<PathNode*>::Node*;
	using PEdge = Digraph<PathNode*>::Edge*;

	// ��ӡ��㵽���ڵ��·����·������
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

	// �����±궼��0��·��ȨֵҪΪ��
	//@param g ����ͼ
	//@param startIdx ����±�
	void Dijkstra(Digraph<PathNode*>* g, int startIdx) {
		assert(g->nodes.size() > 1);

		std::list<PNode> lst;
		for (auto &v : g->nodes) {
			v->data->pathLen = INF;
			lst.push_back(v);
		}

		PNode pn = g->nodes[startIdx];
		pn->data->pathLen = 0; // ��ʼ�����·������
		lst.pop_front();

		PEdge pe;
		PNode pMin;
		int temp;
		while (!lst.empty()) {
			pMin = lst.front();
			// ���� pn �ڵ�����г��Ƚڵ�
			pe = pn->firstOutEdge;
			while (pe) {
				// ������pn�᳢�Ը����Ѿ�ȷ�����·���ĳ��Ƚڵ㣬֮���Բ���Ҫ����Щȷ�����޳���ȥ����Ϊ��ȷ���ĳ��ȵ�
				// ��·�������Ѿ�����С�ˣ���ôpn->data + pe->weight��һ����С�ڸ�ȷ�����·��ֵ���õ�Ҳ�Ͳ��ᱻ���¡�
				temp = pn->data->pathLen + pe->weight;
				if (temp < pe->inNode->data->pathLen) {
					pe->inNode->data->pathLen = temp;
					// ���� pn ��·���ȸýڵ����ʷ·�����̣����Ըýڵ�Ӧ�þ��� pn ���
					pe->inNode->data->prev = pn->data;
				}
				pe = pe->outNext;
			}
			// �ҵ������µĽڵ���·��������С���Ǹ��ڵ�
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

	// ·��Ȩֵ����Ϊ��
	//@param g ����ͼ
	//@param startIdx ����±꣬��0��ʼ
	void BellmanFord(Digraph<PathNode*>* g, int startIdx) {
		// ��ʼ������·������
		for (auto &v : g->nodes) {
			v->data->pathLen = INF;
		}
		g->nodes[startIdx]->data->pathLen = 0;
		// relaxation �� n-1 ��
		for (int i = 0; i < g->nodes.size() - 1; i++) {
			for (auto &v : g->edges) {
				if (v->outNode->data->pathLen != INF && v->outNode->data->pathLen + v->weight < v->inNode->data->pathLen) {
					v->inNode->data->pathLen = v->outNode->data->pathLen + v->weight;
					v->inNode->data->prev = v->outNode->data;
				}
			}
		}
		// �� n ��Ŀ�����ж�ͼ���Ƿ��и�����������relax����ش��ڸ���
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

	// ����ʮ�ֽ����㷨��·��Ȩֵ����Ϊ��
	//@param g �ڽӾ���
	//@param n �ڵ���
	void FloydWarshall(int** g, int n) {
		// ע����ڵ�ı���һ��Ҫ�������
		for (int k = 0; k < n; k++) {
			// �����ڲ㣬ÿ����һ���ڵ�ˢһ����
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

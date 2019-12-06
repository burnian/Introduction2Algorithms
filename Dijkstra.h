/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/26/2019, 17:02
*@Last Modify: 12/06/2019, 18:24
*@Desc: �Ͻ�˹����Ѱ·�㷨
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
		DijNode* prev = nullptr; // ����ǰһ���ڵ�

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
			return lhs->data->pathLen > rhs->data->pathLen; // С����
		};
	};

	// �����±궼��0
	//@param g ����ͼ
	//@param startIdx ����±�
	void Dijkstra(Digraph<DijNode*>* g, int startIdx) {
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

/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 12/06/2019, 17:32
*@Last Modify: 12/06/2019, 17:32
*@Desc: ...
*********************************************************/
#pragma once
#include "Dijkstra.h"

namespace Bur {
	//@param g ����ͼ
	//@param startIdx ����±꣬��0��ʼ
	void BellmanFord(Digraph<DijNode*>* g, int startIdx) {
		// ��ʼ������·������
		for (auto &v : g->nodes) {
			v->data->pathLen = INF;
		}
		g->nodes[startIdx]->data->pathLen = 0;

		int cnt = g->nodes.size() - 1;
		for (int i = 0; i < cnt; i++) {
			for (auto &v : g->edges) {
				if (v->outNode->data->pathLen != INF && v->outNode->data->pathLen + v->weight < v->inNode->data->pathLen) {
					v->inNode->data->pathLen = v->outNode->data->pathLen + v->weight;
					v->inNode->data->prev = v->outNode->data;
				}
			}
		}
		// �� n ��Ŀ�����ж�ͼ���Ƿ��и���
		for (auto &v : g->edges) {
			if (v->outNode->data->pathLen != INF && v->outNode->data->pathLen + v->weight < v->inNode->data->pathLen)
				std::cout << "Negative-weight cycle exists in the graph." << std::endl;
		}
	}
}

// test case:
//auto g = new Bur::Digraph<Bur::DijNode*>();
//for (int i = 0; i < 5; i++) {
//	g->AddNode(new Bur::DijNode('A' + i, INF));
//}
//
//g->AddEdge(0, 1, -1);
//g->AddEdge(0, 2, 4);
//g->AddEdge(1, 2, 3);
//g->AddEdge(1, 3, 2);
//g->AddEdge(1, 4, 2);
//g->AddEdge(3, 1, 1);
//g->AddEdge(3, 2, 5);
//g->AddEdge(4, 3, -3);
//
//BellmanFord(g, 0);
//PathPirnt(g);

/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 12/06/2019, 17:32
*@Last Modify: 12/06/2019, 17:32
*@Desc: ...
*********************************************************/
#pragma once
#include "Dijkstra.h"

namespace Bur {
	//@param g 有向图
	//@param startIdx 起点下标，从0开始
	void BellmanFord(Digraph<DijNode*>* g, int startIdx) {
		// 初始化各点路径长度
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
		// 第 n 遍目的是判断图中是否有负环
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

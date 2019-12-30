/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/28/2019, 17:58
*@Last Modify: 12/18/2019, 16:49
*@Desc: 图
*********************************************************/
#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <functional>
#include <assert.h>

namespace Bur {
	// 有向图
	template<typename T>
	class Digraph
	{
	public:
		struct Edge;
		struct Node {
			T data;
			Edge* firstInEdge = nullptr; // 入边
			Edge* firstOutEdge = nullptr; // 出边

			Node(const T& _1) :data(_1) {};
		};

		struct Edge {
			int weight = 0;
			Node* inNode = nullptr; // 该边进入该节点，终止节点
			Node* outNode = nullptr; // 该边从该节点出去，起始节点
			Edge* inNext = nullptr;
			Edge* outNext = nullptr;
		};

		using Visit = std::function<void(Node*)>;

		// constructor
		Digraph() {};

		// deconstructor
		~Digraph() {
			for (auto &v : nodes) {
				delete v;
			}
			for (auto &v : edges) {
				delete v;
			}
		};

		// 在构建图的时候要先添加节点后添加边
		void AddNode(const T& data) {
			nodes.push_back(new Node(data));
		}

		// 添加一条边
		void AddEdge(int outIdx, int inIdx, int weight = 0) {
			int len = nodes.size();
			assert(outIdx < len && inIdx < len);

			Edge* e = new Edge();
			e->weight = weight;
			e->outNode = nodes[outIdx];
			e->inNode = nodes[inIdx];
			edges.push_back(e);
			Edge* p;
			Edge* pre;

			p = nodes[outIdx]->firstOutEdge;
			pre = nullptr;
			while (p) {
				pre = p;
				p = p->outNext;
			}
			if (pre) {
				pre->outNext = e;
			}
			else {
				nodes[outIdx]->firstOutEdge = e;
			}
			
			p = nodes[inIdx]->firstInEdge;
			pre = nullptr;
			while (p) {
				pre = p;
				p = p->inNext;
			}
			if (pre) {
				pre->inNext = e;
			}
			else {
				nodes[inIdx]->firstInEdge = e;
			}
		}

		// 判空
		bool Empty() {
			return nodes.size() <= 0;
		}

		// 广度优先遍历，优先遍历某个出度点，然后回溯
		void BFS(Visit visit) {
			std::queue<Node*> q;
			std::unordered_set<Node*> s; // 其底层为 hash 实现，可以实现快速查找
			q.push(nodes[0]);
			s.insert(nodes[0]);
			Node* pn;
			while (!q.empty()) {
				pn = q.front();
				q.pop();
				Edge* pe = pn->firstOutEdge;
				while (pe) {
					if (s.end() == s.find(pe->inNode)) {
						q.push(pe->inNode);
						s.insert(pe->inNode);
					}
					pe = pe->outNext;
				}
				visit(pn);
			}
		}

		// 深度优先遍历，优先遍历某节点的所有出度点，一般以入度为0 的节点为起点，默认起点为 nodes[0]
		void DFS(Visit visit) {
			std::stack<Node*> stk;
			std::unordered_set<Node*> s;
			stk.push(nodes[0]);
			s.insert(nodes[0]);
			Node* pn;
			while (!stk.empty()) {
				pn = stk.top();
				stk.pop();
				Edge* pe = pn->firstOutEdge;
				while (pe) {
					if (s.end() == s.find(pe->inNode)) {
						stk.push(pe->inNode);
						s.insert(pe->inNode);
					}
					pe = pe->outNext;
				}
				visit(pn);
			}
		}

		// iostream 打印
		friend std::ostream& operator<<(std::ostream &out, const Digraph &g) {
			for (int i = 0; i < g.nodes.size(); i++) {
				out << g.nodes[i]->data;
				Edge* p = g.nodes[i]->firstOutEdge;
				while (p) {
					if (p->weight != 0)
						out << "-" << p->weight;
					out << "->" << p->inNode->data;
					p = p->outNext;
				}
				out << std::endl;
			}
			return out;
		}

	public:
		std::vector<Node*> nodes; // 十字链表实现 orthList
		std::vector<Edge*> edges; // 边表
	};
}

// test case:
//auto g = new Bur::Digraph<char>();
//for (int i = 0; i < 9; i++) {
//	g->AddNode('a' + i);
//}
//
//g->AddEdge(0, 1);
//g->AddEdge(0, 3);
//g->AddEdge(1, 2);
//g->AddEdge(1, 4);
//g->AddEdge(3, 1);
//g->AddEdge(3, 4);
//g->AddEdge(4, 2);
//g->AddEdge(4, 6);
//g->AddEdge(4, 8);
//g->AddEdge(5, 3);
//g->AddEdge(5, 7);
//g->AddEdge(6, 5);
//g->AddEdge(6, 8);
//g->AddEdge(7, 6);
//g->AddEdge(8, 7);
//
//g->BFS([](Bur::Digraph<char>::Node* node) {
//	std::cout << node->data << " ";
//});
//std::cout << std::endl;
//
//g->DFS([](Bur::Digraph<char>::Node* node) {
//	std::cout << node->data << " ";
//});
//std::cout << std::endl;

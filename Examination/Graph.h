/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/28/2019, 17:58
*@Last Modify: 12/18/2019, 16:49
*@Desc: ͼ
*********************************************************/
#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <functional>
#include <assert.h>

namespace Bur {
	// ����ͼ
	template<typename T>
	class Digraph
	{
	public:
		struct Edge;
		struct Node {
			T data;
			Edge* firstInEdge = nullptr; // ���
			Edge* firstOutEdge = nullptr; // ����

			Node(const T& _1) :data(_1) {};
		};

		struct Edge {
			int weight = 0;
			Node* inNode = nullptr; // �ñ߽���ýڵ㣬��ֹ�ڵ�
			Node* outNode = nullptr; // �ñߴӸýڵ��ȥ����ʼ�ڵ�
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

		// �ڹ���ͼ��ʱ��Ҫ����ӽڵ����ӱ�
		void AddNode(const T& data) {
			nodes.push_back(new Node(data));
		}

		// ���һ����
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

		// �п�
		bool Empty() {
			return nodes.size() <= 0;
		}

		// ������ȱ��������ȱ���ĳ�����ȵ㣬Ȼ�����
		void BFS(Visit visit) {
			std::queue<Node*> q;
			std::unordered_set<Node*> s; // ��ײ�Ϊ hash ʵ�֣�����ʵ�ֿ��ٲ���
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

		// ������ȱ��������ȱ���ĳ�ڵ�����г��ȵ㣬һ�������Ϊ0 �Ľڵ�Ϊ��㣬Ĭ�����Ϊ nodes[0]
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

		// iostream ��ӡ
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
		std::vector<Node*> nodes; // ʮ������ʵ�� orthList
		std::vector<Edge*> edges; // �߱�
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

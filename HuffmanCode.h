/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/17/2019, 16:15
*@Last Modify: 11/28/2019, 16:49
*@Desc: ����������
*********************************************************/
#pragma once
#include <queue>
#include <vector>
#include <map>
#include <string>
#include "BTree.h"

namespace Bur {
	using HCTree = BTree<std::pair<char, size_t> >;
	using HCNode = HCTree::Node;

	struct cmp
	{
		bool operator()(HCNode* lhs, HCNode* rhs) {
			return lhs->data.second > rhs->data.second;
		}
	};

	void HuffmanCode(std::map<char, size_t>& m, std::map<char, std::string>& ret) {
		std::priority_queue<HCNode*, std::vector<HCNode*>, cmp> q; // С����
		HCNode* p;
		for (auto &v : m) {
			p = new HCNode(v);
			q.push(p);
		}

		while (q.size() > 1) {
			p = new HCNode(std::pair<char, size_t>('0', 0)); // �½��ڵ��seconde ֵ��ʾƵ��
			p->lChild = q.top();
			p->lChild->parent = p;
			p->data.second += p->lChild->data.second; // Ƶ���ϴ����ڵ���������
			p->lChild->data.second = 0; // ��Ƶ�ʸĳ����ӱ�� 0
			q.pop();
			p->rChild = q.top();
			p->rChild->parent = p;
			p->data.second += p->rChild->data.second; // Ƶ���ϴ����ڵ���������
			p->rChild->data.second = 1; // ��Ƶ�ʸĳ��Һ��ӱ�� 1
			q.pop();
			q.push(p);
		}

		std::stack<size_t> stk;
		HCTree::LevelOrder(q.top(), [&](HCNode* node) {
			if (!node->lChild && !node->rChild) {
				HCNode* p = node;
				while (p->parent) {
					stk.push(p->data.second);
					p = p->parent;
				}
				std::string str = "";
				while (!stk.empty()) {
					str.append(stk.top() == 0 ? "0" : "1");
					stk.pop();
				}
				ret[node->data.first] = str;
			}
		});
	}
}

// test case:
//std::map<char, size_t> data = {
//	std::pair<char, size_t>('a', 45),
//	std::pair<char, size_t>('b', 13),
//	std::pair<char, size_t>('c', 12),
//	std::pair<char, size_t>('d', 16),
//	std::pair<char, size_t>('e', 9),
//	std::pair<char, size_t>('f', 5)
//};
//
//std::map<char, std::string> ret;
//Bur::HuffmanCode(data, ret);
//
//for (auto &v : ret) {
//	std::cout << v.first << " : " << v.second << std::endl;
//}

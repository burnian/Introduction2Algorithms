/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/17/2019, 16:17
*@Last Modify: 12/01/2019, 22:08
*@Desc: ��������������Ƶ�����ԭ��Ӧ�������Ƿ���ʹ�á�
*********************************************************/
#pragma once
#include<stack>
#include<queue>
#include<functional>

namespace Bur {
	template<typename T>
	class BTree {
	public:
		struct Node
		{
			Node(T _1 = 0) :data(_1) {};
			T data;
			Node* parent = nullptr;
			Node* lChild = nullptr;
			Node* rChild = nullptr;
			// ֮�������Ҫ��ǽڵ��Ƿ����ӽڵ㣬�����
			//bool isLeft = false;
		};

		using Visit = std::function<void(Node*)>;

		// ��α���
		static void LevelOrder(Node* root, Visit visit) {
			std::queue<Node*> queue;
			queue.push(root);
			while (!queue.empty())
			{
				root = queue.front();
				queue.pop();
				visit(root);
				if (root->lChild) queue.push(root->lChild);
				if (root->rChild) queue.push(root->rChild);
			}
		}

		// �ǵݹ��������
		static void NRPreOrder(Node* root, Visit visit) {
			std::stack<Node*> stk;
			stk.push(root);
			while (!stk.empty())
			{
				root = stk.top();
				stk.pop();
				visit(root);
				if (root->rChild) stk.push(root->rChild);
				if (root->lChild) stk.push(root->lChild);
			}
		}

		// �ǵݹ��������
		static void NRInOrder(Node* root, Visit visit) {
			std::stack<Node*> stk;
			while (root || !stk.empty()) {
				while (root) {
					stk.push(root);
					root = root->lChild;
				}
				root = stk.top();
				stk.pop();
				visit(root);
				root = root->rChild;
			}
		}

		// �ǵݹ�������
		static void NRPostOrder(Node* root, Visit visit) {
			std::stack<Node*> stk;
			Node* pre = nullptr; //ǰһ�η��ʵĽ�� 
			stk.push(root);
			while (!stk.empty())
			{
				root = stk.top();
				if ((root->lChild == nullptr && root->rChild == nullptr)
					|| (pre && (pre == root->lChild || pre == root->rChild))) {
					visit(root); // ����ǰ�����Ҷ�ڵ㣬�����ӽڵ㶼�ѱ����ʹ�������ʡ���һ�����ʵĽڵ��������Һ�����֤�����ӽڵ㶼�����ʹ��ˡ�
					stk.pop();
					pre = root;
				}
				else {
					if (root->rChild)
						stk.push(root->rChild);
					if (root->lChild)
						stk.push(root->lChild);
				}
			}
		}

	};
}

// test case:
//using BTree = Bur::BTree<int>;
//using Node = BTree::Node;
//
//Node* root = new Node(0);
//
//root->lChild = new Node(1);
//root->lChild->lChild = new Node(3);
//root->lChild->rChild = new Node(4);
//
//root->rChild = new Node(2);
//root->rChild->lChild = new Node(5);
//root->rChild->rChild = new Node(6);
//
//BTree::LevelOrder(root, [](int data) {
//	std::cout << data << " ";
//});
//std::cout << std::endl;
//BTree::NRInOrder(root, [](int data) {
//	std::cout << data << " ";
//});
//std::cout << std::endl;
//BTree::NRPostOrder(root, [](int data) {
//	std::cout << data << " ";
//});
//std::cout << std::endl;
//BTree::NRPreOrder(root, [](int data) {
//	std::cout << data << " ";
//});
//std::cout << std::endl;

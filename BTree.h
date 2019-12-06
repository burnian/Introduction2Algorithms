/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/17/2019, 16:17
*@Last Modify: 12/01/2019, 22:08
*@Desc: 二叉树，所有设计的优先原则应该首先是方便使用。
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
			// 之后如果需要标记节点是否左子节点，则添加
			//bool isLeft = false;
		};

		using Visit = std::function<void(Node*)>;

		// 层次遍历
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

		// 非递归先序遍历
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

		// 非递归中序遍历
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

		// 非递归后序遍历
		static void NRPostOrder(Node* root, Visit visit) {
			std::stack<Node*> stk;
			Node* pre = nullptr; //前一次访问的结点 
			stk.push(root);
			while (!stk.empty())
			{
				root = stk.top();
				if ((root->lChild == nullptr && root->rChild == nullptr)
					|| (pre && (pre == root->lChild || pre == root->rChild))) {
					visit(root); // 若当前结点是叶节点，或其子节点都已被访问过，则访问。上一个访问的节点是其左右孩子则证明其子节点都被访问过了。
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

/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/27/2019, 10:50
*@Last Modify: 09/28/2019, 17:33
*@Desc: 链表
*********************************************************/
#pragma once
#include <assert.h>
#include <functional>


namespace Bur {
	// 节点数据的初始化方法
	template<typename T>
	class LinkList
	{
	public:
		struct Node {
			T* elem = nullptr;
			Node* next = nullptr;
		};

		LinkList()
		{
			this->_head = new Node();
			assert(this->_head);
			this->_head->elem = 0;
		}

		// 用于输入节点数据的构造方法
		LinkList(std::function<bool(T*)> func)
			:_nodeInitFunc(func)
		{
			this->_head = new Node();
			assert(this->_head);
			this->_head->elem = 0;
		}

		~LinkList() {
			Node* p = this->_head;
			Node* temp = p->next;
			delete(p);
			p = temp;
			while (p)
			{
				temp = p->next;
				delete(p->elem);
				delete(p);
				p = temp;
			}
		}

		// 输入式创建链表，_nodeInitFunc返回true就继续输入，false就结束
		void CreateFromKeyboard() {
			Node* r = this->_head;
			bool flag = true;
			while (flag)
			{
				Node* node = new Node();
				assert(node);
				node->elem = new T();
				assert(node->elem);
				flag = _nodeInitFunc(node->elem);
				r->next = node;
				r = node;
				this->Add2Length(1);
			}
		}

		// 读取数据式创建链表
		void CreateFromData(T** arr, int len) {
			Node* r = this->_head;
			for (int i = 0; i < len; i++) {
				Node* node = new Node();
				assert(node);
				node->elem = arr[i];
				r->next = node;
				r = node;
				this->Add2Length(1);
			}
		}

		// 查询 头结点是0号元素
		Node* GetNode(int pos) {
			if (pos > 0 && pos <= this->GetLength()) {
				Node* p = this->_head;
				for (int i = 0; i < pos; i++) {
					p = p->next;
				}
				return p;
			}
		}

		// 链表长度
		Node* GetHead() {
			return this->_head;
		}

		// 链表长度
		int GetLength() {
			return (int)(this->_head->elem);
		}

		// 长度+1
		void Add2Length(int n) {
			_head->elem = (T*)((int)(_head->elem) + n);
		}

		// 插入
		void Insert(int pos, T* elem) {
			Node* node = new Node();
			assert(node);
			node->elem = elem;
			Node* p = this->_head;
			for (int i = 1; i < pos && i <= this->GetLength(); i++) {
				p = p->next;
			}
			node->next = p->next;
			p->next = node;
			this->Add2Length(1);
		}

		void Insert(Node* p, T* elem) {
			assert(p);
			Node* node = new Node();
			assert(node);
			node->elem = elem;
			node->next = p->next;
			p->next = node;
			this->Add2Length(1);
		}

		// 删除 头结点是0号元素，删除下标从s（含s）到e（不含e）的所有节点，不填参数的默认情况是删除所有节点
		void Delete(int s = 1, int e = 0) {
			int len = this->GetLength();
			assert(s < 1 || s > len || e > len);
			Node* p = this->_head;
			Node* del = p;
			for (int i = 1; i < s; i++) {
				p = p->next;
			}
			if (e > 0) {
				for (int i = s; i < e; i++) {
					del = p->next;
					p->next = del->next;
					delete(del->elem);
					delete(del);
					this->Add2Length(-1);
				}
			}
			else {
				// s以后的所有元素都删除
				del = p->next;
				p->next = nullptr;
				while (del)
				{
					p = del->next;
					delete(del->elem);
					delete(del);
					del = p;
					this->Add2Length(-1);
				}
			}
		}

		// 用一个事件遍历每个节点
		void Visit(std::function<void(Node*)> func) {
			Node* p = this->_head->next;
			while (p) {
				func(p);
				p = p->next;
			}
		}

	private:
		Node* _head;
		// 初始化节点数据，返回是否继续创建的flag
		std::function<bool(T*)> _nodeInitFunc;
	};

}

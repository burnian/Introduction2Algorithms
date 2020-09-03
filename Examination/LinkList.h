/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/27/2019, 10:50
*@Last Modify: 09/28/2019, 17:33
*@Desc: ����
*********************************************************/
#pragma once
#include <assert.h>
#include <functional>


namespace Bur {
	// �ڵ����ݵĳ�ʼ������
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

		// ��������ڵ����ݵĹ��췽��
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

		// ����ʽ��������_nodeInitFunc����true�ͼ������룬false�ͽ���
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

		// ��ȡ����ʽ��������
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

		// ��ѯ ͷ�����0��Ԫ��
		Node* GetNode(int pos) {
			if (pos > 0 && pos <= this->GetLength()) {
				Node* p = this->_head;
				for (int i = 0; i < pos; i++) {
					p = p->next;
				}
				return p;
			}
		}

		// ������
		Node* GetHead() {
			return this->_head;
		}

		// ������
		int GetLength() {
			return (int)(this->_head->elem);
		}

		// ����+1
		void Add2Length(int n) {
			_head->elem = (T*)((int)(_head->elem) + n);
		}

		// ����
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

		// ɾ�� ͷ�����0��Ԫ�أ�ɾ���±��s����s����e������e�������нڵ㣬���������Ĭ�������ɾ�����нڵ�
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
				// s�Ժ������Ԫ�ض�ɾ��
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

		// ��һ���¼�����ÿ���ڵ�
		void Visit(std::function<void(Node*)> func) {
			Node* p = this->_head->next;
			while (p) {
				func(p);
				p = p->next;
			}
		}

	private:
		Node* _head;
		// ��ʼ���ڵ����ݣ������Ƿ����������flag
		std::function<bool(T*)> _nodeInitFunc;
	};

}

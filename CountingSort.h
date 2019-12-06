/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/26/2019, 16:49
*@Last Modify: 09/30/2019, 00:53
*@Desc: ��������
*********************************************************/
#pragma once
#include <vector>

namespace Bur {
	class Countable {
	public:
		Countable(int a = 0) :priority(a) {};
	public:
		int priority;
	};

	int c[1000] = { 0 }; // ȫ�ֱ���Ҫ���������ռ���
	//@param h ���Ƚ�Ȩֵ����Сֵ
	//@param r ���Ƚ�Ȩֵ�����ֵ
	void CountingSort(std::vector<Countable*>& origin, std::vector<Countable*>& dest, int h, int r) {
		for (auto &v : origin) {
			c[v->priority - h]++;
		}

		int cnt = r - h + 1;
		for (int i = 1; i < cnt; i++) {
			c[i] += c[i - 1];
		}

		for (int i = origin.size() - 1; i >= 0; i--) {
			int temp = origin[i]->priority - h;
			dest[c[temp] - 1] = origin[i];
			c[temp]--;
		}
	};
}


// �÷�
//class A : public Countable {
//public:
//	A(const char s[20], int a) :Countable(a) {
//		strcpy_s(name, s);
//	};
//public:
//	char name[20];
//};
//
//std::vector<Countable*> origin = { new A("hhh", 1004), new A("hello", 1001), new A("ddd", 1003), new A("iii", 1004), new A("jjj", 1003) };
//std::vector<Countable*> dest(origin.size());
//CountingSort(origin, dest, 1000, 1004);

/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/26/2019, 20:06
*@Last Modify: 09/26/2019, 20:06
*@Desc: �������򣬰Ѹ�λ�����ȶ������㷨������������������о��ź���
*********************************************************/
#pragma once
#include <vector>

namespace Bur {
	// Ĭ�ϼ�����Χ��0~9
	void CountingSort(std::vector<int> &origin, std::vector<int> &dest, int pos) {
		int c[10] = { 0 };
		for (auto &v : origin) {
			c[v / pos % 10]++;
		}

		for (int i = 1; i < 10; i++) {
			c[i] += c[i - 1];
		}

		for (int i = origin.size() - 1; i >= 0; i--) {
			int temp = origin[i] / pos % 10;
			dest[c[temp] - 1] = origin[i];
			c[temp]--;
		}
	};

	void RadixSort(std::vector<int> &origin, int d) {
		std::vector<int> dest(origin.size());
		bool flag = true;
		for (int i = 0; i < d; i++) {
			if (flag)
				CountingSort(origin, dest, pow(10, i));
			else
				CountingSort(dest, origin, pow(10, i));
			flag = !flag;
		}
		if (!flag)
			origin.assign(dest.begin(), dest.end());
	}
}

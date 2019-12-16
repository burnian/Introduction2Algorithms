#include <iostream>
#include <random>
#include <time.h>
#include "MaxSubarray.h"


#define LEN 90000



void main(int args, char* argv) {
	std::random_device rd;

	int a[LEN];
	for (int i = 0; i < LEN; i++) {
		a[i] = rd() % 100 - 50;
	}

	//for (auto &v : a) {
	//	std::cout << v << " ";
	//}
	//std::cout << std::endl;
	//std::cout << std::endl;
	//int a[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };

	std::cout << "MaxSubarrayDQ 开始时间：" << clock() << std::endl;
	Bur::MSARes* r = Bur::MaxSubarrayDQ(a, 0, LEN - 1);
	std::cout << "MaxSubarrayDQ 结束时间：" << clock() << std::endl;
	std::cout << r->left << " " << r->right << " " << r->sum << std::endl;

	int i, j;
	std::cout << "MaxSubarrayBF 开始时间：" << clock() << std::endl;
	int res = Bur::MaxSubarrayBF(LEN, a, i, j);
	std::cout << "MaxSubarrayBF 结束时间：" << clock() << std::endl;
	std::cout << i << " " << j << " " << res << std::endl;

	system("pause");
}

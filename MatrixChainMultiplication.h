/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 10/16/2019, 15:59
*@Last Modify: 11/12/2019, 17:40
*@Desc: 矩阵链乘法计算顺序（matrix-chain multiplication computing order）最优算法。
*		对于同一条矩阵链，不同的计算顺序，其计算量有天壤之别，该算法用于获取计算量最少的那种计算顺序。
*********************************************************/
#pragma once
#include <iostream>


namespace Bur {
	// 用一维数组存储上三角矩阵，(1 + i)*i / 2为等差数列求和公式
	//@param i row下标
	//@param j col下标
	//@param n 一行的列数
	int MatIdx(int i, int j, int n) {
		return i * n + j - (1 + i)*i / 2;
	}

	// 每个子链的最优计算次数都存在 optimal
	//@param matChain 存放矩阵的数组，其中元素为数组，0表行数，1表列数
	//@param n 矩阵数
	//@param optimal 保存各子问题的最优解，即第i个到第j个矩阵的最小计算次数。
	//@param cutIdx 从i号矩阵到j号矩阵的最优算法要从cutIdx处切开分别相乘
	void OptimalMatChainMultiOrder(int(*matChain)[2], int n, int* optimal, int* cutIdx) {
		for (int l = 1; l <= n - 1; l++) // 根据子链规模递增，大规模的子链计算结果可以通过查找小规模子链的结果来获得，避免重复计算
			for (int i = 0; i < n - l; i++) {
				int j = i + l;
				for (int k = i; k < j; k++) {
					int temp = optimal[MatIdx(i, k, n)] + optimal[MatIdx(k + 1, j, n)] \
						+ matChain[i][0] * matChain[k][1] * matChain[j][1]; // 标量乘法的计算次数
					int idx = MatIdx(i, j, n);
					if (optimal[idx] <= 0 || temp < optimal[idx]) {
						optimal[idx] = temp;
						cutIdx[idx] = k;
					}
				}
			}
	}

	void PrintOrder(int* cutIdx, int i, int j, int n) {
		if (i == j) {
			std::cout << "A" << i+1;
			return;
		}
		int k = cutIdx[MatIdx(i, j, n)];
		std::cout << "(";
		PrintOrder(cutIdx, i, k, n);
		PrintOrder(cutIdx, k + 1, j, n);
		std::cout << ")";
	}

	// 贪心实现
	int MatChainMultiOrderGD(const int(*matChain)[2], int n) {
		int(*copyChain)[2] = new int[n][2];
		memcpy(copyChain, matChain, n * 2 * sizeof(int));

		int* order = new int[n - 1]; // 对矩阵链中的所有列维数据进行插入排序，从大到小，最后把矩阵下标存在order中
		for (int i = 0; i < n - 1; i++) {
			int j = i - 1;
			while (j >= 0 && copyChain[i][1] > copyChain[order[j]][1])
				order[j + 1] = order[j--];
			order[j + 1] = i;
		}
		int sum = 0;
		for (int i = 0; i < n - 1; i++) {
			sum += copyChain[order[i]][0] * copyChain[order[i]][1] * copyChain[order[i] + 1][1];
			// 矩阵合并后，修改行列值
			copyChain[order[i]][1] = copyChain[order[i] + 1][1];
			copyChain[order[i] + 1][0] = copyChain[order[i]][0];
		}
		return sum;
	}
}

// test case:
//随机生成一组长度为LEN的矩阵链
//std::random_device rd;
//int arr[LEN][2];
//int last = rd() % 100 + 1;
//for (int i = 0; i < LEN; i++) {
//	arr[i][0] = last;
//	last = rd() % 100 + 1;
//	arr[i][1] = last;
//}
//
//for (int i = 0; i < LEN; i++) {
//	std::cout << "(" << arr[i][0] << "," << arr[i][1] << ")";
//}
//std::cout << std::endl;
//std::cout << std::endl;
//
//int arr[6][2] = {
//	{30,35},
//	{35,15},
//	{15,5},
//	{5,10},
//	{10,20},
//	{20,25}
//};
//int optimal[40] = { 0 };
//int cutIdx[40];
//Bur::OptimalMatChainMultiOrder(arr, 6, optimal, cutIdx);
//for (int i = 6, idx = 0; i > 0; i--) {
//	for (int j = 0; j < i; j++) {
//		std::cout << optimal[idx + j] << " ";
//	}
//	idx += i;
//	std::cout << std::endl;
//}
//
//std::cout << std::endl;
//
//for (int i = 6, idx = 0; i > 0; i--) {
//	for (int j = 0; j < i; j++) {
//		std::cout << cutIdx[idx + j] << " ";
//	}
//	idx += i;
//	std::cout << std::endl;
//}
//
//std::cout << std::endl;
//
//std::cout << optimal[Bur::MatIdx(0, 5, 6)] << std::endl;
//
//std::cout << std::endl;
//Bur::PrintOrder(cutIdx, 0, 5, 6);

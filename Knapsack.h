/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/17/2019, 12:01
*@Last Modify: 11/17/2019, 16:06
*@Desc: 0-1背包，该算法不用对数据进行预处理，比如根据物品重量或者性价比排序
*		所谓动态规划，指的是总是利用小规模问题的最优解来推出较大规模问题的最优解，细节上就是一个填表的过程
*********************************************************/
#pragma once
#include <iostream>

namespace Bur {
	//value weight 都是 0~n-1 的，trace 是 0~n-1,0~capacity-1 的
	int Knapsack01(int* value, int* weight, int n, int capacity, bool** trace) {
		int temp1, temp2;
		// 最大价值表，纵向表示待考虑的各物品，横向表示待考虑的容量，内容为当前最大价值
		int** tab = new int*[n + 1];
		for (int i = 0; i <= n; i++) {
			tab[i] = new int[capacity + 1]{ 0 };
		}
		// i表示当前考虑的物品编号，j表示当前考虑的容量
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= capacity; j++) {
				if (weight[i - 1] > j) {
					tab[i][j] = tab[i - 1][j];
					trace[i - 1][j - 1] = false;
				}
				else {
					temp1 = value[i - 1] + tab[i - 1][j - weight[i - 1]]; // 纳入i号物品的最大价值
					temp2 = tab[i - 1][j]; // 不纳入i号物品的最大价值
					if (temp1 > temp2) {
						tab[i][j] = temp1;
						trace[i - 1][j - 1] = true;
					}
					else {
						tab[i][j] = temp2;
						trace[i - 1][j - 1] = false;
					}
				}
			}
		}
		temp1 = tab[n][capacity];

		for (int i = 0; i <= n; i++) {
			delete[] tab[i];
		}
		delete[] tab;

		return temp1;
	}

	//@param i 物品编号 1~n
	//@param j 当前背包容量 1~capacity
	void PrintKnapsack01(bool** trace, int* weight, int i, int j) {
		if (i <= 0 || j <= 0)
			return;
		if (trace[i - 1][j - 1]) {
			PrintKnapsack01(trace, weight, i - 1, j -= weight[i - 1]);
			std::cout << i << " ";
		}
		else {
			PrintKnapsack01(trace, weight, i - 1, j);
		}
	}
}


// test case:
//int value[] = { 22,6,18,28,1 };
//int weight[] = { 6,2,5,7,1 };
//int n = 5;
//int capacity = 11;
//
//bool** trace = new bool*[n];
//for (int i = 0; i < n; i++) {
//	trace[i] = new bool[capacity] {false};
//}
//
//int maxVal = Bur::Knapsack01(value, weight, n, capacity, trace);
//std::cout << maxVal << std::endl;
//Bur::PrintKnapsack01(trace, weight, n, capacity);
//std::cout << std::endl;
//
//for (int i = 0; i < n; i++) {
//	delete[] trace[i];
//}
//delete[] trace;

/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/17/2019, 12:01
*@Last Modify: 11/17/2019, 16:06
*@Desc: 0-1���������㷨���ö����ݽ���Ԥ�������������Ʒ���������Լ۱�����
*		��ν��̬�滮��ָ������������С��ģ��������Ž����Ƴ��ϴ��ģ��������Ž⣬ϸ���Ͼ���һ�����Ĺ���
*********************************************************/
#pragma once
#include <iostream>

namespace Bur {
	//value weight ���� 0~n-1 �ģ�trace �� 0~n-1,0~capacity-1 ��
	int Knapsack01(int* value, int* weight, int n, int capacity, bool** trace) {
		int temp1, temp2;
		// ����ֵ�������ʾ�����ǵĸ���Ʒ�������ʾ�����ǵ�����������Ϊ��ǰ����ֵ
		int** tab = new int*[n + 1];
		for (int i = 0; i <= n; i++) {
			tab[i] = new int[capacity + 1]{ 0 };
		}
		// i��ʾ��ǰ���ǵ���Ʒ��ţ�j��ʾ��ǰ���ǵ�����
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= capacity; j++) {
				if (weight[i - 1] > j) {
					tab[i][j] = tab[i - 1][j];
					trace[i - 1][j - 1] = false;
				}
				else {
					temp1 = value[i - 1] + tab[i - 1][j - weight[i - 1]]; // ����i����Ʒ������ֵ
					temp2 = tab[i - 1][j]; // ������i����Ʒ������ֵ
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

	//@param i ��Ʒ��� 1~n
	//@param j ��ǰ�������� 1~capacity
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

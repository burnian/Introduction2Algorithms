/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 10/16/2019, 15:59
*@Last Modify: 11/12/2019, 17:40
*@Desc: �������˷�����˳��matrix-chain multiplication computing order�������㷨��
*		����ͬһ������������ͬ�ļ���˳���������������֮��
*********************************************************/
#pragma once
#include <iostream>


namespace Bur {
	// ��һά����洢�����Ǿ���(1 + i)*i / 2Ϊ�Ȳ�������͹�ʽ
	//@param i row�±�
	//@param j col�±�
	//@param n һ�е�����
	int MatIdx(int i, int j, int n) {
		return i * n + j - (1 + i)*i / 2;
	}

	// ÿ�����������ż������������ optimal
	//@param matChain ��ž�������飬����Ԫ��Ϊ���飬0��������1������
	//@param n ������
	//@param optimal ���������������Ž⣬����i������j���������С���������
	void OptimalMatChainMultiOrder(int(*matChain)[2], int n, int* optimal, int* cutIdx) {
		for (int l = 1; l <= n - 1; l++) // ����������ģ���������ģ����������������ͨ������С��ģ�����Ľ������ã������ظ�����
			for (int i = 0; i < n - l; i++) {
				int j = i + l;
				for (int k = i; k < j; k++) {
					int temp = optimal[MatIdx(i, k, n)] + optimal[MatIdx(k + 1, j, n)] \
						+ matChain[i][0] * matChain[k][1] * matChain[j][1];
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
}

// test code:
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

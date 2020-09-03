/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 08/29/2020, 10:30
*@Last Modify: 08/30/2020, 16:18
*@Desc: 130�⣺��Χ�Ƶ�����
		����Χ������ӹ��򣬵��Ǳ߽紦��O������
*********************************************************/
#pragma once
#include <iostream>
#include <vector>
#include "UnionFindSet.h"


namespace Bur {
	const int DIR[2][2] = { {0,1}, {1,0} };

	void printMat(std::vector<std::vector<char>>& board) {
		for (auto v : board) {
			for (auto vv : v) {
				std::cout << vv;
			}
			std::cout << std::endl;
		}
	}

	void solve(std::vector<std::vector<char>>& board) {
		size_t m = board.size();
		if (m <= 0) return;
		size_t n = board[0].size();
		// ��ʶδ��X��Χ��O������
		size_t openIdx = m * n;
		UnionFindSet ufSet(openIdx + 1);
		size_t idx = 0;
		int temp1, temp2;
		// ��������O�����������ߵĺ�openIdx������
		for (size_t i = 0; i < m; i++) {
			for (size_t j = 0; j < n; j++) {
				if (board[i][j] == 'O') {
					idx = i * n + j;
					for (int k = 0; k < 2; k++) {
						temp1 = i + DIR[k][0];
						temp2 = j + DIR[k][1];
						if (temp1 < m && temp2 < n && board[temp1][temp2] == 'O') {
							ufSet.Unite(idx, temp1 * n + temp2);
						}
					}
					if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
						ufSet.Unite(idx, openIdx);
					}
				}
			}
		}
		for (size_t i = 0; i < m; i++) {
			for (size_t j = 0; j < n; j++) {
				idx = i * n + j;
				if (ufSet.Find(idx) != ufSet.Find(openIdx)) {
					board[i][j] = 'X';
				}
			}
		}
	}
}

//test case:
//std::vector<std::vector<char>> board = {
//	{'X','X','X','X'},
//	{'X','O','O','X'},
//	{'X','X','O','X'},
//	{'X','O','X','X'},
//};
//
//Bur::printMat(board);
//Bur::solve(board);
//std::cout << std::endl;
//Bur::printMat(board);

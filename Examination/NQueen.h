/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 12/29/2019, 00:00
*@Last Modify: 12/30/2019, 17:46
*@Desc: N皇后问题，回溯解法，都不属于暴力求解，在遍历状态空间树的时候都跳过了多个无解子树
*********************************************************/
#pragma once
#include <iostream>
#include <vector>

#define NUM 8

namespace Bur{
	// 检查row行的皇后是否和其他行的皇后冲突（在同一行/列/对角线的情况）
	bool IsConflict(int* board, int row) {
		for (int i = 0; i < row; i++) {
			if ((board[row] == board[i])
				|| (row + board[row] == i + board[i])
				|| (row - board[row] == i - board[i]))
				return true;
		}
		return false;
	}
	// 
	void NQueenPrint(int* board, int n) {
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < board[i]; j++)
				std::cout << "#";
			std::cout << "O";
			for (int j = board[i] + 1; j < n; j++)
				std::cout << "#";
			std::cout << std::endl;
		}
		std::cout << "==========================\n";
	}
	// 循环非递归回溯求解
	//@param n 棋盘尺寸
	void NQueenBT(int n) {
		int i = 0;
		int* board = new int[n] {0};
		while (board[0] < n) {
			while (i < n) {
				while (board[i] < n && IsConflict(board, i))
					board[i]++;
				if (board[i] >= n) { // 该行无解
					// 当前行为首行，状态空间树的根节点
					if (i <= 0) {
						delete board;
						return;
					}
					// 回溯
					board[i] = 0;
					board[--i]++;
				}
				else
					i++;
			}
			//NQueenPrint(board, n);
			// 最后一行继续向后探索
			board[--i]++;
		}
	}
	// 比 NQueenBT 稍快
	void NQueenBT2(int n) {
		int* board = new int[n] {0};
		int i = 0;
		while (i >= 0) {
			while (board[i] < n && IsConflict(board, i))
				board[i]++;
			if (board[i] >= n) { // 该行无解
				// 回溯
				board[i--] = 0;
				if (i >= 0)
					board[i]++;
			}
			else { // 该行有解
				if (i == n - 1) { // 打印该组解
					//NQueenPrint(board, n);
					// 回溯
					board[i--] = 0;
					if (i >= 0)
						board[i]++;
				}
				else
					i++;
			}
		}
		delete board;
	}

	// test case:
	//std::cout << "NQueenBT 开始时间：" << clock() << std::endl;
	//Bur::NQueenBT(8);
	//std::cout << "NQueenBT 结束时间：" << clock() << std::endl;


	static int gBoard[NUM] = { 0 }, gCount = 0;
	// 输出每一种情况下棋盘中皇后的摆放情况
	void Print()
	{
		for (int i = 0; i < NUM; i++)
		{
			for (int j = 0; j < gBoard[i]; j++)
				std::cout << "#";
			std::cout << "O";
			for (int j = gBoard[i] + 1; j < NUM; j++)
				std::cout << "#";
			std::cout << std::endl;
		}
		std::cout << "==========================\n";
	}
	// 检查是否存在有多个皇后在同一行/列/对角线的情况
	bool IsValid(int row, int col)
	{
		int col2;
		for (int row2 = 0; row2 < row; row2++)
		{
			col2 = gBoard[row2];
			if ((col == col2) || (row + col) == (row2 + col2) || (row - col) == (row2 - col2))
				return false;
		}
		return true;
	}
	//Rcs 即recursive，递归回溯求解，该方法比循环非递归回溯求解 NQueenBT2 更快
	//@idx 从1开始，即第一行
	void NQueenRcs(int row) {
		for (int col = 0; col < NUM; col++) {
			if (IsValid(row, col)) {
				gBoard[row] = col;
				if (row >= NUM - 1) {
					// 因为前n-1行已经占去n-1列，所以最后一行有且仅有唯一落子位，找到该位则无需再去判断其后位置是否可行
					gCount++;
					//Print();
					return;
				}
				NQueenRcs(row + 1);
			}
		}
	}
	// test case:
	//std::cout << "NQueenRcs 开始时间：" << clock() << std::endl;
	//Bur::NQueenRcs(1);
	//std::cout << "NQueenRcs 结束时间：" << clock() << std::endl;
}

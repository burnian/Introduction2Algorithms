/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 12/29/2019, 00:00
*@Last Modify: 12/30/2019, 17:46
*@Desc: N�ʺ����⣬���ݽⷨ���������ڱ�����⣬�ڱ���״̬�ռ�����ʱ�������˶���޽�����
*********************************************************/
#pragma once
#include <iostream>
#include <vector>

#define NUM 8

namespace Bur{
	// ���row�еĻʺ��Ƿ�������еĻʺ��ͻ����ͬһ��/��/�Խ��ߵ������
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
	// ѭ���ǵݹ�������
	//@param n ���̳ߴ�
	void NQueenBT(int n) {
		int i = 0;
		int* board = new int[n] {0};
		while (board[0] < n) {
			while (i < n) {
				while (board[i] < n && IsConflict(board, i))
					board[i]++;
				if (board[i] >= n) { // �����޽�
					// ��ǰ��Ϊ���У�״̬�ռ����ĸ��ڵ�
					if (i <= 0) {
						delete board;
						return;
					}
					// ����
					board[i] = 0;
					board[--i]++;
				}
				else
					i++;
			}
			//NQueenPrint(board, n);
			// ���һ�м������̽��
			board[--i]++;
		}
	}
	// �� NQueenBT �Կ�
	void NQueenBT2(int n) {
		int* board = new int[n] {0};
		int i = 0;
		while (i >= 0) {
			while (board[i] < n && IsConflict(board, i))
				board[i]++;
			if (board[i] >= n) { // �����޽�
				// ����
				board[i--] = 0;
				if (i >= 0)
					board[i]++;
			}
			else { // �����н�
				if (i == n - 1) { // ��ӡ�����
					//NQueenPrint(board, n);
					// ����
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
	//std::cout << "NQueenBT ��ʼʱ�䣺" << clock() << std::endl;
	//Bur::NQueenBT(8);
	//std::cout << "NQueenBT ����ʱ�䣺" << clock() << std::endl;


	static int gBoard[NUM] = { 0 }, gCount = 0;
	// ���ÿһ������������лʺ�İڷ����
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
	// ����Ƿ�����ж���ʺ���ͬһ��/��/�Խ��ߵ����
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
	//Rcs ��recursive���ݹ������⣬�÷�����ѭ���ǵݹ������� NQueenBT2 ����
	//@idx ��1��ʼ������һ��
	void NQueenRcs(int row) {
		for (int col = 0; col < NUM; col++) {
			if (IsValid(row, col)) {
				gBoard[row] = col;
				if (row >= NUM - 1) {
					// ��Ϊǰn-1���Ѿ�ռȥn-1�У��������һ�����ҽ���Ψһ����λ���ҵ���λ��������ȥ�ж����λ���Ƿ����
					gCount++;
					//Print();
					return;
				}
				NQueenRcs(row + 1);
			}
		}
	}
	// test case:
	//std::cout << "NQueenRcs ��ʼʱ�䣺" << clock() << std::endl;
	//Bur::NQueenRcs(1);
	//std::cout << "NQueenRcs ����ʱ�䣺" << clock() << std::endl;
}

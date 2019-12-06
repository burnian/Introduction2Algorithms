/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/12/2019, 17:39
*@Last Modify: 11/16/2019, 18:40
*@Desc: longest common subsequence ���ͬ�����С���Ҫ˼���ǣ�
*       �����ڳ���Ϊ i ������ A �� j �� ���� B �ĺ���ֱ����һ��Ԫ��
*		1.����ӵ�����Ԫ�ز�ͬʱ��tab(i+1,j+1) = max(tab(i+1, j), tab(i, j+1))�����ֵҲ������ tab(i, j) + 1
*		2.����ӵ�����Ԫ����ͬʱ��tab(i+1,j+1) = tab(i, j) + 1��֤����Ȼ tab(i, j) + 1 <= tab(i+1,j+1) <= tab(i, j) + 2��
*		  �� tab(i+1,j+1) = tab(i, j) + 2����˵�� ei+1 �� ej+1 �ֱ�����һ��ƥ�䣬������ A ��ĩβԪ�� ei+1 ƥ���� B �е�
*		  Ԫ�� ek����ô ej+1 һ��ֻ��ƥ�� ei+1 �����Ԫ�أ�����Ȼ�����ܣ����Զ���ֻ������һ������һ��ƥ�䣬�����ܶ�ƥ�䣬���
*		  ֤���� tab(i+1,j+1) < tab(i, j) + 2
*********************************************************/
#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace Bur {
	//@param str1 str2 ����ȡ������е������ַ���
	//@param trace 
	void LCS(const std::string& str1, const std::string& str2, int** trace) {
		int x = str1.length();
		int y = str2.length();
		// ���������г��ȵĶ�ά���� tab
		int** tab = new int*[x + 1];
		tab[0] = new int[y + 1]{ 0 };
		for (int i = 1; i <= x; i++) {
			tab[i] = new int[y+1] {0};
			for (int j = 1; j <= y; j++) {
				if (str1[i - 1] == str2[j - 1]) {
					tab[i][j] = tab[i - 1][j - 1] + 1;
					trace[i - 1][j - 1] = 0; // ��ʾtabֵ������ȡ
				}
				else if (tab[i - 1][j] > tab[i][j - 1]) {
					tab[i][j] = tab[i - 1][j];
					trace[i - 1][j - 1] = 1; // ��ʾtabֵ����ȡ
				}
				else {
					tab[i][j] = tab[i][j - 1];
					trace[i - 1][j - 1] = 2; // ��ʾtabֵ����ȡ
				}
			}
		}

		for (int i = 0; i <= x; i++) {
			for (int j = 0; j <= y; j++) {
				std::cout << tab[i][j] << " ";
			}
			std::cout << std::endl;
		}

		for (int i = 0; i <= x; i++) {
			delete[] tab[i];
		}
		delete[] tab;
	}

	// ֮����ѡ��Ӻ���ǰ�ݹ��ӡ����Ϊ��ÿ�� trace �ڵ㶼�ж��ǰ����Ψһ��̣�����ֻ����βԪ�ص��±���ȷ
	// �����Ƚϵľ��������������У�ֻ�е��Ƚ����У�ĩβ�±꣩ȷ�������ȷ��ƥ�䴦��켣��
	//@param i ��ʾ str1 ��βԪ���±�
	//@param j ��ʾ str2 ��βԪ���±�
	void PrintLCS(const std::string& str1, int** trace, int i, int j) {
		if (i < 0 || j < 0)
			return;
		if (trace[i][j] == 0) {
			PrintLCS(str1, trace, i - 1, j - 1);
			std::cout << str1[i]; // �� PrintLCS �����ԭ����
		}
		else if (trace[i][j] == 1) {
			PrintLCS(str1, trace, i - 1, j);
		}
		else {
			PrintLCS(str1, trace, i, j - 1);
		}
	}
}


/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/12/2019, 17:39
*@Last Modify: 11/16/2019, 18:40
*@Desc: longest common subsequence 最长相同子序列。主要思想是：
*       总是在长度为 i 的序列 A 和 j 的 序列 B 的后面分别添加一个元素
*		1.当添加的这俩元素不同时，tab(i+1,j+1) = max(tab(i+1, j), tab(i, j+1))。最大值也不过是 tab(i, j) + 1
*		2.当添加的这俩元素相同时，tab(i+1,j+1) = tab(i, j) + 1。证：显然 tab(i, j) + 1 <= tab(i+1,j+1) <= tab(i, j) + 2；
*		  若 tab(i+1,j+1) = tab(i, j) + 2，则说明 ei+1 和 ej+1 分别贡献了一个匹配，不妨设 A 的末尾元素 ei+1 匹配了 B 中的
*		  元素 ek，那么 ej+1 一定只能匹配 ei+1 后面的元素，这显然不可能，所以二者只能有其一贡献了一个匹配，不可能都匹配，这就
*		  证明了 tab(i+1,j+1) < tab(i, j) + 2
*********************************************************/
#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace Bur {
	//@param str1 str2 待获取最长子序列的两个字符串
	//@param trace 
	void LCS(const std::string& str1, const std::string& str2, int** trace) {
		int x = str1.length();
		int y = str2.length();
		// 存放最长子序列长度的二维数组 tab
		int** tab = new int*[x + 1];
		tab[0] = new int[y + 1]{ 0 };
		for (int i = 1; i <= x; i++) {
			tab[i] = new int[y+1] {0};
			for (int j = 1; j <= y; j++) {
				if (str1[i - 1] == str2[j - 1]) {
					tab[i][j] = tab[i - 1][j - 1] + 1;
					trace[i - 1][j - 1] = 0; // 表示tab值向左上取
				}
				else if (tab[i - 1][j] > tab[i][j - 1]) {
					tab[i][j] = tab[i - 1][j];
					trace[i - 1][j - 1] = 1; // 表示tab值向上取
				}
				else {
					tab[i][j] = tab[i][j - 1];
					trace[i - 1][j - 1] = 2; // 表示tab值向左取
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

	// 之所以选择从后往前递归打印是因为，每个 trace 节点都有多个前驱和唯一后继，所以只能由尾元素的下标来确
	// 定待比较的具体是哪两条序列，只有当比较序列（末尾下标）确定后才能确定匹配处理轨迹。
	//@param i 表示 str1 的尾元素下标
	//@param j 表示 str2 的尾元素下标
	void PrintLCS(const std::string& str1, int** trace, int i, int j) {
		if (i < 0 || j < 0)
			return;
		if (trace[i][j] == 0) {
			PrintLCS(str1, trace, i - 1, j - 1);
			std::cout << str1[i]; // 放 PrintLCS 下面的原因是
		}
		else if (trace[i][j] == 1) {
			PrintLCS(str1, trace, i - 1, j);
		}
		else {
			PrintLCS(str1, trace, i, j - 1);
		}
	}
}


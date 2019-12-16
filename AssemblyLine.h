/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 10/14/2019, 17:46
*@Last Modify: 10/16/2019, 15:57
*@Desc: 双装配线最快调度算法，输入两组装配线所有站的装配和切换时间，输出最快装配安排。
*********************************************************/
#pragma once
#include <iostream>
#include <stack>

namespace Bur {
	struct Station {
		int switchCost; // 从外线前一站转到该站的转换开销
		int runCost; // 该站的运行开销
		int minTime = 0; // 从起始站到该站的最短装配时间
		int preLine = 0; // 装配到该站的前一站所属线号

		Station(int _1, int _2) :switchCost(_1), runCost(_2) {};
	};

	//@param station[i][j] 存的是i号线j站，之所以不用链表存储station是因为之后还要用分治实现
	//@param cnt 站数（不含终点站）
	int AssemblyLineDP(Station*** s, int cnt) {
		int temp1, temp2;
		// 起始站处理 i=0
		s[0][0]->minTime = s[0][0]->switchCost + s[0][0]->runCost;
		s[1][0]->minTime = s[1][0]->switchCost + s[1][0]->runCost;
		for (int i = 1; i < cnt; i++) {
			// 处理0号线i站
			temp1 = s[0][i - 1]->minTime;
			temp2 = s[1][i - 1]->minTime + s[0][i]->switchCost;
			if (temp1 < temp2) {
				s[0][i]->preLine = 0;
				s[0][i]->minTime = temp1 + s[0][i]->runCost;
			}
			else {
				s[0][i]->preLine = 1;
				s[0][i]->minTime = temp2 + s[0][i]->runCost;
			}
			// 处理1号线i站
			temp1 = s[0][i - 1]->minTime + s[1][i]->switchCost;
			temp2 = s[1][i - 1]->minTime;
			if (temp1 < temp2) {
				s[1][i]->preLine = 0;
				s[1][i]->minTime = temp1 + s[1][i]->runCost;
			}
			else {
				s[1][i]->preLine = 1;
				s[1][i]->minTime = temp2 + s[1][i]->runCost;
			}
		}
		// 终点站处理
		s[0][cnt]->preLine = 1;
		s[0][cnt]->minTime = s[1][cnt - 1]->minTime + s[0][cnt]->switchCost;
		s[1][cnt]->preLine = 0;
		s[1][cnt]->minTime = s[0][cnt - 1]->minTime + s[1][cnt]->switchCost;

		return s[0][cnt]->minTime < s[1][cnt]->minTime ? 0 : 1;
	}

	void PrintAssemblyLine(Station*** s, int line, int cnt) {
		std::cout << s[line][cnt]->minTime << std::endl;
		for (int i = cnt; i > 0; i--) {
			line = s[line][i]->preLine;
			std::cout << "(" << line + 1 << "," << i << ")" << std::endl;
		}
	}
}

// test case:
//int cnt = 6;
//Bur::Station*** station = new Bur::Station**[2]{
//	new Bur::Station*[cnt + 1] {
//		new Bur::Station(2, 7),
//		new Bur::Station(2, 9),
//		new Bur::Station(1, 3),
//		new Bur::Station(2, 4),
//		new Bur::Station(2, 8),
//		new Bur::Station(1, 4),
//		new Bur::Station(2, 0) // 终点站为虚站
//	},
//	new Bur::Station*[cnt + 1] {
//		new Bur::Station(4, 8),
//		new Bur::Station(2, 5),
//		new Bur::Station(3, 6),
//		new Bur::Station(1, 4),
//		new Bur::Station(3, 5),
//		new Bur::Station(4, 7),
//		new Bur::Station(3, 0) // 终点站为虚站
//	},
//};
//int outLine = Bur::AssemblyLineDP(station, cnt);
//Bur::PrintAssemblyLine(station, outLine, cnt);
/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 10/14/2019, 17:46
*@Last Modify: 10/16/2019, 15:57
*@Desc: assembly line schedule (als)，双装配线最快调度算法，输入两组装配线所
*	有站的装配和切换时间，输出最快装配安排。
*********************************************************/
#pragma once
#include <iostream>


namespace Bur {
	struct Station {
		int switchCost; // 从外线前一站转到该站的转换开销
		int runCost; // 该站的运行开销
		int minTime = 0; // 从起始站到该站的最短装配时间
		int preLine = 0; // 装配到该站的前一站所属线号

		Station(int _1, int _2) :switchCost(_1), runCost(_2) {};
	};

	// DP算法有给出最短路径
	//@param station[i][j] 存的是i号线j站，之所以不用链表存储station是因为之后还要用分治实现
	//@param cnt 站数（不含终点站）
	//@return 装配时间最短的终点站所在的线路
	int ALS_DP(Station*** s, int cnt) {
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

	void PrintAL(Station*** s, int line, int cnt) {
		std::cout << s[line][cnt]->minTime << std::endl;
		for (int i = cnt; i > 0; i--) {
			line = s[line][i]->preLine;
			std::cout << "(" << line + 1 << "," << i << ")" << std::endl;
		}
	}


	int minOf4(int i1, int i2, int i3, int i4) {
		int ret1 = i1 < i2 ? i1 : i2;
		int ret2 = i3 < i4 ? i3 : i4;
		return ret1 < ret2 ? ret1 : ret2;
	}

	class ALSection {
	public:
		ALSection(int _1, int _2) :start(_1), end(_2) {};
		// 把merge方法写在class里面的好处就在于返回值可以继续调用merge方法
		ALSection* MergeRight(Station*** s, ALSection* secR) {
			int temp1 = minOf4(
				min00 + secR->min00,
				min00 + s[1][secR->start]->switchCost + secR->min10,
				min01 + s[0][secR->start]->switchCost + secR->min00,
				min01 + secR->min10
			);
			int temp2 = minOf4(
				min00 + secR->min01,
				min00 + s[1][secR->start]->switchCost + secR->min11,
				min01 + s[0][secR->start]->switchCost + secR->min01,
				min01 + secR->min11
			);
			int temp3 = minOf4(
				min10 + secR->min00,
				min10 + s[1][secR->start]->switchCost + secR->min10,
				min11 + s[0][secR->start]->switchCost + secR->min00,
				min11 + secR->min10
			);
			int temp4 = minOf4(
				min10 + secR->min01,
				min10 + s[1][secR->start]->switchCost + secR->min11,
				min11 + s[0][secR->start]->switchCost + secR->min01,
				min11 + secR->min11
			);
			min00 = temp1;
			min01 = temp2;
			min10 = temp3;
			min11 = temp4;
			end = secR->end;
			return this;
		}

		void Print() {
			std::cout << start << "->" << end << ": (minLTRT: " << min00 << ", minLTRB: " <<
				min01 << ", minLBRT: " << min10 << ", minLBRB: " << min11 << std::endl;
		}
	public:
		int start, end;
		int min00; // left-top to right-top
		int min01; // left-top to right-bottom
		int min10; // left-bottom to right-top
		int min11; // left-bottom to right-bottom
	};

	// DC算法没有给出最短路径
	// 执行完后会多出一个ALSection 对象，需要在外部delete
	ALSection* ALS_DC(Station*** s, int l, int r) {
		if (l == r) {
			ALSection* ret = new ALSection(l, r);
			ret->min00 = s[0][l]->runCost;
			ret->min01 = s[0][l]->runCost + s[1][r]->runCost;
			ret->min10 = s[1][l]->runCost + s[0][r]->runCost;
			ret->min11 = s[1][l]->runCost;
			return ret;
		}
		int m = (l + r) / 2;
		ALSection* secL = ALS_DC(s, l, m);
		ALSection* secR = ALS_DC(s, m + 1, r);
		secL->MergeRight(s, secR);
		delete secR;
		return secL;
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
//int outLine = Bur::ALS_DP(station, cnt);
//Bur::PrintAL(station, outLine, cnt);

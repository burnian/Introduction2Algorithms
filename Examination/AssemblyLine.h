/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 10/14/2019, 17:46
*@Last Modify: 10/16/2019, 15:57
*@Desc: assembly line schedule (als)��˫װ�����������㷨����������װ������
*	��վ��װ����л�ʱ�䣬������װ�䰲�š�
*********************************************************/
#pragma once
#include <iostream>


namespace Bur {
	struct Station {
		int switchCost; // ������ǰһվת����վ��ת������
		int runCost; // ��վ�����п���
		int minTime = 0; // ����ʼվ����վ�����װ��ʱ��
		int preLine = 0; // װ�䵽��վ��ǰһվ�����ߺ�

		Station(int _1, int _2) :switchCost(_1), runCost(_2) {};
	};

	// DP�㷨�и������·��
	//@param station[i][j] �����i����jվ��֮���Բ�������洢station����Ϊ֮��Ҫ�÷���ʵ��
	//@param cnt վ���������յ�վ��
	//@return װ��ʱ����̵��յ�վ���ڵ���·
	int ALS_DP(Station*** s, int cnt) {
		int temp1, temp2;
		// ��ʼվ���� i=0
		s[0][0]->minTime = s[0][0]->switchCost + s[0][0]->runCost;
		s[1][0]->minTime = s[1][0]->switchCost + s[1][0]->runCost;
		for (int i = 1; i < cnt; i++) {
			// ����0����iվ
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
			// ����1����iվ
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
		// �յ�վ����
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
		// ��merge����д��class����ĺô������ڷ���ֵ���Լ�������merge����
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

	// DC�㷨û�и������·��
	// ִ��������һ��ALSection ������Ҫ���ⲿdelete
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
//		new Bur::Station(2, 0) // �յ�վΪ��վ
//	},
//	new Bur::Station*[cnt + 1] {
//		new Bur::Station(4, 8),
//		new Bur::Station(2, 5),
//		new Bur::Station(3, 6),
//		new Bur::Station(1, 4),
//		new Bur::Station(3, 5),
//		new Bur::Station(4, 7),
//		new Bur::Station(3, 0) // �յ�վΪ��վ
//	},
//};
//int outLine = Bur::ALS_DP(station, cnt);
//Bur::PrintAL(station, outLine, cnt);

/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 10/14/2019, 17:46
*@Last Modify: 10/16/2019, 15:57
*@Desc: ˫װ�����������㷨����������װ��������վ��װ����л�ʱ�䣬������װ�䰲�š�
*********************************************************/
#pragma once
#include <iostream>
#include <stack>

namespace Bur {
	struct Station {
		int switchCost; // ������ǰһվת����վ��ת������
		int runCost; // ��վ�����п���
		int minTime = 0; // ����ʼվ����վ�����װ��ʱ��
		int preLine = 0; // װ�䵽��վ��ǰһվ�����ߺ�

		Station(int _1, int _2) :switchCost(_1), runCost(_2) {};
	};

	//@param station[i][j] �����i����jվ��֮���Բ�������洢station����Ϊ֮��Ҫ�÷���ʵ��
	//@param cnt վ���������յ�վ��
	int AssemblyLineDP(Station*** s, int cnt) {
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
//int outLine = Bur::AssemblyLineDP(station, cnt);
//Bur::PrintAssemblyLine(station, outLine, cnt);
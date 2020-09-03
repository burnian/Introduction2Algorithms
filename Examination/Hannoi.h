/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 12/30/2019, 17:49
*@Last Modify: 12/30/2019, 18:08
*@Desc: ��ŵ���ݹ����
*********************************************************/
#pragma once
#include <iostream>

namespace Bur {
	// ����1����3
	//@param size ��ŵ���ߴ磬һ������ţ���������ţ����������
	void Hannoi(int size, int src, int mid, int des) {
		if (size <= 1) {
			std::cout << src << "->" << des << std::endl;
			return;
		}
		Hannoi(size - 1, src, des, mid);
		Hannoi(1, src, mid, des);
		Hannoi(size - 1, mid, src, des);
	}
	// test case:
	//Bur::Hannoi(3, 1, 2, 3);
}

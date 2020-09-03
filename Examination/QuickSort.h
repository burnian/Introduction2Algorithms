/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/25/2019, 19:49
*@Last Modify: 09/30/2019, 00:43
*@Desc: ���ţ���С����
*       ������������ȡpivot = rd() % interval + base��ֻҪintervalС��2^31�η����ͼ���������Ϊpivot����rd��min��max֮����ȷֲ���
*       ���ǿ��԰�rd��ȡֵscope����Ϊn��interval������ֻ��һ����ȡ������0 ~ interval-1�ģ����Ҳ���ڴˣ����в���ֵ���ֵĴ���Ҫ��������ֵ��
*       ����ֲ�������پ��ȣ���һ������£�interval����С��������΢�Ĳ�������ȫ���Ժ��ԡ�
*       std::random_device rd.min() = 0; rd.max() = 2^32
*********************************************************/
#pragma once
#include <random>


namespace Bur {
	//std::random_device rd;

	int Partition(int* a, int l, int r) {
		//int pivot = rd() % (r - l + 1) + l;
		int pivot = l;
		std::swap(a[pivot], a[r]);
		pivot = a[r];
		int i = l;
		for (int j = l; j < r; j++) {
			if (a[j] < pivot) {
				std::swap(a[i], a[j]);
				i++;
			}
		}
		std::swap(a[i], a[r]);
		return i;
	}

	void QuickSort(int* a, int l, int r) {
		if (l < r)
		{
			int m = Partition(a, l, r);
			QuickSort(a, l, m - 1);
			QuickSort(a, m + 1, r);
		}
	}
}

// test case:
//std::cout << "QuickSort ��ʼʱ�䣺" << clock() << std::endl;
//Bur::QuickSort(b, 0, LEN - 1);
//std::cout << "QuickSort ����ʱ�䣺" << clock() << std::endl;

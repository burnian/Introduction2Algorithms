/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/25/2019, 19:49
*@Last Modify: 09/30/2019, 00:43
*@Desc: 快排，从小到大
*       对于这里的随机取pivot = rd() % interval + base，只要interval小于2^31次方，就几乎可以认为pivot是在rd的min和max之间均匀分布的
*       我们可以把rd的取值scope划分为n份interval，其中只有一份是取不完整0 ~ interval-1的，误差也就在此，会有部分值出现的次数要多于其他值，
*       随机分布结果不再均匀，但一般情况下，interval都很小，所以略微的不均匀完全可以忽略。
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
//std::cout << "QuickSort 开始时间：" << clock() << std::endl;
//Bur::QuickSort(b, 0, LEN - 1);
//std::cout << "QuickSort 结束时间：" << clock() << std::endl;

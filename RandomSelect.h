/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/30/2019, 15:17
*@Last Modify: 09/30/2019, 15:17
*@Desc: 该算法旨在选出数组中第k大的数，T(n)的最好情况为n，最坏情况为n^2，pivot随机取。
*********************************************************/
#pragma once
#include "QuickSort.h"


namespace Bur{
	int RandomSelect(int* arr, int l, int r, int k) {
		int idx = RandomizedPartition(arr, l, r);
		int rank = idx + 1;
		if (k < rank)
			return RandomSelect(arr, l, idx - 1, k);
		else if (k > rank)
			return RandomSelect(arr, idx + 1, r, k);
		else
			return arr[idx];
	}
}

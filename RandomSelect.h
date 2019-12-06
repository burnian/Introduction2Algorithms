/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/30/2019, 15:17
*@Last Modify: 09/30/2019, 15:17
*@Desc: ���㷨ּ��ѡ�������е�k�������T(n)��������Ϊn������Ϊn^2��pivot���ȡ��
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

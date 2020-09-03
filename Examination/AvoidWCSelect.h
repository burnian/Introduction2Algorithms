/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/30/2019, 15:19
*@Last Modify: 10/01/2019, 18:15
*@Desc: 该算法旨在选出数组中第k大的数，最坏情况下时间复杂度在T(n)=cn，此时要求问题规模达到n>120，通过递归地选取中位数，
*       得到的最终中位数总有1/4的数大于它且1/4的数小于它，剩下的一半可能大于也可能小于它，
*       也就是说每次partition，最坏的情况下也至少可以扔掉30%的数据。
*       WC = Worst Case
*********************************************************/
#pragma once
#include "InsertSort.h"
#define GROUP_LENGTH 5


namespace Bur {
	int Partition(int* arr, int l, int r, int pivot) {
		std::swap(arr[pivot], arr[r]);
		pivot = arr[r];
		int i = l;
		for (int j = l; j < r; j++) {
			if (arr[j] < pivot) {
				std::swap(arr[i], arr[j]);
				i++;
			}
		}
		std::swap(arr[i], arr[r]);
		return i;
	}

	// 递归地选择中位数
	int MedianSelect(int* arr, int l, int r, int elemStep) {
		int groupStep = elemStep * GROUP_LENGTH;
		int groupCnt = (r - l + elemStep) / groupStep;
		for (int i = 0; i < groupCnt; i++) {
			int start = l + i * groupStep;
			InsertSort(arr, start, start + groupStep, elemStep);
		}

		if (groupCnt <= 0)
			// 中间组的中位数下标
			return l + (r - l) / elemStep / 2 * elemStep; // 这里不能化简，因为/符号为取商，丢掉余数，化简后就会导致余数被利用起来了
		else
			MedianSelect(arr, l + 2 * elemStep, l + (groupCnt - 1) * groupStep + 2 * elemStep, groupStep);
	}

	int AvoidWCSelect(int* arr, int l, int r, int k) {
		int pivot = MedianSelect(arr, l, r, 1);
		int m = Partition(arr, l, r, pivot);
		int rank = m + 1;
		if (k < rank)
			AvoidWCSelect(arr, l, m - 1, k);
		else if (k > rank)
			AvoidWCSelect(arr, m + 1, r, k);
		else
			return arr[m];
	}
}


//int arr[] = { 3,7,4,5,6,5,6,2,3,4,1,5,4,2,3,5,6,8,7,4,5,6,7,9,8 }; median 为 5
//int arr[] = { 29,22,28,14,45,
//			10,44,23,9,39,
//			38,52,6,5,50,
//			37,11,26,3,15,
//			2,53,40,54,25,
//			55,12,19,30,16,
//			18,13,1,48,41,
//			24,43,46,47,17,
//			34,20,31,32,33,
//			35,4,49,51,7,
//			36,27,8,21 }; 这组数据是1~55的随机排列，median 为 28
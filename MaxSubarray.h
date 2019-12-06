/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/30/2019, 00:26
*@Last Modify: 09/30/2019, 00:26
*@Desc: 分治递归求最大子数组
*********************************************************/
#pragma once
#include <iostream>


namespace Bur {
	class MSARes
	{
	public:
		MSARes(int l, int r, int s) :left(l), right(r), sum(s) {};
	public:
		int left;
		int right;
		int sum;
	};

	MSARes* MaxCrossSubarray(int* arr, int lBound, int mid, int rBound) {
		int lMax = mid;
		int lMaxSum = arr[mid];
		int sum = lMaxSum;
		for (int i = mid - 1; i >= lBound; i--) {
			sum += arr[i];
			if (sum > lMaxSum) {
				lMaxSum = sum;
				lMax = i;
			}
		}
		int rMax = mid + 1;
		int rMaxSum = arr[mid + 1];
		sum = rMaxSum;
		for (int i = mid + 2; i <= rBound; i++) {
			sum += arr[i];
			if (sum > rMaxSum) {
				rMaxSum = sum;
				rMax = i;
			}
		}
		return new MSARes(lMax, rMax, lMaxSum + rMaxSum);
	}

	MSARes* MaxSubarray(int* arr, int left, int right) {
		if(left == right)
			return new MSARes(left, right, arr[left]);
		int mid = (left + right) / 2;
		MSARes* lResult = MaxSubarray(arr, left, mid);
		MSARes* rResult = MaxSubarray(arr, mid + 1, right);
		MSARes* mResult = MaxCrossSubarray(arr, left, mid, right);
		if (lResult->sum > rResult->sum && lResult->sum > mResult->sum) {
			delete(rResult);
			delete(mResult);
			return lResult;
		}
		else if (rResult->sum > lResult->sum && rResult->sum > mResult->sum) {
			delete(lResult);
			delete(mResult);
			return rResult;
		}
		else {
			delete(lResult);
			delete(rResult);
			return mResult;
		}
	}
}


// 用法
//int arr[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
//Bur::MSARes* r = Bur::MaxSubarray(arr, 0, 15);
//7 10 43

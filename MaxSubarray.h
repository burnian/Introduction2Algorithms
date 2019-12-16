/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/30/2019, 00:26
*@Last Modify: 12/16/2019, 23:02
*@Desc: 分治递归求最大子数组
*********************************************************/
#pragma once
#include <iostream>


namespace Bur {
	struct MSARes
	{
		int left;
		int right;
		int sum;

		MSARes(int l, int r, int s) :left(l), right(r), sum(s) {};
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

	MSARes* MaxSubarrayDQ(int* arr, int left, int right) {
		if(left == right)
			return new MSARes(left, right, arr[left]);
		int mid = (left + right) / 2;
		MSARes* lRes = MaxSubarrayDQ(arr, left, mid);
		MSARes* rRes = MaxSubarrayDQ(arr, mid + 1, right);
		MSARes* mRes = MaxCrossSubarray(arr, left, mid, right);
		if (lRes->sum > rRes->sum &&
			lRes->sum > mRes->sum) {
			delete(rRes);
			delete(mRes);
			return lRes;
		}
		else if (rRes->sum > lRes->sum && rRes->sum > mRes->sum) {
			delete(lRes);
			delete(mRes);
			return rRes;
		}
		else {
			delete(lRes);
			delete(rRes);
			return mRes;
		}
	}

	// brute-force solution
	int MaxSubarrayBF(int n, int* a, int &besti, int &bestj)
	{
		int sum = -1;
		for (int i = 0; i < n; ++i) {
			int thissum = 0;
			for (int j = i; j < n; ++j) {
				thissum += a[j];
				if (thissum > sum) {
					sum = thissum;
					besti = i, bestj = j;
				}
			}
		}
		return sum;
	}
}


// 用法
//int arr[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
//Bur::MSARes* r = Bur::MaxSubarray(arr, 0, 15);
//7 10 43

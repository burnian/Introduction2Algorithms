/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/30/2019, 15:19
*@Last Modify: 10/01/2019, 18:15
*@Desc: ���㷨ּ��ѡ�������е�k�������������ʱ�临�Ӷ���T(n)=cn����ʱҪ�������ģ�ﵽn>120��ͨ���ݹ��ѡȡ��λ����
*       �õ���������λ������1/4������������1/4����С������ʣ�µ�һ����ܴ���Ҳ����С������
*       Ҳ����˵ÿ��partition����������Ҳ���ٿ����ӵ�30%�����ݡ�
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

	// �ݹ��ѡ����λ��
	int MedianSelect(int* arr, int l, int r, int elemStep) {
		int groupStep = elemStep * GROUP_LENGTH;
		int groupCnt = (r - l + elemStep) / groupStep;
		for (int i = 0; i < groupCnt; i++) {
			int start = l + i * groupStep;
			InsertSort(arr, start, start + groupStep, elemStep);
		}

		if (groupCnt <= 0)
			// �м������λ���±�
			return l + (r - l) / elemStep / 2 * elemStep; // ���ﲻ�ܻ�����Ϊ/����Ϊȡ�̣����������������ͻᵼ������������������
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


//int arr[] = { 3,7,4,5,6,5,6,2,3,4,1,5,4,2,3,5,6,8,7,4,5,6,7,9,8 }; median Ϊ 5
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
//			36,27,8,21 }; ����������1~55��������У�median Ϊ 28
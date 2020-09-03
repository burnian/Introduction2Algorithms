/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/29/2019, 12:36
*@Last Modify: 01/02/2020, 17:31
*@Desc: 桶排序
*********************************************************/
#pragma once
#include "LinkList.h"
#define N 10 // 宏定义不用放在namespace里


namespace Bur {
	//@param arr 待排序数组
	//@param len 待排序数组的长度
	//@param low 数据下界（数据可以等于下界）
	//@param up  数据上界（数据不能等于上界）
	void BucketSort(double* arr, int len, double low, double up) {
		Bur::LinkList<double>* buckets[N] = { nullptr };
		for (int i = 0; i < len; i++) {
			int idx = (arr[i] - low) / (up - low) * N;
			if (!buckets[idx]) {
				// 得到一个新桶
				buckets[idx] = new Bur::LinkList<double>();
			}
			Bur::LinkList<double>::Node* p = buckets[idx]->GetHead();
			// 链表插入排序
			while (p->next && arr[i] > *p->next->elem)
				p = p->next;
			buckets[idx]->Insert(p, new double(arr[i]));
		}

		for (int i = 0, j = 0; i < N; i++) {
			if (buckets[i]) {
				buckets[i]->Visit([&](Bur::LinkList<double>::Node* node) {
					arr[j++] = *node->elem;
				});
			}
		}
	}
}


// 用法
//double arr[] = { 515,968,454,418,595,777,787,798,880,555 };
//BucketSort(arr, 10, 100, 1000);

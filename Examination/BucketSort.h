/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/29/2019, 12:36
*@Last Modify: 01/02/2020, 17:31
*@Desc: Ͱ����
*********************************************************/
#pragma once
#include "LinkList.h"
#define N 10 // �궨�岻�÷���namespace��


namespace Bur {
	//@param arr ����������
	//@param len ����������ĳ���
	//@param low �����½磨���ݿ��Ե����½磩
	//@param up  �����Ͻ磨���ݲ��ܵ����Ͻ磩
	void BucketSort(double* arr, int len, double low, double up) {
		Bur::LinkList<double>* buckets[N] = { nullptr };
		for (int i = 0; i < len; i++) {
			int idx = (arr[i] - low) / (up - low) * N;
			if (!buckets[idx]) {
				// �õ�һ����Ͱ
				buckets[idx] = new Bur::LinkList<double>();
			}
			Bur::LinkList<double>::Node* p = buckets[idx]->GetHead();
			// �����������
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


// �÷�
//double arr[] = { 515,968,454,418,595,777,787,798,880,555 };
//BucketSort(arr, 10, 100, 1000);

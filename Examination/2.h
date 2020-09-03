/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 12/15/2019, 17:50
*@Last Modify: 12/15/2019, 17:50
*@Desc: ���ʵ��һ�������㷨��������������ʽ�洢�������������������һ���󶥶ѡ�
		������δ�ɶ�ʱ��ֻ�ܴ����һ����Ҷ�ڵ�һ��һ����ǰ�����������ܴӶ������µ���
*********************************************************/
#pragma once

void MaxHeap(int* arr, int size) {
	// ����Ԫ���±����1��ʼ�����Ե�Ҫ��ȡ�����е�����ʱ���һ
	int last = size / 2;
	int max = 0;
	int right, temp;
	while (last > 0) {
		max = 2 * last;
		right = 2 * last + 1;
		if (right <= size && arr[right - 1] > arr[max - 1]) {
			max = right;
		}
		if (arr[max - 1] > arr[last - 1]) {
			temp = arr[max - 1];
			arr[max - 1] = arr[last - 1];
			arr[last - 1] = temp;
		}
		last--;
	}
}
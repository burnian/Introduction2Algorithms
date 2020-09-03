/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 12/15/2019, 17:50
*@Last Modify: 12/15/2019, 17:50
*@Desc: 设计实现一个分治算法，将给定数组形式存储的无序输入数据整理成一个大顶堆。
		当数组未成堆时，只能从最后一个非叶节点一个一个往前调整，而不能从顶端向下调整
*********************************************************/
#pragma once

void MaxHeap(int* arr, int size) {
	// 以下元素下标均从1开始，所以当要获取数组中的数据时需减一
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
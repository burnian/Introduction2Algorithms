/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/30/2019, 17:36
*@Last Modify: 09/30/2019, 17:36
*@Desc: 插入排序，从小到大
*********************************************************/
#pragma once

namespace Bur {
	// 长度为len的数组全排序
	void InsertSort(int* arr, int len) {
		int temp, j;
		for (int i = 1; i < len; i++) {
			temp = arr[i];
			for (j = i - 1; j >= 0 && arr[j] > temp; j--) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}
	}

	// 把数组中l~r的一段数据排序
	void InsertSort(int* arr, int l, int r) {
		int temp, j;
		for (int i = l + 1; i <= r; i++) {
			temp = arr[i];
			for (j = i - 1; j >= l && arr[j] > temp; j--) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}
	}

	//@param l 待排序数据在数组中的起始下标
	//@param r 待排序数据在数组中的终止下标后一位
	void InsertSort(int* arr, int l, int r, int step) {
		int temp, j;
		for (int i = l + step; i < r; i += step) {
			temp = arr[i];
			for (j = i - step; j >= l && arr[j] > temp; j -= step) {
				arr[j + step] = arr[j];
			}
			arr[j + step] = temp;
		}
	}
}
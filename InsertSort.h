/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/30/2019, 17:36
*@Last Modify: 09/30/2019, 17:36
*@Desc: �������򣬴�С����
*********************************************************/
#pragma once

namespace Bur {
	// ����Ϊlen������ȫ����
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

	// ��������l~r��һ����������
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

	//@param l �����������������е���ʼ�±�
	//@param r �����������������е���ֹ�±��һλ
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
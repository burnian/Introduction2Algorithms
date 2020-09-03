/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/07/2019, 18:27
*@Last Modify: 12/15/2019, 21:23
*@Desc: 归并排序
*********************************************************/
#pragma once

namespace Bur {
	void Merge(int* a, int l, int m, int r)
	{
		int len = r - l + 1;
		int* temp = new int[len];

		for (int i = 0; i < len; i++)
			temp[i] = a[l + i];

		int i = 0;
		int mm = m - l;
		int j = mm + 1;
		int rr = r - l;
		while (i <= mm && j <= rr) {
			if (temp[i] > temp[j])
				a[l++] = temp[j++];
			else
				a[l++] = temp[i++];
		}

		while (i <= mm)
			a[l++] = temp[i++];
		while (j <= rr)
			a[l++] = temp[j++];

		delete[] temp;
	}

	void MergeSort(int* a, int l, int r)
	{
		if (l < r)
		{
			int m = (l + r) / 2;
			MergeSort(a, l, m);
			MergeSort(a, m + 1, r);
			Merge(a, l, m, r);
		}
	}
}

// test case:
//std::cout << "MergeSort 开始时间：" << clock() << std::endl;
//MergeSort(a, 0, LEN - 1);
//std::cout << "MergeSort 结束时间：" << clock() << std::endl;
//for (auto &v : a) {
//	std::cout << v << " ";
//}
//std::cout << std::endl;
//std::cout << std::endl;

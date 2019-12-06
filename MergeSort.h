/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/07/2019, 18:27
*@Last Modify: 11/12/2019, 22:42
*@Desc: πÈ≤¢≈≈–Ú
*********************************************************/
#pragma once

void Merge(int a[], int l, int m, int r)
{
	int lenL = m - l + 1;
	int lenR = r - m;
	int* L = new int[lenL];
	int* R = new int[lenR];
	for (int i = 0; i < lenL; i++) {
		L[i] = a[l + i];
	}
	for (int i = 0; i < lenR; i++) {
		R[i] = a[m + 1 + i];
	}
	int i = 0;
	int j = 0;
	int k = l;
	while (lenL > 0 && lenR > 0) {
		if (L[i] > R[j]) {
			a[k++] = R[j++];
			lenR--;
		}
		else
		{
			a[k++] = L[i++];
			lenL--;
		}
	}

	while (lenL-- > 0)
	{
		a[k++] = L[i++];
	}
	while (lenR-- > 0)
	{
		a[k++] = R[j++];
	}

	delete[] L;
	delete[] R;
}

void MergeSort(int a[], int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		MergeSort(a, l, m);
		MergeSort(a, m + 1, r);
		Merge(a, l, m, r);
	}
}

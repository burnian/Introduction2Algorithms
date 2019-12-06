/*
排序初级版
*/
#include<iostream>
using namespace std;


int partition(int arr[], const int start, const int end)
{
	int pivotvalue = arr[start];
	int l = start + 1, h = end;
	bool done = false;
	while (!done)
	{
		while (l <= h && arr[l] <= pivotvalue)l += 1;
		while (h >= l && arr[h] >= pivotvalue)h -= 1;
		if (h < l)done = true;
		else {
			int temp = arr[l];
			arr[l] = arr[h];
			arr[h] = temp;
		}
	}	
	int temp = arr[h];
	arr[h] = arr[start];
	arr[start] = temp;
	return h;
}

void qsort(int arr[], const int start, const int end)
{
	int ll = partition(arr, start, end);
	if (start >= end)return;
	ll = partition(arr, start, end);
	qsort(arr, start, ll - 1);
	qsort(arr, ll + 1, end);
}

int main()
{
	int a[]{ 49,38,27,97,76,13,27,49 };
	/*冒泡排序（错误有边界设置不合理，外部循环n-1,内部也循环n-1)
	for (int i = 7; i >0; i--)
	{
		for (int j = 0; j<i; j++)
		{
			if ( a[j]> a[j + 1]  )
			{
				int temp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = temp;
			}
		}
	}
	
	*/
	/*选择排序
	for (int i = 0; i <7; i++)
	{
		int min = a[i]; int index;
		for (int j = i + 1; j <= 7; j++)
		{
			if (a[j] < min)
			{
				min = a[j];
				index = j;
			}
		}
		int temp = a[i];
		a[i] = min;
		a[index] = temp;

	}
	for (auto t : a)
		cout << t << endl;
	cout << '\n';
	*/
	qsort(a, 0, 7);
	for (auto k : a)
		cout << k << '\t';
	cout << '\n';
	
	system("pause");
	return 0;
}
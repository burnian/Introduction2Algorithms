/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/17/2019, 19:52
*@Last Modify: 09/27/2019, 10:51
*@Desc: �ݹ�ʵ�ֶ�����
*********************************************************/
#include "Heap.h"

Heap::Heap(std::vector<int> &p, bool b)
	:bTree(p), isMaxHeap(b)
{
	Heapify();
}


Heap::~Heap()
{
	bTree.clear();
}

// ������key Ϊ���ڵ��һ�Ŷ�����
void Heap::AdjustDown(int key) {
	if (key <= bTree.size()) {
		if (isMaxHeap)
			MaxAdjust(key);
		else
			MinAdjust(key);
	}
}

// �������������ѳɶѺ󣬲��ϰ�key �ڵ����ϵ���
void Heap::AdjustUp(int key) {
	if (key <= bTree.size()) {
		for (int i = key / 2; i >= 1; key = i, i /= 2) {
			if ((isMaxHeap && bTree[key - 1] > bTree[i - 1]) || (!isMaxHeap && bTree[key - 1] < bTree[i - 1]))
				std::swap(bTree[key - 1], bTree[i - 1]);
			else
				break;
		}
	}
}

void Heap::Heapify() {
	for (int i = bTree.size() / 2; i >= 1; i--) {
		AdjustDown(i);
	}
}

int Heap::GetHeapTop() {
	if (bTree.size() > 0)
		return bTree[0];
}

void Heap::Insert(int node) {
	bTree.push_back(node);
	int key = bTree.size();
	while ((key /= 2) >= 1) {
		AdjustDown(key);
	}
}

void Heap::ModifyNode(int key, int val) {
	int oldVal = bTree[key - 1];
	bTree[key - 1] = val;
	if ((isMaxHeap && val > oldVal) || (!isMaxHeap && val < oldVal))
		AdjustUp(key);
	else
		AdjustDown(key);
}

int Heap::ExtractHeapTop() {
	if (bTree.size() > 0) {
		int ret = bTree[0];
		bTree[0] = bTree.back();
		bTree.pop_back();
		AdjustDown(1);
		return ret;
	}
}

// �ݹ齨���󶥶�key vector�±��1��ʼ
void Heap::MaxAdjust(int key) {
	int len = bTree.size();
	int left = 2 * key;
	int right = 2 * key + 1;
	int max = 0;
	if (left <= len) {
		max = left;
	}
	if (right <= len) {
		if (bTree[right - 1] > bTree[max - 1])
			max = right;
	}
	// �ϲ�
	if (max > 0 && bTree[max - 1] > bTree[key - 1]) {
		std::swap(bTree[max - 1], bTree[key - 1]);
		MaxAdjust(max);
	}
}

// �ݹ齨��С����key vector�±��1��ʼ
void Heap::MinAdjust(int key) {
	int len = bTree.size();
	int left = 2 * key;
	int right = 2 * key + 1;
	int min = 0;
	if (left <= len) {
		min = left;
	}
	if (right <= len) {
		if (bTree[right - 1] < bTree[min - 1])
			min = right;
	}
	// �ϲ�
	if (min > 0 && bTree[min - 1] < bTree[key - 1]) {
		std::swap(bTree[min - 1], bTree[key - 1]);
		MinAdjust(min);
	}
}

void Heap::Print() {
	int len = bTree.size();
	int margin = len / 2;
	for (int i = 1; i <= len; i *= 2) {
		for (int k = margin; k > 0; k--) {
			std::cout << " ";
		}
		for (int j = i; j < 2 * i && j <= len; j++) {
			std::cout << bTree[j - 1] << " ";
		}
		margin -= 1;
		std::cout << std::endl;
	}
}


/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/17/2019, 19:51
*@Last Modify: 08/29/2020, 12:23
*@Desc: ...
*********************************************************/
#pragma once
#include <iostream>
#include <vector>


class Heap
{
public:
	Heap(std::vector<int> &bTree, bool isMaxHeap);
	~Heap();

	// ����������heapify �ϲ�����Ϊ������������������ã��ϲ�֮���Ȼ��Ҫ���ڲ��������жϣ�Ӱ��Ч��
	void MaxAdjust(int key);
	void MinAdjust(int key);
	void Heapify();
	void Insert(int node);
	// ���ضѶ��ڵ�����
	int GetHeapTop();
	// ���ضѶ��ڵ�������ɾ���ýڵ�
	int ExtractHeapTop();
	// �޸�ĳ�ڵ��С
	void ModifyNode(int key, int val);
	void Print();
	inline void AdjustUp(int key);
	inline void AdjustDown(int key);

public:
	bool isMaxHeap;
	std::vector<int> bTree;
};


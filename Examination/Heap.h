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

	// 不把这两个heapify 合并是因为这两个函数会大量调用，合并之后必然需要在内部做不少判断，影响效率
	void MaxAdjust(int key);
	void MinAdjust(int key);
	void Heapify();
	void Insert(int node);
	// 返回堆顶节点数据
	int GetHeapTop();
	// 返回堆顶节点数据且删除该节点
	int ExtractHeapTop();
	// 修改某节点大小
	void ModifyNode(int key, int val);
	void Print();
	inline void AdjustUp(int key);
	inline void AdjustDown(int key);

public:
	bool isMaxHeap;
	std::vector<int> bTree;
};


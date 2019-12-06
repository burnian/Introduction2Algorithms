/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/17/2019, 07:34
*@Last Modify: 12/01/2019, 21:58
*@Desc: 多个活动共享一个场地，求开展活动数最多的分配方案，该算法需要对数据进行预处理，根据活动的结束时间升序排列。
*********************************************************/
#pragma once
#include <vector>

namespace Bur {
	class Activity
	{
	public:
		Activity(size_t _1, float _2, float _3) :id(_1), start(_2), finish(_3) {}
	public:
		size_t id;
		float start;
		float finish;
	};

	void ActivitySelection(Activity** arr, int n, std::vector<Activity*>& ret) {
		Activity* cur = arr[0];
		ret.push_back(cur);
		for (int i = 1; i < n; i++) {
			if (arr[i]->start >= cur->finish) {
				ret.push_back(arr[i]);
				cur = arr[i];
			}
		}
	}
}

//// test case:
//Bur::Activity* arr[] = {
//	new Bur::Activity(1,1,4),
//	new Bur::Activity(2,3,5),
//	new Bur::Activity(3,0,6),
//	new Bur::Activity(4,5,7),
//	new Bur::Activity(5,3,8),
//	new Bur::Activity(6,5,9),
//	new Bur::Activity(7,6,10),
//	new Bur::Activity(8,8,11),
//	new Bur::Activity(9,8,12),
//	new Bur::Activity(10,2,13),
//	new Bur::Activity(11,12,14),
//};
//
//std::vector<Bur::Activity*> ret;
//Bur::ActivitySelection(arr, 11, ret);
//
//for (auto v : ret) {
//	std::cout << v->id << " ";
//}
//std::cout << std::endl;
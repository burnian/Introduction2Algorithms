/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 12/31/2019, 14:55
*@Last Modify: 12/31/2019, 14:55
*@Desc: 求某集合中和为某定值的各子集
*********************************************************/
#pragma once
#include <vector>

#define NUM 4

namespace Bur {
	int state[NUM] = { 0 };
	int val[NUM] = { 5,10,15,20 }; // val升序排列
	int target = 25;

	// 递归回溯求解，从状态空间树的角度考虑
	//@selSum 已选中元素和
	//@k 当前处理元素下标
	//@restSum 剩余未处理元素和
	//@target 目标值
	void SubsetSumResBT(int selSum, int k, int restSum) {
		// 左子树，纳入val[k]
		state[k] = 1;
		if (selSum + val[k] == target) {
			for (int i = 0; i <= k; i++) {
				std::cout << state[i] << " ";
			}
			std::cout << std::endl;
		}
		// 纳入val[k]后与剩余元素的最小值相加，若和>target，则说明纳入val[k]会导致无解，所以走剔除val[k]的分支
		else if (selSum + val[k] + val[k + 1] <= target)
			SubsetSumResBT(selSum + val[k], k + 1, restSum - val[k]);
		// 右子树，剔除val[k]。只有同时满足下面条件才有解。
		// 1.剩余元素和>=target; 2.纳入剩余元素中的最小值<=target。
		if (selSum + restSum - val[k] >= target && selSum + val[k + 1] <= target) {
			state[k] = 0;
			SubsetSumResBT(selSum, k + 1, restSum - val[k]);
		}
	}
}

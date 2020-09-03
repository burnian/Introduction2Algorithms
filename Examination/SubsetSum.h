/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 12/31/2019, 14:55
*@Last Modify: 12/31/2019, 14:55
*@Desc: ��ĳ�����к�Ϊĳ��ֵ�ĸ��Ӽ�
*********************************************************/
#pragma once
#include <vector>

#define NUM 4

namespace Bur {
	int state[NUM] = { 0 };
	int val[NUM] = { 5,10,15,20 }; // val��������
	int target = 25;

	// �ݹ������⣬��״̬�ռ����ĽǶȿ���
	//@selSum ��ѡ��Ԫ�غ�
	//@k ��ǰ����Ԫ���±�
	//@restSum ʣ��δ����Ԫ�غ�
	//@target Ŀ��ֵ
	void SubsetSumResBT(int selSum, int k, int restSum) {
		// ������������val[k]
		state[k] = 1;
		if (selSum + val[k] == target) {
			for (int i = 0; i <= k; i++) {
				std::cout << state[i] << " ";
			}
			std::cout << std::endl;
		}
		// ����val[k]����ʣ��Ԫ�ص���Сֵ��ӣ�����>target����˵������val[k]�ᵼ���޽⣬�������޳�val[k]�ķ�֧
		else if (selSum + val[k] + val[k + 1] <= target)
			SubsetSumResBT(selSum + val[k], k + 1, restSum - val[k]);
		// ���������޳�val[k]��ֻ��ͬʱ���������������н⡣
		// 1.ʣ��Ԫ�غ�>=target; 2.����ʣ��Ԫ���е���Сֵ<=target��
		if (selSum + restSum - val[k] >= target && selSum + val[k + 1] <= target) {
			state[k] = 0;
			SubsetSumResBT(selSum, k + 1, restSum - val[k]);
		}
	}
}

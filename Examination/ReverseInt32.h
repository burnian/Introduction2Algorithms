/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 01/01/2020, 16:37
*@Last Modify: 01/01/2020, 16:51
*@Desc: ������ת������123->321��-135->-531��Խ����������0
*********************************************************/
#pragma once

//#define MIN 0x80000000 ������ʾ���޷����������Ǹ���
//#define MAX 0x7fffffff

namespace Bur {
	int reverse(int x) {
		int ret = 0;
		while (x != 0) {
			int pop = x % 10;// ��׷�ӣ�ret �� INT_MAX �� INT_MIN ��һλ��ʱ��һ������Խ��
			// INT_MAX=2^31 - 1=2^16 * 2^8 * 2^4 * 2^2 * 2 - 1 =>��λ=6*6*6*4*2 - 1 = 7
			if (ret > INT_MAX / 10 || (ret == INT_MAX / 10 && pop > 7))
				return 0;
			// -INT_MIN=2^31=2^16 * 2^8 * 2^4 * 2^2 * 2=>��λ=6*6*6*4*2 = 8
			if (ret < INT_MIN / 10 || (ret == INT_MIN / 10 && pop < -8))
				return 0;
			ret = ret * 10 + pop;
			x /= 10;
		}
		return ret;
	}
}
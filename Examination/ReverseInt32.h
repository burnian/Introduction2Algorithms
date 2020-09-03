/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 01/01/2020, 16:37
*@Last Modify: 01/01/2020, 16:51
*@Desc: 整数翻转，例：123->321，-135->-531，越界整数返回0
*********************************************************/
#pragma once

//#define MIN 0x80000000 这里会表示成无符号整数而非负数
//#define MAX 0x7fffffff

namespace Bur {
	int reverse(int x) {
		int ret = 0;
		while (x != 0) {
			int pop = x % 10;// 待追加，ret 比 INT_MAX 和 INT_MIN 少一位的时候一定不会越界
			// INT_MAX=2^31 - 1=2^16 * 2^8 * 2^4 * 2^2 * 2 - 1 =>个位=6*6*6*4*2 - 1 = 7
			if (ret > INT_MAX / 10 || (ret == INT_MAX / 10 && pop > 7))
				return 0;
			// -INT_MIN=2^31=2^16 * 2^8 * 2^4 * 2^2 * 2=>个位=6*6*6*4*2 = 8
			if (ret < INT_MIN / 10 || (ret == INT_MIN / 10 && pop < -8))
				return 0;
			ret = ret * 10 + pop;
			x /= 10;
		}
		return ret;
	}
}
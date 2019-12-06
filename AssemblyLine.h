/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 10/14/2019, 17:46
*@Last Modify: 10/16/2019, 15:57
*@Desc: 双装配线最快调度算法，输入两组装配线所有站的装配和切换时间，输出最快装配安排。
*********************************************************/
#pragma once
#define MAX 10

namespace Bur {
	template<int len>
	float AssemblyLine(float(*station)[len], float(*transfer)[len + 1], int* rest) {
		float minTime[2][MAX] = { {0}, {0} };
		int minSrc[2][MAX] = { {0}, {0} };
		float temp1, temp2, temp3;
		minTime[0][0] = transfer[0][0] + station[0][0];
		minTime[1][0] = transfer[1][0] + station[1][0];
		for (int j = 1; j < len; j++) {
			temp1 = minTime[0][j - 1];
			temp2 = minTime[1][j - 1] + transfer[1][j];
			if (temp1 < temp2) {
				minSrc[0][j] = 0;
				minTime[0][j] = temp1 + station[0][j];
			}
			else {
				minSrc[0][j] = 1;
				minTime[0][j] = temp2 + station[0][j];
			}
			temp1 = minTime[0][j - 1] + transfer[0][j];
			temp2 = minTime[1][j - 1];
			if (temp1 < temp2) {
				minSrc[1][j] = 0;
				minTime[1][j] = temp1 + station[1][j];
			}
			else {
				minSrc[1][j] = 1;
				minTime[1][j] = temp2 + station[1][j];
			}
		}
		temp1 = minTime[0][len - 1] + transfer[0][len];
		temp2 = minTime[1][len - 1] + transfer[1][len];
		if (temp1 < temp2) {
			temp3 = temp1;
			rest[len - 1] = 0;
		}
		else {
			temp3 = temp2;
			rest[len - 1] = 1;
		}
		for (int i = len - 1; i > 0; i--) {
			rest[i - 1] = minSrc[rest[i]][i];
		}
		return temp3;
	}
}

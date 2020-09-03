/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 08/29/2020, 15:27
*@Last Modify: 08/30/2020, 21:06
*@Desc: 岛屿数量
*********************************************************/
#pragma once
#include <vector>
#include <unordered_set>
#include "UnionFindSet.h"


namespace Bur {
	////////////////////////////////////////////////////////////
	// 解法一：并查集
	////////////////////////////////////////////////////////////
	const int DIR[2][2] = { {0,1}, {1,0} };

	int numIslands1(std::vector<std::vector<char>>& grid) {
		int m = grid.size(); // row
		if (m <= 0) return 0;
		int n = grid[0].size(); // col
		UnionFindSet ufSet(m * n);
		std::unordered_set<int> landMark; // 岛屿地标
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (grid[i][j] == '1') {
					int idx = i * n + j;
					// 连接陆地
					for (int k = 0; k < 2; k++) {
						int temp1 = i + DIR[k][0];
						int temp2 = j + DIR[k][1];
						if (temp1 < m && temp2 < n && grid[temp1][temp2] == '1') {
							int idxNext = temp1 * n + temp2;
							// 若被连接区域已有地标（曾被连过），则消除连接区域和被连接区域地标
							if (landMark.find(ufSet.Find(idxNext)) != landMark.end()) {
								landMark.erase(ufSet.Find(idx));
								landMark.erase(ufSet.Find(idxNext));
							}
							ufSet.Unite(idx, idxNext);
						}
					}
					// 判断是否新地标
					if (landMark.find(ufSet.Find(idx)) == landMark.end()) {
						landMark.insert(ufSet.Find(idx));
					}
				}
			}
		}
		return landMark.size();
	}

	////////////////////////////////////////////////////////////
	// 解法二：深度优先遍历
	////////////////////////////////////////////////////////////
	void DFS(std::vector<std::vector<char>>& grid, int r, int c) {
		grid[r][c] = '0';
		if (r - 1 >= 0 && grid[r - 1][c] == '1') DFS(grid, r - 1, c);
		if (r + 1 < grid.size() && grid[r + 1][c] == '1') DFS(grid, r + 1, c);
		if (c - 1 >= 0 && grid[r][c - 1] == '1') DFS(grid, r, c - 1);
		if (c + 1 < grid[0].size() && grid[r][c + 1] == '1') DFS(grid, r, c + 1);
	}

	int numIslands2(std::vector<std::vector<char>>& grid) {
		int nr = grid.size();
		if (!nr) return 0;
		int nc = grid[0].size();

		int num_islands = 0;
		for (int r = 0; r < nr; ++r) {
			for (int c = 0; c < nc; ++c) {
				if (grid[r][c] == '1') {
					++num_islands;
					DFS(grid, r, c);
				}
			}
		}

		return num_islands;
	}
}


///////////////////////////////
//for test
//
//vector<vector<char>> grid = {
//	//{'1','1','1','1','0'},
//	//{'1','1','0','1','0'},
//	//{'1','1','0','0','0'},
//	//{'0','0','0','0','0'},
//	//{'1','1','0','0','0'},
//	//{'1','1','0','0','0'},
//	//{'0','0','1','0','0'},
//	//{'0','0','0','1','1'},
//	{'1','1','1'},
//	{'0','1','0'},
//	{'1','1','1'},
//	//{'1','0','1','1','1'},
//	//{'1','0','1','0','1'},
//	//{'1','1','1','0','1'},
//};
//
//Bur::numIslands1(grid);

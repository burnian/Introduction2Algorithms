/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 08/29/2020, 11:10
*@Last Modify: 08/30/2020, 16:18
*@Desc: 并查集
*********************************************************/
#pragma once


namespace Bur {
	class UnionFindSet {
	public:
		UnionFindSet(size_t n) {
			// 记录每个元素的parent节点 先将它们的父节点设为自己
			parents = new size_t[n];
			// 记录节点的rank值
			ranks = new size_t[n]{ 0 };
			for (size_t i = 0; i < n; i++) {
				parents[i] = i;
			}
		};

		// 寻找根节点
		size_t Find(size_t x) {
			if (x != parents[x]) {
				parents[x] = Find(parents[x]);
			}
			return parents[x];
		};

		void Unite(size_t x, size_t y) {
			size_t rootX = Find(x);
			size_t rootY = Find(y);
			if (rootX == rootY) return;
			if (ranks[rootX] > ranks[rootY])
				parents[rootY] = rootX;
			else if (ranks[rootX] < ranks[rootY])
				parents[rootX] = rootY;
			else {
				parents[rootY] = rootX;
				ranks[rootX]++;
			}
		};

		~UnionFindSet() {
			delete[] parents;
			delete[] ranks;
		};

	private:
		size_t* parents; // 存的不是根，而是父或父父节点
		size_t* ranks;
	};
}
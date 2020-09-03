int minOf4(int i1, int i2, int i3, int i4) {
	int ret1 = i1 < i2 ? i1 : i2;
	int ret2 = i3 < i4 ? i3 : i4;
	return ret1 < ret2 ? ret1 : ret2;
}

class ALSection {
public:
	ALSection(int _1, int _2) :start(_1), end(_2) {};
	// 把merge方法写在class里面的好处就在于返回值可以继续调用merge方法
	ALSection* MergeRight(Station*** s, ALSection* secR) {
		int temp1 = minOf4(
			min00 + secR->min00,
			min00 + s[1][secR->start]->switchCost + secR->min10,
			min01 + s[0][secR->start]->switchCost + secR->min00,
			min01 + secR->min10
		);
		int temp2 = minOf4(
			min00 + secR->min01,
			min00 + s[1][secR->start]->switchCost + secR->min11,
			min01 + s[0][secR->start]->switchCost + secR->min01,
			min01 + secR->min11
		);
		int temp3 = minOf4(
			min10 + secR->min00,
			min10 + s[1][secR->start]->switchCost + secR->min10,
			min11 + s[0][secR->start]->switchCost + secR->min00,
			min11 + secR->min10
		);
		int temp4 = minOf4(
			min10 + secR->min01,
			min10 + s[1][secR->start]->switchCost + secR->min11,
			min11 + s[0][secR->start]->switchCost + secR->min01,
			min11 + secR->min11
		);
		min00 = temp1;
		min01 = temp2;
		min10 = temp3;
		min11 = temp4;
		end = secR->end;
		return this;
	}

	void Print() {
		std::cout << start << "->" << end << ": (minLTRT: " << min00 << ", minLTRB: " <<
			min01 << ", minLBRT: " << min10 << ", minLBRB: " << min11 << std::endl;
	}
public:
	int start, end;
	int min00; // left-top to right-top
	int min01; // left-top to right-bottom
	int min10; // left-bottom to right-top
	int min11; // left-bottom to right-bottom
};

// DC算法没有给出最短路径
// 执行完后会多出一个ALSection 对象，需要在外部delete
ALSection* ALS_DC(Station*** s, int l, int r) {
	if (l == r) {
		ALSection* ret = new ALSection(l, r);
		ret->min00 = s[0][l]->runCost;
		ret->min01 = s[0][l]->runCost + s[1][r]->runCost;
		ret->min10 = s[1][l]->runCost + s[0][r]->runCost;
		ret->min11 = s[1][l]->runCost;
		ret->Print();
		return ret;
	}
	int m = (l + r) / 2;
	ALSection* secL = ALS_DC(s, l, m);
	ALSection* secR = ALS_DC(s, m + 1, r);
	secL->MergeRight(s, secR);
	delete secR;
	secL->Print();
	return secL;
}

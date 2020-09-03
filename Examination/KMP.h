#pragma once
#include<string.h>


void get_next(char T[], int next[]) {
	next[0] = -1;
	// 指向模式串中的每一个元素
	int i = 0;
	// 串中某个元素对应的next值
	int j = -1;
	int length = strlen(T);
	while (i < length)
	{
		if (j == -1 || T[i] == T[j]) {
			next[++i] = ++j;
		}
		else {
			j = next[j];
		}
	}
}

// 复杂度为o(m+n)的字符串模式匹配算法
int KMP(char S[], char T[], int pos) {
	int lenS = strlen(S);
	int lenT = strlen(T);
	int* next = new int[lenT + 1];
	get_next(T, next);
	int i = pos;
	int j = 0;
	while (i < lenS && j < lenT) {
		if (j == -1 || S[i] == T[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	delete next;
	if (j >= lenT) {
		return i - lenT;
	}
	return -1;
}
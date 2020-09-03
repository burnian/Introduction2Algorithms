#pragma once
#include<string.h>


void get_next(char T[], int next[]) {
	next[0] = -1;
	// ָ��ģʽ���е�ÿһ��Ԫ��
	int i = 0;
	// ����ĳ��Ԫ�ض�Ӧ��nextֵ
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

// ���Ӷ�Ϊo(m+n)���ַ���ģʽƥ���㷨
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
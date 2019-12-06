/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 07/11/2018, 09:19
*@Last Modify: 09/30/2019, 09:19
*@Desc: ��׺���ʽ��ֵ
*********************************************************/
#pragma once
#include<stdio.h>
#include<math.h>
#include"Stack.h"

#define MAX_LEVEL 4

namespace Bur {
	// �Ϸ�������ַ�������
	char LegalOperator[MAX_LEVEL][5] = { "()", "+-", "*/%", "^" };


	// �ַ��Ƿ�Ϊ�����ַ�
	bool Is_Number(char c) {
		return c >= 48 && c <= 57;
	}

	int ToNumber(char c) {
		return c - 48;
	}

	// ��ȡ����������ȼ����Ƿ���������ȼ�С��0,
	int Get_Char_Priority(char c) {
		if (c == '\0') return -1;
		for (size_t i = 0; i < MAX_LEVEL; i++) {
			for (char* p = LegalOperator[i]; *p != '\0'; p++) {
				if (*p == c) return i;
			}
		}
		return -1;
	}

	// ���������ַ��Ľ��
	void Calculate(SqStack<int>* varStack, SqStack<char>* oprStack) {
		char opr = Pop(oprStack);
		int var2 = Pop(varStack);
		int var1 = Pop(varStack);
		int temp = 0;
		switch (opr)
		{
		case'+':temp = var1 + var2; break;
		case'-':temp = var1 - var2; break;
		case'*':temp = var1 * var2; break;
		case'/':temp = var1 / var2; break;
		case'%':temp = var1 % var2; break;
		case'^':temp = pow(var1, var2); break;
		default:
			break;
		}
		Push(varStack, temp);
	}


	//char exp[100] = "40+ (10+(40 + 20)/6)^(2*3) - 40";
	char* Middle_Expression(char exp[]) {
		char *p = exp;

		SqStack<int>* varStack = Create_SqStack<int>();
		SqStack<char>* oprStack = Create_SqStack<char>();
		bool isSeqNum = false;
		while (*p != '\0')
		{
			char c = *p;
			if (Is_Number(c))
			{
				int num = c - 48;
				if (isSeqNum) {
					num += Pop(varStack) * 10;
				}
				Push(varStack, num);
				isSeqNum = true;
			}
			else
			{
				int prior = Get_Char_Priority(c);
				if (prior >= 0) {
					isSeqNum = false;
					if (c == ')') {
						while (*(oprStack->top - 1) != '(') {
							Calculate(varStack, oprStack);
						}
						Pop(oprStack);
					}
					else {
						if (c != '(') {
							// ��ǰ���������������ȼ�����ջ�����������ջ�����򽫴���������������ȼ���ջ��ÿһ����������бȽ�
							while (!Is_Stack_Empty(oprStack) && prior <= Get_Char_Priority(*(oprStack->top - 1)))
								Calculate(varStack, oprStack);
						}
						Push(oprStack, c);
					}
				}
			}
			p++;
		}

		while (!Is_Stack_Empty(oprStack))
			Calculate(varStack, oprStack);

		char* buffer = new char[20];
		int a = Pop(varStack);
		_itoa_s(a, buffer, 20, 10);
		return buffer;
	}
}

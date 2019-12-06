/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 07/11/2018, 09:19
*@Last Modify: 09/30/2019, 09:19
*@Desc: 中缀表达式求值
*********************************************************/
#pragma once
#include<stdio.h>
#include<math.h>
#include"Stack.h"

#define MAX_LEVEL 4

namespace Bur {
	// 合法运算符字符串常量
	char LegalOperator[MAX_LEVEL][5] = { "()", "+-", "*/%", "^" };


	// 字符是否为数字字符
	bool Is_Number(char c) {
		return c >= 48 && c <= 57;
	}

	int ToNumber(char c) {
		return c - 48;
	}

	// 获取运算符的优先级，非法运算符优先级小于0,
	int Get_Char_Priority(char c) {
		if (c == '\0') return -1;
		for (size_t i = 0; i < MAX_LEVEL; i++) {
			for (char* p = LegalOperator[i]; *p != '\0'; p++) {
				if (*p == c) return i;
			}
		}
		return -1;
	}

	// 计算两个字符的结果
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
							// 当前待处理的运算符优先级高于栈顶运算符则入栈，否则将待处理运算符的优先级与栈内每一个运算符进行比较
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

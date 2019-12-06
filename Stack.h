#pragma once
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 50


// T只可能为系统类型或者自定义类型的指针
template<typename T>
struct SqStack
{
	T* base;
	T* top;
	size_t size;
};

// 顺序栈
template<typename T>
SqStack<T>* Create_SqStack() {
	SqStack<T>* stack = new SqStack<T>();
	stack->base = (T*)malloc(STACK_INIT_SIZE * sizeof(T));
	if (!stack->base) exit(1);
	stack->top = stack->base;
	stack->size = STACK_INIT_SIZE;
	return stack;
}

// 入栈
template<typename T>
void Push(SqStack<T>* stack, T elem) {
	int length = stack->top - stack->base;
	if (length >= stack->size) {
		size_t newSize = stack->size + STACK_INCREMENT;
		stack->base = (T*)realloc(stack->base, newSize * sizeof(T));
		if (!stack->base) exit(1);
		stack->top = stack->base + length;
		stack->size = newSize;
	}
	*stack->top++ = elem;
}

// 出栈
template<typename T>
T Pop(SqStack<T>* stack) {
	if (stack->top <= stack->base) {
		return NULL;
	}
	return *(--stack->top);
}

// 判空
template<typename T>
bool Is_Stack_Empty(SqStack<T>* stack) {
	return stack->base >= stack->top;
}

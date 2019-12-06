/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/27/2019, 10:48
*@Last Modify: 09/27/2019, 10:48
*@Desc: 类似vector的顺序表
*********************************************************/
#pragma once
#include<stdlib.h>

#define LIST_INIT_SIZE 10
#define LIST_INCREMENT 10


// 因为SLElemType都是系统类型，所以无需重载赋值操作
struct SLElemType {
	int id;
	const char* name;
};

// 顺序表表头
struct SqList {
	SLElemType* elem;
	int length;
	int size;
};

// 创建顺序表
SqList* Create_SqList() {
	SqList* list = new SqList();
	if (!list) exit(1);
	list->elem = (SLElemType*)malloc(LIST_INIT_SIZE * sizeof(SLElemType));
	if (!list->elem) exit(1);
	list->length = 0;
	list->size = LIST_INIT_SIZE;
	return list;
}

// 插入，插入位置从0到length
int Insert_SqList(SqList* list, int pos, SLElemType* elem) {
	if (pos<0 || pos>list->length) {
		return 1;
	}
	if (list->length >= list->size) {
		int newSize = list->size + LIST_INCREMENT;
		list->elem = (SLElemType*)realloc(list->elem, newSize * sizeof(SLElemType));
		if (!list->elem) exit(1);
		list->size = newSize;
	}
	for (int i = list->length; i > pos; --i) {
		list->elem[i] = list->elem[i - 1];
	}
	list->elem[pos] = *elem;
	++list->length;

	return 0;
}

// 删除
int Delete_SqList(SqList* list, int pos) {
	if (pos<0 || pos>list->length - 1) {
		return 1;
	}
	for (int i = pos + 1; i <= list->length - 1; ++i) {
		list->elem[i - 1] = list->elem[i];
	}
	--list->length;

	return 0;
}
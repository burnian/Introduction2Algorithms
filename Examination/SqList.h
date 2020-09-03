/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 09/27/2019, 10:48
*@Last Modify: 09/27/2019, 10:48
*@Desc: ����vector��˳���
*********************************************************/
#pragma once
#include<stdlib.h>

#define LIST_INIT_SIZE 10
#define LIST_INCREMENT 10


// ��ΪSLElemType����ϵͳ���ͣ������������ظ�ֵ����
struct SLElemType {
	int id;
	const char* name;
};

// ˳����ͷ
struct SqList {
	SLElemType* elem;
	int length;
	int size;
};

// ����˳���
SqList* Create_SqList() {
	SqList* list = new SqList();
	if (!list) exit(1);
	list->elem = (SLElemType*)malloc(LIST_INIT_SIZE * sizeof(SLElemType));
	if (!list->elem) exit(1);
	list->length = 0;
	list->size = LIST_INIT_SIZE;
	return list;
}

// ���룬����λ�ô�0��length
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

// ɾ��
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
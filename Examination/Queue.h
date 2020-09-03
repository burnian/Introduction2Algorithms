#pragma once
#define QUEUE_INIT_SIZE 100
#define QUEUE_INCREMENT 50

// Tֻ����Ϊϵͳ���ͻ����Զ������͵�ָ��
template<typename T>
struct SqQueue
{
	T* base;
	size_t front;
	size_t rear;
	size_t size;
};


// ��������
template<typename T>
SqQueue<T>* Create_SqQueue() {
	SqQueue<T>* queue = new SqQueue<T>();
	queue->base = (T*)malloc(QUEUE_INIT_SIZE * sizeof(T));
	queue->front = queue->rear = 0;
	queue->size = QUEUE_INIT_SIZE;
	return queue;
}

// ���
template<typename T>
void EnQueue(SqQueue<T>* queue, T elem) {
	if (Is_Queue_Full(queue)) {
		size_t newSize = queue->size + QUEUE_INCREMENT;
		queue->base = (T*)realloc(queue->base, newSize * sizeof(T));
		if (!queue->base) exit(1);
		if (queue->rear < queue->front) {
			for (size_t i = queue->size - 1; i >= queue->front; i--) {
				queue->base[i + QUEUE_INCREMENT] = queue->base[i];
			}
			queue->front += QUEUE_INCREMENT;
		}
		queue->size = newSize;
	}
	queue->base[queue->rear] = elem;
	queue->rear = (queue->rear + 1) % queue->size;
}

// ����
template<typename T>
T  DeQueue(SqQueue<T>* queue) {
	if (Is_Queue_Empty(queue)) return NULL;
	T r = queue->base[queue->front];
	queue->front = (queue->front + 1) % queue->size;
	return r;
}

// �п�
template<typename T>
bool Is_Queue_Empty(SqQueue<T>* queue) {
	return queue->front == queue->rear;
}

// ����
template<typename T>
bool Is_Queue_Full(SqQueue<T>* queue) {
	return queue->front == (queue->rear + 1) % queue->size;
}
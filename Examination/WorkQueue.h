#pragma once
#include <functional>

typedef std::function<void()> NextFunc;
typedef std::function<void(NextFunc)> WorkQueueFunc;

// ִ�ж������ȵ�����
struct WorkQueueNode
{
	int priority;
	WorkQueueFunc pFunc;
	WorkQueueNode* next;
};

class WorkQueueList
{
public:
	WorkQueueList();
	~WorkQueueList();

	// ���ò������򣬰����ȼ�ֵ��С��������
	WorkQueueList* insert(WorkQueueNode* pNode);
	// �ӱ�ͷ����һ���ڵ�
	WorkQueueNode* shift();
	// ����
	unsigned long getLen();
public:
	WorkQueueNode* _pHead;
	unsigned long _len;
};


// ִ�ж���
class WorkQueue
{
public:
	WorkQueue();
	~WorkQueue();

	static WorkQueue* getInstance();

	// ����¼�
	void addWork(int priority, WorkQueueFunc pFunc);
	// ����֡����
	void setFrameFunc(std::function<void(std::function<void()>)> func);
	// �Ƴ�֡����
	void removeFrameFunc();
private:
	// ִ����һ���¼�
	void next();


private:
	static WorkQueue* _instance;
	// �����¼���ִ�ж������ȵ�����
	WorkQueueList* _pList;
	// �����Ƿ�������
	bool _isWorking;
	// ����ִ�к���
	std::function<void(std::function<void()>)> _runInNextFrame;
};


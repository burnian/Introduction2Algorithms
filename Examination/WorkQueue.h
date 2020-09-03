#pragma once
#include <functional>

typedef std::function<void()> NextFunc;
typedef std::function<void(NextFunc)> WorkQueueFunc;

// 执行队列优先单链表
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

	// 采用插入排序，按优先级值从小到大排列
	WorkQueueList* insert(WorkQueueNode* pNode);
	// 从表头弹出一个节点
	WorkQueueNode* shift();
	// 表长度
	unsigned long getLen();
public:
	WorkQueueNode* _pHead;
	unsigned long _len;
};


// 执行队列
class WorkQueue
{
public:
	WorkQueue();
	~WorkQueue();

	static WorkQueue* getInstance();

	// 添加事件
	void addWork(int priority, WorkQueueFunc pFunc);
	// 设置帧函数
	void setFrameFunc(std::function<void(std::function<void()>)> func);
	// 移除帧函数
	void removeFrameFunc();
private:
	// 执行下一个事件
	void next();


private:
	static WorkQueue* _instance;
	// 保存事件的执行队列优先单链表
	WorkQueueList* _pList;
	// 队列是否在运行
	bool _isWorking;
	// 周期执行函数
	std::function<void(std::function<void()>)> _runInNextFrame;
};


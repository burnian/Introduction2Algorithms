#include "WorkQueue.h"


// 执行队列优先单链表
WorkQueueList::WorkQueueList()
	:_len(0)
{
}


WorkQueueList::~WorkQueueList()
{
	WorkQueueNode* p = nullptr;
	while (_len > 0)
	{
		p = _pHead;
		_pHead = _pHead->next;
		delete(p);
		_len--;
	}
}

WorkQueueList* WorkQueueList::insert(WorkQueueNode* pNode)
{
	_len++;

	if (_pHead == nullptr)
	{
		_pHead = pNode;
		return this;
	}
	WorkQueueNode* p = _pHead;
	if (p->priority > pNode->priority)
	{
		pNode->next = _pHead;
		_pHead = pNode;
		return this;
	}
	while (p->next != nullptr && p->next->priority <= pNode->priority)
	{
		p = p->next;
	}
	pNode->next = p->next;
	p->next = pNode;
	return this;
}

WorkQueueNode* WorkQueueList::shift()
{
	if (_len <= 0)
	{
		return nullptr;
	}
	_len--;

	WorkQueueNode* p = _pHead;
	_pHead = _pHead->next;
	return p;
}

unsigned long WorkQueueList::getLen()
{
	return _len;
}



// 执行队列
WorkQueue* WorkQueue::_instance = nullptr;

WorkQueue::WorkQueue()
	:_isWorking(false),
	_runInNextFrame(nullptr)
{
	_pList = new WorkQueueList();
}

WorkQueue::~WorkQueue()
{
	delete(_pList);
}

WorkQueue* WorkQueue::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new WorkQueue();
	}
	return _instance;
}

void WorkQueue::addWork(int priority, WorkQueueFunc pFunc)
{
	WorkQueueNode* node = new WorkQueueNode();
	node->priority = priority;
	node->pFunc = pFunc;
	_pList->insert(node);
	if (!_isWorking)
	{
		_isWorking = true;
		if (_runInNextFrame == nullptr)
		{
			next();
		}
		else
		{
			_runInNextFrame([this]()
			{
				next();
			});
		}
	}
}

void WorkQueue::next()
{
	WorkQueueNode* node = _pList->shift();
	if (node == nullptr)
	{
		_isWorking = false;
		return;
	}
	NextFunc func = [this]()
	{
		next();
	};
	node->pFunc(func);
	delete(node);
}

void WorkQueue::setFrameFunc(std::function<void(std::function<void()>)> func)
{
	_runInNextFrame = func;
}

void WorkQueue::removeFrameFunc()
{
	_runInNextFrame = nullptr;
}


//void iSleep(int second)
//{
//	for (int i = 0; i < second; i++)
//	{
//		Sleep(1000);
//		printf(".");
//	}
//	printf("\n");
//}
//
//void workQueueLogic()
//{
//	std::vector<std::function<void()>> frameEvents;
//
//	WorkQueue* workQueue = WorkQueue::getInstance();
//	workQueue->setFrameFunc([&](std::function<void()> func) {
//		frameEvents.push_back(func);
//	});
//
//	workQueue->addWork(5, [](NextFunc nextFunc) {
//		printf("priority 5\n");
//		iSleep(2);
//		nextFunc();
//	});
//	workQueue->addWork(10, [](NextFunc nextFunc) {
//		printf("priority 10\n");
//		iSleep(2);
//		nextFunc();
//	});
//	workQueue->addWork(0, [](NextFunc nextFunc) {
//		printf("priority 0\n");
//		iSleep(2);
//		nextFunc();
//	});
//
//	printf("next frame\n\n");
//	for each (auto func in frameEvents)
//	{
//		func();
//	}
//	frameEvents.clear();
//}

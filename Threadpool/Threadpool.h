#pragma once
///////////////////////////////////////////////////////////////////////
// QueuedWorkItems.h - child thread processes enqueued work items    //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016         //
///////////////////////////////////////////////////////////////////////
/*
* A single child thread processes work items equeued by main thread
*/

#include <thread>
#include <functional>
#include "BlockingQueue.h"
#include <mutex>

template<typename Result>
using WorkItem = std::function<Result()>;

///////////////////////////////////////////////////////////////////////
// class to process work items
// - each work item is processed sequentially on a single child thread

template<typename Result>
class ProcessWorkItem
{
public:
	void start();
	void doWork(WorkItem<Result>* pWi);
	Result result();
	void wait();
	ProcessWorkItem(int n);
	
	~ProcessWorkItem();
private:
	std::vector<std::thread*> _pThread;
	BlockingQueue<WorkItem<Result>*> _workItemQueue;
	BlockingQueue<Result> _resultsQueue;
	std::mutex mtx;
	int num;
};


template<typename Result>
inline ProcessWorkItem<Result>::ProcessWorkItem(int n)
{
	num = n;
}
template<typename Result>
BlockingQueue<WorkItem<Result>*> getQ()
{
	return _workItemQueue;
}
//----< wait for child thread to terminate >---------------------------

template<typename Result>
void ProcessWorkItem<Result>::wait()
{
	for(auto thr:_pThread)
		thr->join();
}

//----< enqueue work item >--------------------------------------------

template<typename Result>
void ProcessWorkItem<Result>::doWork(WorkItem<Result>* pWi)
{
	_workItemQueue.enQ(pWi);
}
//----< retrieve results with blocking call >--------------------------

template<typename Result>
Result ProcessWorkItem<Result>::result()
{
	return _resultsQueue.deQ();
}
//----< start child thread that dequeus work items >-------------------

template<typename Result>
void ProcessWorkItem<Result>::start()
{
	std::function<void()> threadProc =
		[&]() {
		while (true)
		{
			WorkItem<Result>* pWi = _workItemQueue.deQ();
			
			mtx.lock();
			if (pWi == nullptr)
			{
				_workItemQueue.enQ(nullptr);
				//std::cout << "\n  shutting down work item processing";
				mtx.unlock();
				return;
			}
			Result result = (*pWi)();
			_resultsQueue.enQ(result);
			mtx.unlock();
		}
	};
	
	for (int i = 0; i < num; i++)
		_pThread.push_back(new std::thread(threadProc));
}
//----< clean up heap >------------------------------------------------

template<typename Result>
ProcessWorkItem<Result>::~ProcessWorkItem()
{
	for(auto thr:_pThread)
		delete thr;
}



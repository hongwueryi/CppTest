
#include <vector>
#include <thread>
#include <mutex>

#include "ThreadPool.h"

CThreadPool::CThreadPool(int iCounts):ThreadCouts_(iCounts), isStart(false)
{
	start();
}

CThreadPool::~CThreadPool()
{
	if (isStart)
		stop();
}

void CThreadPool::AddTask(const TASK_FUNC& task)
{
	std::unique_lock<std::mutex>locker(m_mutex);
	deqtasks_.push_back(task);
	m_condition.notify_one();
}

void CThreadPool::ThreadLoopFunc()
{
	while (isStart)
	{
		TASK_FUNC task = takeTask();
		if (task)
			task();
	}
}

void CThreadPool::stop()
{
	std::unique_lock<std::mutex>locker(m_mutex);
	isStart = false;
	m_condition.notify_all();

	std::vector<std::thread*>::iterator it;
	for (it = vecThreads_.begin(); it != vecThreads_.end(); ++it)
	{
		(*it)->join();
		delete *it;
	}
	vecThreads_.shrink_to_fit();
}

void CThreadPool::start()
{
	isStart = true;
	vecThreads_.reserve(ThreadCouts_);
	for (int i = 0; i < ThreadCouts_; ++i)
	{
		vecThreads_.push_back(new std::thread(std::bind(&CThreadPool::ThreadLoopFunc, this)));
	}
}

TASK_FUNC CThreadPool::takeTask()
{
	std::unique_lock<std::mutex>locker(m_mutex);
	while (isStart && deqtasks_.empty())
	{
		m_condition.wait(locker);
	}

	TASK_FUNC task;
	if (!deqtasks_.empty() && isStart)
	{
		task = deqtasks_.front();
		deqtasks_.pop_front();
	}
	return task;
}

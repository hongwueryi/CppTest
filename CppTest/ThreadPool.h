#pragma once
#include <deque>
typedef std::function<void()> TASK_FUNC;

class CThreadPool
{
public:
	CThreadPool(int iCounts);
	~CThreadPool();

public:
	void AddTask(const TASK_FUNC& task);
	void ThreadLoopFunc();
	void start();
	TASK_FUNC takeTask();
	void stop();
private:
	bool isStart;
	int ThreadCouts_;
	std::vector<std::thread*> vecThreads_;
	std::deque<TASK_FUNC> deqtasks_;
	std::mutex m_mutex;
	std::condition_variable m_condition;
};

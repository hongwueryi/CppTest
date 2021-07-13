#include <iostream>
#include "threadpool.h"

#if 0
int main()
{
	// create thread pool with 4 worker threads
	ThreadPool pool(4);

	// enqueue and store future
	auto result = pool.enqueue([](int answer) { return answer; }, 42);

	// get result from future, print 42
	std::cout << result.get() << std::endl;
	getchar();
}
#endif

void func()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "worker thread ID:" << std::this_thread::get_id() << std::endl;
}

int main()
{
	ThreadPool pool(4);
	while (1)
	{
		pool.enqueue(func);
	}
}
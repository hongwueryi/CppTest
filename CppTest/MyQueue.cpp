#include <assert.h>
#include <mutex>
#include <thread>
#include <memory>
std::mutex g_mux;

enum type_operation
{
	type_push = 0,
	type_pop
};

namespace TestQueue
{
	template <typename T>
	class MyQueue
	{
	public:
		MyQueue(int QueueSize)
			: Size(0)
			, index(0)
			, Capacity(QueueSize)
		{
			Array = new T[QueueSize];
			//memset(Array, 0, QueueSize);
		}

		~MyQueue()
		{
			std::lock_guard<std::mutex> lock(g_mux);
			if (nullptr != Array)
			{
				delete[] Array;
				Array = nullptr;
			}
		}

		//入队
		void push(T x)
		{
			assert(IsFull() ? 0 : 1);
			std::lock_guard<std::mutex> lock(g_mux);
			Array[index++] = x;
			++Size;
			printf("push size=%d\n", Size);
		}

		//出队
		void pop()
		{
			if (IsEmpty())
			{
				return;
			}
			std::lock_guard<std::mutex> lock(g_mux);
			--Size;
			int i = 0;
			while (i++ < Size)
			{
				Array[i - 1] = Array[i];
			}
			printf("pop size=%d\n", Size);
		}

		//返回队首元素
		T front()
		{
			assert(IsEmpty() ? 0 : 1);
			std::lock_guard<std::mutex> lock(g_mux);
			return Array[0];
		}

		//返回队尾元素
		T back()
		{
			std::lock_guard<std::mutex> lock(g_mux);
			assert(IsEmpty() ? 0 : 1);
			return Array[Size - 1];
		}

		bool IsFull()
		{
			std::lock_guard<std::mutex> lock(g_mux);
			return Size == Capacity;
		}

		bool IsEmpty()
		{
			std::lock_guard<std::mutex> lock(g_mux);
			return 0 == Size;
		}

	private:
		T* Array;
		int Capacity;	//队列的最大容量
		int Size;       //队列中对象的数量
		int index;
	};
}

void threadProc(TestQueue::MyQueue<int>& test, int type)
{
	switch (type)
	{
	case type_push:
	{
		for (int i = 0; i < 9; i++)
		{
			test.push(i);
		}
	}
	case type_pop:
	{
		for (int i = 0; i < 9; i++)
		{
			printf("type_pop:front=%d\n", test.front());
			test.pop();
		}
	}
	default:
		break;
	}
}

int main()
{
#if 0
	TestQueue::MyQueue<int> test(2);
	test.push(1);
	test.push(2); 
	test.push(3); //断言终止
#endif
#if 0
	TestQueue::MyQueue<int> test(10);
	test.push(1);
	test.push(2);
	test.push(3);
	int FrontValue = test.front();   //1
	test.pop();
	FrontValue = test.front();   //2

	test.pop();
	FrontValue = test.front();   //3

	test.pop();
	FrontValue = test.front();   //断言终止
#endif
	//加锁保证原子操作，方便测试，异常使用断言中断
	TestQueue::MyQueue<int> test(10);
	std::thread t(threadProc, test, type_push);
	t.detach();
	std::thread t2(threadProc, test, type_pop);
	t2.detach();
	system("pause");
	return 0;
}
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <memory>
#include <condition_variable>
using namespace std::chrono;
std::mutex g_mutex;

std::condition_variable_any condition1;
std::condition_variable_any condition2;

std::string fetchDataFromDB(std::string recvData) {
	//确保函数要5秒才能执行完成
	std::this_thread::sleep_for(seconds(5));

	//处理创建数据库连接、获取数据等事情
	std::cout << "fromDB async" << std::endl;
	return "DB_" + recvData;
}

std::string fetchDataFromFile(std::string recvData) {
	//确保函数要5秒才能执行完成
	std::this_thread::sleep_for(seconds(2));

	//处理获取文件数据
	std::cout << "fromfile sync" << std::endl;
	return "File_" + recvData;
}
#if 0
int main() {
	//获取开始时间
	system_clock::time_point start = system_clock::now();

	//std::future<std::string> resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");
	//或者可以使用lambda表达式
	std::future<std::string> resultFromDB = std::async([](std::string receiveData) {
		std::this_thread::sleep_for(seconds(5));
		std::cout << "fromDB async" << std::endl;
		return "DB_" + receiveData;
	}, "Data");

	//从文件获取数据
	std::string fileData = fetchDataFromFile("Data");

	//从DB获取数据
	//数据在future<std::string>对象中可获取之前，将一直阻塞
	std::string dbData = resultFromDB.get();

	//获取结束时间
	auto end = system_clock::now();

	auto diff = duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << "Total Time taken= " << diff << "Seconds" << std::endl;

	//组装数据
	std::string data = dbData + " :: " + fileData;

	//输出组装的数据
	std::cout << "Data = " << data << std::endl;

	getchar();
	return 0;
}
#endif
typedef struct struct_Test
{
	int id;
	float value;
};
#include <vector>
#include <windows.h>
#include <atomic>
std::atomic_int atomic_d = 0;


void threadTest(int a, int&b)
{
	b = a;
	printf("%d", std::this_thread::get_id());
	return;
}

#if 0
template<typename T>
class threadsafe_queue
{
private:
	std::mutex mut;
	std::queue<T> data_queue;
	std::condition_variable data_cond;
public:
	void push(T new_value)
	{
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(new_value);
		data_cond.notify_one();
	}
	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		value = data_queue.front();
		data_queue.pop();
	}
};
threadsafe_queue<data_chunk> data_queue; // 1
void data_preparation_thread()
{
	while (more_data_to_prepare())
	{
		data_chunk const data = prepare_data();
		data_queue.push(data); // 2
	}
}
void data_processing_thread()
{
	while (true)
	{
		data_chunk data;
		data_queue.wait_and_pop(data); // 3
		process(data);
		if (is_last_chunk(data))
			break;
	}
}

class thread_pool
{
	std::atomic_bool done;
	thread_safe_queue<std::function<void()> > work_queue; // 1
	std::vector<std::thread> threads; // 2
	join_threads joiner; // 3
	void worker_thread()
	{
		while (!done) // 4
		{
			std::function<void()> task;
			if (work_queue.try_pop(task)) // 5
			{
				task(); // 6
			}
			else
			{
				std::this_thread::yield(); // 7
			}
		}
	}
public:
	thread_pool() :
		done(false), joiner(threads)
	{
		unsigned const thread_count = std::thread::hardware_concurrency(); // 12
		try
		{
			for (unsigned i = 0; i < thread_count; ++i)
			{
				threads.push_back(
					std::thread(&thread_pool::worker_thread, this)); // 9
			}
		}
		catch (...)
		{
			done = true; // 10
			throw;
		}
		}
	~thread_pool()
	{
		done = true; // 11
	}
	template<typename FunctionType>
	void submit(FunctionType f)
	{
		work_queue.push(std::function<void()>(f)); // 12
	}
};
#endif

template<class T> typename T tfunc(T a)
{
	return ++a;
}

class _tagNode {
public:
	void do_some_work(int a)
	{
		std::this_thread::sleep_for(seconds(1));
		printf("do_some_word a=%d\n", a);
	}
};

#include <ctime>
#include <ratio>
#include <iomanip> // put_time
#include <sstream>

std::mutex g_mux;
std::recursive_mutex g_recursive_mux;  

std::mutex tlock1_mux;
std::mutex tlock2_mux;
void lock_guard_test(int data)
{
	//std::lock_guard<std::mutex>lguard(g_mux);
	std::lock_guard<std::recursive_mutex>lguard(g_recursive_mux);
	printf("lock_guard_test %d\n", data);
}

void tLock1Proc()
{
	printf("tLock1Proc...\n");
	std::lock_guard<std::mutex> m1(tlock1_mux, std::adopt_lock);
	printf("tLock1Proc..._1\n");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::lock_guard<std::mutex> m2(tlock2_mux, std::adopt_lock);
	printf("tLock1Proc..._2\n");
	std::this_thread::sleep_for(std::chrono::seconds(3));
	printf("tLock1Proc..._3\n");
}

void tLock2Proc()
{
	printf("tLock2Proc...\n");
	std::lock_guard<std::mutex> m2(tlock2_mux, std::adopt_lock);
	printf("tLock2Proc..._1\n");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::lock_guard<std::mutex> m1(tlock1_mux, std::adopt_lock);
	printf("tLock2Proc..._2\n");
	std::this_thread::sleep_for(std::chrono::seconds(3));
	printf("tLock2Proc..._3\n");
}

int main1_()
{
	std::lock(tlock1_mux, tlock2_mux);
	std::thread tLock1(tLock1Proc);
	std::thread tLock2(tLock2Proc);
	printf("main...\n");
	getchar();
	return 0;
}


#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
std::once_flag g_once_flag;
void printThreadID(int id)
{
	mtx.lock();
	std::lock_guard<std::mutex>lck(mtx, std::adopt_lock);
	std::call_once(g_once_flag, []() {printf("once\n"); });
	std::cout << "thread # " << id << '\n';
}

void testAdoptingConstructor()
{
	std::thread threads[10];

	for (int i = 0; i < 10; ++i)
	{
		threads[i] = std::thread(printThreadID, i + 1);
	}

	for (auto& th : threads)
	{
		th.join();
	}
}


class Singleton {
public:
	static Singleton* getInstance() {
		static std::once_flag onceFlag; // 必须是静态的
		std::call_once(onceFlag, [&] {m_instance = new Singleton(); printf("singleton\n"); }); // 只会调用一次
		return m_instance;
	}
	void test() {}
	
private:
	Singleton() {} //私有构造函数，不允许使用者自己生成对象，但是必须要实现
	Singleton(const Singleton& other) = delete;
	Singleton& operator = (const Singleton& other) = delete;

private:
	static Singleton* m_instance; //静态成员变量 
	
};

Singleton* Singleton::m_instance = nullptr; //静态成员需要先初始化

int add(int a, int b)
{
	return a + b;
}

void do_other_things()
{
	//std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << "Hello World" << std::endl;
}

void print(std::promise<std::string>& p)
{
	printf("print\n");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	p.set_value("There is the result whitch you want.");
	std::this_thread::sleep_for(std::chrono::seconds(5));
	printf("thread end\n");
}

#if 1
#include <queue>
template<typename T> class threadsafe_queue 
{
private:
	mutable std::mutex mut;
	std::queue<T> data_queue;
	std::condition_variable data_cond;

public: 
	threadsafe_queue() {}
	void push(T new_value)
	{
		//printf("push\n");
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(std::move(new_value));
		printf("push_new_value=%d\n", new_value);
		data_cond.notify_one();  // 1 
		Sleep(100);
	}

	void wait_and_pop(T& value)  // 2 
	{ 
		std::unique_lock<std::mutex> lk(mut); 
		data_cond.wait(lk,[this]{return !data_queue.empty();});
		value=std::move(data_queue.front());
		data_queue.pop();
	}

	std::shared_ptr<T> wait_and_pop()  // 3 
	{ 
		std::unique_lock<std::mutex> lk(mut); 
		data_cond.wait(lk,[this]{return !data_queue.empty();});  // 4 
		std::shared_ptr<T> res( std::make_shared<T>(std::move(data_queue.front())));
		data_queue.pop();
		return res;
	}

	bool try_pop(T& value) {
		//printf("try_pop\n");
		std::lock_guard<std::mutex> lk(mut); 
		if (data_queue.empty())
			return false;
		value = std::move(data_queue.front());
		printf("value=%d\n", value);
		data_queue.pop();
		Sleep(5);
		return true; 
	}

	std::shared_ptr<T> try_pop() 
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return std::shared_ptr<T>();  // 5 
		std::shared_ptr<T> res( std::make_shared<T>(std::move(data_queue.front())));
		data_queue.pop();
		return res;
	}
	bool empty() const 
	{ 
		std::lock_guard<std::mutex> lk(mut);
		return data_queue.empty();
	}	
};
#endif

#include <deque>
std::deque<int>g_data;
std::atomic<bool> atomic_IsReady(false);
int main11()
{
	threadsafe_queue<int> safequeue;
	std::thread t111([&]{
		for (int i = 0; i < 50; i++)
		{
			safequeue.push(i);
		}
	});
	std::thread t222([&]{
		for (int i = 0; i < 80; i++)
		{
			int value;
			safequeue.try_pop(value);
			//safequeue.wait_and_pop(value);
		}
	});
	t111.join();
	t222.join();
#if 0
	std::thread tRead([]() {
		for (int i = 0; i < 10; i++)
		{
			while (!atomic_IsReady.load())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			printf("The answer=%d\n", g_data[0]);
			g_data.pop_front();
			
		}
	});
	std::thread tWrite([] {
		for (int i = 0; i < 10; i++)
		{
			atomic_IsReady.store(false);
			g_data.push_back(i);
			atomic_IsReady = true;
		}
			
	});
	tRead.join();
	tWrite.join();
#endif
#if 1
	std::promise<std::string> promise;
	
	std::future<std::string> result = promise.get_future();
	std::thread t(print, std::ref(promise));
	do_other_things();
	std::cout << result.get() << std::endl; // get()会等待至其有值
	printf("join\n");
	t.join();
	printf("join2\n");
#endif
#if 0
	std::packaged_task<int(int, int)> task(add);
	do_other_things();
	std::future<int> result = task.get_future();
	task(1, 1); //必须要让任务执行，否则在get()获取future的值时会一直阻塞
	std::cout << result.get() << std::endl;
#endif
#if 0
	//通过async来获取异步操作结果
	std::future<int>  result = std::async([]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		return 8;
	});

	std::cout << "the future result : " << result.get() << std::endl;
	std::cout << "the future status : " << result.valid() << std::endl;
	try
	{
		result.wait();  //或者 result.get() ,会异常
						//因此std::future只能用于单线程中调用 ，多线程调用使用std::shared_future();
	}
	catch (...)
	{
		std::cout << "get error....\n ";
	}
#endif
#if 0
	Singleton::getInstance()->test();
	Singleton::getInstance()->test();
#endif
	//testAdoptingConstructor();
	getchar();
	return 0;
}

int main()
{

	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	
	Sleep(3000);
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	std::chrono::duration<uint64_t> time_span = std::chrono::duration_cast<duration<uint64_t>>(t2 - t1);
	uint64_t dspan = time_span.count();  //seconds
	

#if 0
	std::lock(tlock1_mux, tlock2_mux);
	std::thread tLock1(tLock1Proc);
	std::thread tLock2(tLock2Proc);


	//std::lock_guard<std::mutex>lguard(g_mux);
	std::lock_guard<std::recursive_mutex>lguard(g_recursive_mux);
	printf("main...\n");
	lock_guard_test(5);  //如果使用std::mutex 而非std::recursive_mutex就会出现死锁，抛出异常
#endif
#if 0
	_tagNode node;
	//std::thread t(&_tagNode::do_some_work, &node, 1);  等同下一句
	std::thread t(std::mem_fn(&_tagNode::do_some_work), &node, 1);
 	if (t.joinable())
 		t.join();
	printf("do_some_word a=%d\n", 0);
	
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t nowtime_t = std::chrono::system_clock::to_time_t(now);
	//std::put_time(std::localtime(&nowtime), "%Y-%m-%d %X");
	std::stringstream ss;
	struct tm now_time;
	localtime_s(&now_time, &nowtime_t);
	printf("%d-%d-%d %d:%d:%d\n", now_time.tm_year + 1900, now_time.tm_mon + 1,
		now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
	steady_clock::time_point t1 = steady_clock::now();
	std::cout << "printing out 1000 stars...\n";
	for (int i = 0; i < 1000; ++i) std::cout << "*";
	std::cout << std::endl;
	steady_clock::time_point t2 = steady_clock::now();
	
	std::chrono::duration<double> time_span = std::chrono::duration_cast<duration<double>>(t2 - t1);
	double dspan = time_span.count();
	std::cout << "It took me " << time_span.count() << " seconds.";
	std::cout << std::endl;
#endif

#if 0
	std::shared_ptr<int> sp1(new int(10));
	std::shared_ptr<int> sp2(sp1);
	std::weak_ptr<int> weakp(sp2);
	//输出和 wp 同指向的 shared_ptr 类型指针的数量
	int icount = weakp.use_count(); //2
									//释放 sp2

	sp2.reset();
	icount = weakp.use_count();   //1
	if (auto ptr = weakp.lock())
	{
		icount = *(weakp.lock());   //10
	}


	int a = 0;
	a = tfunc(a);
	int * p = new int(5);
	std::shared_ptr<int> pshared(p);

	if (!pshared)
	{
		std::shared_ptr<int> pshared2 = std::make_shared<int>(5);
		int cout = pshared.use_count();
		int cout2 = pshared2.use_count();
		pshared2 = pshared;
		cout = pshared.use_count();
		cout2 = pshared2.use_count();
		int *pold = pshared.get();
	}
	int cout = pshared.use_count();
	std::unique_ptr<int> uni(new int(5));
	std::unique_ptr<int> uni2 = std::move(uni);
	int uninum = *uni2; //5
						//uninum = *uni;  //奔溃，uni isempty

	uni.get_deleter();
	std::weak_ptr<int>wp(pshared);
	//std::weak_ptr<int>wp = wptr;
	std::shared_ptr<int>psh = wp.lock();
	int count = wp.use_count();
	if (psh)
	{
		if (!wp.expired())
		{
			int count = wp.use_count();
		}
	}
#endif
#if 0
	int sss = std::pow(2, 3);
	std::vector<struct_Test> s;
	for (int i = 0; i < 3; i++)
	{
		struct_Test t;
		t.id = i;
		t.value = 1.0;
		s.push_back(t);
	}

	std::sort(s.begin(), s.end(), [](struct_Test a, struct_Test b) {
		return a.id > b.id;
	});
#endif
#if 0
	int a = 2;
	int refa = 0;
	std::thread t(threadTest, a, std::ref(refa));
	if (t.joinable())
		t.join();
#endif
	
	std::thread thread1([]() {
		while (1)
		{
			printf("run thread1\n");
			std::unique_lock<std::mutex> locker(g_mutex);
			printf("run lock thread1\n");
			condition1.wait(locker);
			printf("threa1 exec...\n");
			//std::this_thread::sleep_for(std::chrono::seconds(2));
			condition2.notify_one();
		}
		});
	
	std::thread thread2([]() {
		while (1)
		{
			printf("run thread2\n");
			std::unique_lock<std::mutex> locker(g_mutex);
			printf("run lock thread2\n");
			condition2.wait(locker);
			printf("threa2 exec...\n");
			//std::this_thread::sleep_for(std::chrono::seconds(3));
			condition1.notify_one();
		}
		});
	thread1.join();
	thread2.join();
	Sleep(1000);
	condition1.notify_one();
	//system("pause");
	while (1)
	{
		Sleep(1000);
	}
	return  0;
}

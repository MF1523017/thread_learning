#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

void f1(int n) {
	for (int i = 0; i < 5; ++i) {
		std::cout << "thread: 1 executing f1\n";
		std::this_thread::sleep_for(std::chrono::microseconds(100000));// 睡1s
	}
}

void f2(int &n) {
	for (int i = 0; i < 5; ++i) {
		std::cout << "thread: 2 executing f2\n";
		++n;
		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}
}

void thread_task(int n) {
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout << "hello thread id: " << std::this_thread::get_id() << " paused " << n << " s " << std::endl; // id is int 
}

int main(int argc, char **argv) {

	unsigned int num = std::thread::hardware_concurrency();
	std::cout << num << " concurrent threads are supported.\n";// 检测当前平台支持的线程数目
	int n = 0;
	std::thread t1;// not a thread not joinable
	std::thread t2(f1, n + 1);
	std::thread t3(f2, std::ref(n));
	std::thread t4(std::move(t3));// t4 is now running f2,t3 is no longer a thread
	std::cout << "thread t2 id: " << t2.get_id() << std::endl;
	std::cout << "thread t4 id: " << t4.get_id() << std::endl;
	std::swap(t2, t4); // 互换 两个线程
	std::cout << "after swap(t2,t4): " << std::endl;
	std::cout << "thread t2 id: " << t2.get_id() << std::endl;
	std::cout << "thread t4 id: " << t4.get_id() << std::endl;
	t2.swap(t4);// 互换 两个线程
	std::cout << "after t2.swap(t4): " << std::endl;
	std::cout << "thread t2 id: " << t2.get_id() << std::endl;
	std::cout << "thread t4 id: " << t4.get_id() << std::endl;
	t2.join();
	t4.join();

	std::thread ts[5];
	std::cout << "spawning 5 threads...\n";
	for (int i = 0; i < 5; ++i) {
		ts[i] = std::thread(thread_task, i + 1);
	}
	std::cout << "done spawning 5 threads! waiting for them to join" << std::endl;
	for (int i = 0; i < 5; ++i) {
		ts[i].join();
	}
	std::cout << "all joined" << std::endl;
	system("pause");
	return 0;
}
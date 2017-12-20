#if 0
unconditional(1):	void wait(unique_lock<mutex>& lck);
wait()之后，被阻塞，当前线程获得的锁mutex 将会被unlock

predicate(2):
template <class Predicate>
void wait(unique_lock<mutex>& lck, Predicate pred);
只有当pred条件为false的时候才调用wait()，然后阻塞当前线程，并且收到notify之后只有pred为true的时候才会解除阻塞
#endif

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int cargo = 0;
bool ready = false;

void print_id(int id) {
	std::unique_lock<std::mutex> lock(mtx);
	while (!ready) {
		cv.wait(lock);
	}
	std::cout << "thread " << id << std::endl;
}


void go() {
	std::unique_lock<std::mutex> lock(mtx);
	ready = true;
	cv.notify_all();
}

bool shipment_available() {
	return cargo != 0;
}
// 消费者线程

void consume(int n) {
	for (int i = 0; i < n; ++i) {
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, shipment_available);
		std::cout << cargo << std::endl;
		cargo = 0;
	}
}


int main(int argc, char **argv) {
	//std::thread ts[10];
	//for (int i = 0; i < 10; ++i) {
	//	ts[i] = std::thread(print_id, i);
	//}
	//std::cout << "10 threads ready to race..." << std::endl;
	//go(); // 0-9 随机运行
	//for (auto &th : ts) {
	//	th.join();
	//}
	std::thread consumer_thread(consume, 10);
	for (int i = 0; i < 10; ++i) {
		while (shipment_available())
		{
			std::this_thread::yield();
		}
		std::unique_lock<std::mutex> lock(mtx);
		cargo = i + 1;
		cv.notify_one();
	}
	consumer_thread.join();
	system("pause");
	return 0;
}
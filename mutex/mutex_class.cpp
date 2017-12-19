#include <thread>
#include <iostream>
#include <mutex>
#include <stdexcept>

volatile int counter(0);
std::mutex mtx;

void try_10k_add() {
	for (int i = 0; i < 10000; ++i) {
		if (mtx.try_lock()) { //���Լ������ɹ��˾�����
			++counter;
			mtx.unlock();
		}
	}
}

void print_even(int x) {
	if (x % 2 == 0) std::cout << x << " is even\n";// ż����ӡ
	else throw (std::logic_error("not even")); // �����ӳ��쳣
}

void print_thread_id(int id) {
	try {
		// using a local lock_guard to lock mtx guarantees unlocking on destruction / exception:
		//std::lock_guard<std::mutex> lck(mtx); // ����������֮�����Զ���� // unique_lock ����
		std::unique_lock<std::mutex> lck(mtx); // ����������֮�����Զ���� // unique_lock ����
		print_even(id);
	}
	catch (std::logic_error&) {
		std::cout << "[exception caught]\n";
	}
}


int main(int argc, char **argv) {
	std::thread ts[10];
	for (int i = 0; i < 10; ++i) {
		ts[i] = std::thread(try_10k_add);
	}
	for (auto &t : ts)t.join();
	std::cout << counter << " successful add of the counter" << std::endl;

	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_thread_id, i + 1);

	for (auto& th : threads) th.join();
	system("pause");
}
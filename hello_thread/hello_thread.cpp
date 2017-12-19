#include <iostream>
#include <thread>
#include <string>
void thread_task() {
	std::cout << "hello thread" << std::endl;
}

void func(int i, double d, const std::string &s) {
	std::cout << i << "," << d << "," << s << std::endl;
}

void func1(int &i) {
	while (10000 != (++i));
}

int main(int argc, char **argv) {
	std::thread t(thread_task);
	std::thread t1(func, 1, 13.14, "sample"); // 打印出来的并不是按照顺序的，可能是hello thread1,
																			//13.14, sample
												//也可能是hello thread1,13.14,sample \n
	t.join();
	t1.join();//join() 就需要等待他们都运行结束才能执行下面的代码
	int a = 0;
	std::thread t2(func1, std::ref(a));
	t2.detach(); //Detached threads are no longer joinable (you cannot wait for them). 
	std::cout << a << std::endl;// 所以这里a输出是0到10000 之间的随机值

	system("pause");
	return 0;
}
#include <iostream>

int i = 0;
auto func = [](int x, int y)->int {return x + y; }; //full pattern: [capture](parameters)->return_type{function body}
auto func1 = [](int x, int y) {return x + y; }; // ingore return type: [capture](parameters){function body}
auto func2 = []() {++i; }; // ingore parameters and return type ,only globle var: [capture](){function body (globle var)}
auto func3 = []{++i; }; // ingore parameters and return type ,only globle var: [capture](){function body (globle var)}
int main(int argc, char **argv) {
	
	std::cout << func(1, 2)<< std::endl;
	std::cout << func1(1, 2) << std::endl;
	func2();
	std::cout << i << std::endl;
	func3();
	std::cout << i << std::endl;
	system("pause");

	return 0;
}
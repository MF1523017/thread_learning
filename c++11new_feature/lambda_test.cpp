#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int i = 0;
auto func = [](int x, int y)->int {return x + y; }; //full pattern: [capture](parameters)->return_type{function body}
auto func1 = [](int x, int y) {return x + y; }; // ingore return type: [capture](parameters){function body}
auto func2 = []() {++i; }; // ingore parameters and return type ,only globle var: [capture](){function body (globle var)}
auto func3 = []{++i; }; // ingore parameters and return type ,only globle var: [capture](){function body (globle var)}
//[]        //未定义变量.试图在Lambda内使用任何外部变量都是错误的.
//[x, &y]   //x 按值捕获, y 按引用捕获.
//[&]       //用到的任何外部变量都隐式按引用捕获
//[=]       //用到的任何外部变量都隐式按值捕获
//[&, x]    //x显式地按值捕获. 其它变量按引用捕获
//[=, &z]   //z按引用捕获. 其它变量按值捕获


//ambda函数是一个依赖于实现的函数对象类型, 这个类型的名字只有编译器知道.
//如果用户想把lambda函数做为一个参数来传递, 那么形参的类型必须是模板类型或者必须能创建一个
//std::function类似的对象去捕获lambda函数.使用 auto关键字可以帮助存储lambda函数,

auto my_lambda_func = [&](int x) {return x*x; };
auto my_lambda_onheap = new auto([=](int x) {return x*x; });


class LambdaTest{
private:
	int get_5()const { return 5; }
public:
	void test() {
		std::vector<int> v;
		for (int i = 0; i < 5; ++i)
			v.push_back(i);
		int total = 0;
		int value = 2;
		std::for_each(v.begin(), v.end(), [&total,value,this](int x) {total += value * x * get_5(); });// 对this的捕获只能是按值捕获
		std::cout << "total: " << total << std::endl;
	}
};

int main(int argc, char **argv) {
	
	std::cout << func(1, 2)<< std::endl;
	std::cout << func1(1, 2) << std::endl;
	func2();
	std::cout << i << std::endl;
	func3();
	std::cout << i << std::endl;

	std::vector<int> v;
	for (int i = 0; i < 5; ++i)
		v.push_back(i);
	int total = 0;
	std::for_each(v.begin(), v.end(), [&total](int x) {total += x; });
	std::cout << "total: " << total << std::endl;

	int total5 = 0;
	int value = 5;
	std::for_each(v.begin(), v.end(), [&,value](int x) {total5 += 5 * x; });
	std::cout << "total: " << total5 << std::endl;

	LambdaTest t;
	t.test();

	system("pause");

	return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int i = 0;
auto func = [](int x, int y)->int {return x + y; }; //full pattern: [capture](parameters)->return_type{function body}
auto func1 = [](int x, int y) {return x + y; }; // ingore return type: [capture](parameters){function body}
auto func2 = []() {++i; }; // ingore parameters and return type ,only globle var: [capture](){function body (globle var)}
auto func3 = []{++i; }; // ingore parameters and return type ,only globle var: [capture](){function body (globle var)}
//[]        //δ�������.��ͼ��Lambda��ʹ���κ��ⲿ�������Ǵ����.
//[x, &y]   //x ��ֵ����, y �����ò���.
//[&]       //�õ����κ��ⲿ��������ʽ�����ò���
//[=]       //�õ����κ��ⲿ��������ʽ��ֵ����
//[&, x]    //x��ʽ�ذ�ֵ����. �������������ò���
//[=, &z]   //z�����ò���. ����������ֵ����


//ambda������һ��������ʵ�ֵĺ�����������, ������͵�����ֻ�б�����֪��.
//����û����lambda������Ϊһ������������, ��ô�βε����ͱ�����ģ�����ͻ��߱����ܴ���һ��
//std::function���ƵĶ���ȥ����lambda����.ʹ�� auto�ؼ��ֿ��԰����洢lambda����,

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
		std::for_each(v.begin(), v.end(), [&total,value,this](int x) {total += value * x * get_5(); });// ��this�Ĳ���ֻ���ǰ�ֵ����
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
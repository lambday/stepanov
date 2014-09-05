#include <iostream>
#include <algorithm>
#include <array.h>
#include <minmax.h>

void test1()
{
	int a = 5, b = 5;
	const int& min = stepanov::min(a, b);
	std::cout << &a << "," << &b << "," << &min << std::endl;
	const int& max = stepanov::max(a, b);
	std::cout << &a << "," << &b << "," << &max << std::endl;
}

void test2()
{
	const size_t n = 5;
	typedef int value_type;
	stepanov::array<value_type> a(n);
	std::cout << a << std::endl;

	// case 1
	std::iota(a.begin(), a.end(), 1);
	std::random_shuffle(a.begin(), a.end());
	int* min_el = stepanov::min_element(a.begin(), a.end(), std::less<value_type>());
	std::cout << a << std::endl;
	std::cout << "min:" << min_el << ":" << *min_el << std::endl;

	// case 2
	std::fill(a.begin(), a.end(), 5);
	min_el = stepanov::min_element(a.begin(), a.end(), std::less<value_type>());
	std::cout << a << std::endl;
	std::cout << "min:" << min_el << ":" << *min_el << std::endl;
}

void test3()
{
	const size_t n = 5;
	typedef int value_type;
	stepanov::array<value_type> a(n);
	std::cout << a << std::endl;

	// case 1
	std::iota(a.begin(), a.end(), 1);
	std::random_shuffle(a.begin(), a.end());
	int* max_el = stepanov::max_element(a.begin(), a.end());
	std::cout << a << std::endl;
	std::cout << "max:" << max_el << ":" << *max_el << std::endl;

	// case 2
	std::fill(a.begin(), a.end(), 5);
	max_el = stepanov::max_element(a.begin(), a.end());
	std::cout << a << std::endl;
	std::cout << "max:" << max_el << ":" << *max_el << std::endl;
}

int main(int argc, char **argv)
{
	test3();
	return 0;
}

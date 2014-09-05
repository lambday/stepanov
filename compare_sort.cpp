#include <iostream>
#include <algorithm>
#include <instrumented.h>
#include <set>

using namespace std;

template <typename T>
struct sort_functor
{
	void operator()(const T& first, const T& last)
	{
		sort(first, last);
	}
};

template <typename T>
struct stable_sort_functor
{
	void operator()(const T& first, const T& last)
	{
		stable_sort(first, last);
	}
};

template <typename T>
struct heap_sort_functor
{
	void operator()(const T& first, const T& last)
	{
		partial_sort(first, last, last);
	}
};

template <class T, class SortFunctor>
void test_sort(T a[], const size_t& n, SortFunctor f)
{
	f(a, a + n);
}

int main(int argc, char** argv)
{
	typedef instrumented<int> type_name;

	instrumented_base::print_counters();
	for (size_t i = 4; i < 16; ++i)
	{
		const size_t n = 0x1 << i;
		type_name a[n];
		iota(a, a + n, 1);
		random_shuffle(a, a + n);
		test_sort(a, n, stable_sort_functor<type_name*>());
		cout << a[0] << "\t[" << n << "]" << endl;
	}
	return 0;
}

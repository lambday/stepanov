#include <iostream>
#include <algorithm>
#include <instrumented.h>
#include <set>

using namespace std;

template <class T>
int find_unique_using_sort(T a[], size_t n)
{
	sort(a, a + n);
	return unique(a, a + n) - a;
	return 0;
}

template <class T>
int find_unique_using_set(T a[], size_t n)
{
	set<T> s(a, a + n);
	return s.size();
}

int main(int argc, char** argv)
{
	typedef instrumented<int> type_name;

	int (*find_unique)(type_name[], size_t) = NULL;
	if (argc > 1)
	{
		cout << "using sort" << endl;
		find_unique = &find_unique_using_sort;
	}
	else
	{
		cout << "using set" << endl;
		find_unique = &find_unique_using_set;
	}

	instrumented_base::print_counters();
	for (size_t i = 4; i < 16; ++i)
	{
		const size_t n = 0x1 << i;
		type_name a[n];
		iota(a, a + n, 1);
		random_shuffle(a, a + n);
		find_unique(a, n);
		cout << a[0] << "\t[" << n << "]" << endl;
	}
	return 0;
}

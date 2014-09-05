#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

size_t max_iter = 1000;

void foo()
{
	for (size_t i = 0; i < max_iter; ++i)
	{
		size_t n = 1000;
		int a[n];
		iota(a, a + n, 0);
		random_shuffle(a, a + n);
		sort(a, a + n);
	}
}

// way 1 - using callback functions
void callback_foo(void (*f)())
{
	f();
}

// way 2 - using functor
struct functor
{
	void operator()()
	{
		foo();
	}
};

template <class Functor>
void functorized_foo(Functor f)
{
	f();
}

int main(int argc, char** argv)
{
	size_t n = max_iter;
	if (argc < 2)
	{
		cout << "callback" << endl;
		for (size_t i = 0; i < n; ++i)
			callback_foo(&foo);
	}
	else
	{
		cout << "functorized" << endl;
		for (size_t i = 0; i < n; ++i)
			functorized_foo(functor());
	}
	return 0;
}

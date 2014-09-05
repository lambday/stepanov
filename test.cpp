/**
 * The MIT License (MIT)
 *
 *	Copyright (c) 2014 Soumyajit De
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */

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

/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Soumyajit De
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

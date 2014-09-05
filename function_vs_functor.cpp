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

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

void test4()
{
	const size_t n = 5;
	typedef int value_type;
	stepanov::array<value_type> a(n);
	std::cout << a << std::endl;

	// case 1
	std::iota(a.begin(), a.end(), 1);
	std::random_shuffle(a.begin(), a.end());
	std::pair<int*, int*> minmax_el = stepanov::minmax_element(a.begin(), a.end());
	std::cout << a << std::endl;
	std::cout << "min:" << minmax_el.first << ":" << *minmax_el.first << std::endl;
	std::cout << "max:" << minmax_el.second << ":" << *minmax_el.second << std::endl;

	// case 2
	std::fill(a.begin(), a.end(), 5);
	minmax_el = stepanov::minmax_element(a.begin(), a.end());
	std::cout << a << std::endl;
	std::cout << "min:" << minmax_el.first << ":" << *minmax_el.first << std::endl;
	std::cout << "max:" << minmax_el.second << ":" << *minmax_el.second << std::endl;
}

int main(int argc, char **argv)
{
	test4();
	return 0;
}

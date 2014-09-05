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

#ifndef INSTRUMENTED_H_
#define INSTRUMENTED_H_

#include <iostream>

using namespace std;

struct instrumented_base
{
	enum operations
	{
		construction = 0,
		cast,
		default_constructor,
		copy,
		assignment,
		destructor,
		equal,
		comparison,
		num_of_operations
	};

	static int counts[num_of_operations];
	static const char* operations_names[];
	static void print_counters();
};

template <typename T>
struct instrumented : instrumented_base
{
	typedef T value_type;

	// semi-regular
	explicit instrumented(const T& x) : value(x)
	{
		counts[construction]++;
	}
	operator T() const
	{
		counts[cast]++;
		return value;
	}
	instrumented(const instrumented& other) : value(other.value)
	{
		counts[copy]++;
	}
	instrumented& operator=(const instrumented& other)
	{
		counts[assignment]++;
		value = other.value;
		return *this;
	}
	instrumented& operator=(const T& x)
	{
		counts[assignment]++;
		value = x;
		return *this;
	}
	instrumented()
	{
		counts[default_constructor]++;
	}
	~instrumented()
	{
		counts[destructor]++;
	}

	// regular
	friend bool operator==(const instrumented& x, const instrumented& y)
	{
		counts[equal]++;
		return x.value == y.value;
	}
	friend bool operator!=(const instrumented& x, const instrumented& y)
	{
		return !(x == y);
	}

	// totally ordered
	friend bool operator<(const instrumented& x, const instrumented& y)
	{
		counts[comparison]++;
		return x.value < y.value;
	}
	friend bool operator>(const instrumented& x, const instrumented& y)
	{
		return y < x;
	}
	friend bool operator<=(const instrumented& x, const instrumented& y)
	{
		return !(x > y);
	}
	friend bool operator>=(const instrumented& x, const instrumented& y)
	{
		return !(x < y);
	}

	// for printing purpose
	friend ostream& operator<<(ostream& os, const instrumented& obj)
	{
		os << counts[construction] << "\t\t" << counts[cast] << "\t\t"
			<< counts[default_constructor] << "\t" << counts[copy] << "\t"
			<< counts[assignment] << "\t" << counts[destructor] << "\t  "
			<< counts[equal] << "\t" << counts[comparison] << "\t\t";
		int total = 0;
		for (int x : counts)
			total += x;
		os << total;
		return os;
	}

	T value;
};
#endif // INSTRUMENTED_H_

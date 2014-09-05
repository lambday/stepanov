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

template <typename T>
struct singleton
{
	typedef T value_type;

	// semi-regular
	explicit singleton(const T& x) : value(x) {}
	operator T() const
	{
		return value;
	}
	singleton(const singleton& other) : value(other.value) {}
	singleton& operator=(const singleton& other)
	{
		value = other.value;
		return *this;
	}
	singleton() {}
	~singleton() {}

	// regular
	friend bool operator==(const singleton& x, const singleton& y)
	{
		return x.value == y.value;
	}
	friend bool operator!=(const singleton& x, const singleton& y)
	{
		return !(x == y);
	}

	// totally ordered
	friend bool operator<(const singleton& x, const singleton& y)
	{
		return x.value < y.value;
	}
	friend bool operator>(const singleton& x, const singleton& y)
	{
		return y < x;
	}
	friend bool operator<=(const singleton& x, const singleton& y)
	{
		return !(x > y);
	}
	friend bool operator>=(const singleton& x, const singleton& y)
	{
		return !(x < y);
	}

	T value;
};

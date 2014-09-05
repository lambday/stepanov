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

#ifndef ARRAY_H_
#define ARRAY_H_

#include <iostream>

namespace stepanov
{

template <typename T>
struct _Iterator
{
	typedef T value_type;
	_Iterator(T* _ptr) : ptr(_ptr) {}
	operator T*() const
	{
		return ptr;
	}
	_Iterator(const _Iterator& other) : ptr(other.ptr) {}
	_Iterator() : ptr(NULL) {}
	_Iterator& operator=(const _Iterator& other)
	{
		ptr = other.ptr;
		return *this;
	}
	~_Iterator() {}

	_Iterator& operator++()
	{
		++ptr;
		return *this;
	}
	_Iterator operator++(int incr)
	{
		_Iterator it = *this;
		++(*this);
		return it;
	}
	T* ptr;
};

template <typename T>
struct array
{
	typedef T value_type;
	typedef _Iterator<T> iterator;

	explicit array(size_t _size) : size(_size)
	{
		values = new value_type[size];
		_begin = values;
		_end = _begin + size;
	}
	explicit array(T* _values, size_t _size) : values(_values), size(_size)
	{
		_begin = values;
		_end = _begin + size;
	}
	operator T*() const
	{
		return values;
	}
	array() : size(0), values(NULL)
	{
	}
	array(const array& other) : size(other.size), values(other.values)
	{
		_begin = values;
		_end = _begin + size;
	}
	array& operator=(const array& other)
	{
		size = other.size;
		values = other.values;
		_begin = values;
		_end = _begin + size;
		return *this;
	}
	~array()
	{
		delete [] values;
	}

	// random access operator
	T& operator[](const size_t i)
	{
		return values[i];
	}
	const T& operator[](const size_t i) const
	{
		return values[i];
	}

	// iterators
	iterator begin() const
	{
		return iterator(_begin);
	}
	iterator end() const
	{
		return iterator(_end);
	}

	// for printing purpose
	friend std::ostream& operator<<(std::ostream& os, const array& obj)
	{
		for (size_t i = 0; i < obj.size; ++i)
		{
			os << &obj._begin[i] << ":" << obj._begin[i] << "\n";
		}
		return os;
	}

	size_t size;
	T* _begin;
	T* _end;
	T* values;
};

}

#endif // ARRAY_H_

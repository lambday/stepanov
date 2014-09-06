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

#ifndef MINMAX_H_
#define MINMAX_H_

#include <iostream>
#include <algorithm>
#include <array.h>
#include <map>

namespace stepanov
{

template <typename T, class Comparator>
// requires T to be StrictWeakOrdered (as opposed to TotallyOrdered)
// TotallyOrdered -> either a < b or a > b or a == b
// StrictWeakOrdered -> either a < b or a > b or a <=> b (equivalent)
const T& min(const T& a, const T& b, Comparator cmp) // assume cmp to be <
{
	if (cmp(b, a)) // same as checking b < a
		return b;
	else return a;
	// the idea is to return the first in case they are same (for min)
}

template <typename T>
const T& min(const T& a, const T& b)
{
	return stepanov::min(a, b, std::less<T>());
}

// in max, the idea is to return the last in case they are same

template <typename T, class Comparator>
const T& max(const T& a, const T& b, Comparator cmp)
{
	if (cmp(b, a)) return a;
	else return b;
}

template <typename T>
const T& max(const T& a, const T& b)
{
	return stepanov::max(a, b, std::greater<T>());
}

// iterated - first points to first element, last points to one past last element
template <typename I, class Comparator>
// requires I to be a ForwardIterator
// and Comparator to be StrictWeakOrdered on the value_type(I)
I min_element(I first, I last, Comparator cmp)
{
	// end case - first and last are same
	if (first == last) return last;
	I min_el = first;
	++first;
	while (first != last)
	{
		// invariants:
		// min_el is the current min
		// first is the current element
		// we want to update this min only if the new element that
		// we are looking at is strictly minimum.
		if (cmp(*first, *min_el)) min_el = first;
		++first;
	}
	return min_el;
}

template <class I>
I min_element(I first, I last)
{
	return stepanov::min_element(first, last, std::less<typename I::value_type>());
}

// iterated - first points to first element, last points to one past last element
template <typename I, class Comparator>
// requires I to be a ForwardIterator
// and Comparator to be StrictWeakOrdered on the value_type(I)
I max_element(I first, I last, Comparator cmp)
{
	// end case - first and last are same
	if (first == last) return last;
	I max_el = first;
	++first;
	while (first != last)
	{
		// invariants:
		// max_el is the current max
		// first is the current element
		// we want to update this max if the new element that
		// we are looking at is max or equal.
		if (!cmp(*first, *max_el)) max_el = first;
		++first;
	}
	return max_el;
}

template <class I>
I max_element(I first, I last)
{
	return stepanov::max_element(first, last, std::less<typename I::value_type>());
}

// for same elements, min should return the leftmost and max should
// return the rightmost
template <typename I, class Comparator>
// requires I to be a ForwardIterator
// and Comparator to be StrictWeakOrdered on the value_type(I)
std::pair<I, I> minmax_element(I first, I last, Comparator cmp)
{
	// handle size 0 case
	if (first == last)
		return std::make_pair(last, last);

	// for the following, we know that the size is at least 1
	I current_min = first;
	++first;
	// needs checking - this may reach last
	// if it does, the min and max are the same element
	if (first == last)
		return std::make_pair(current_min, current_min);
	// for the following, we know that the size is at least 2
	I current_max = first;

	// initialization
	// assuming cmp is <, we want to swap only when max is strictly
	// lesser than min (no swapping when they are same)
	if (cmp(*current_max, *current_min))
		std::swap(current_min, current_max);
	++first;

	while (first != last)
	{
		// invariants:
		// current_min contains the running min
		// currnet_max contains the running max
		// first is at the 1st one we are looking for in a group of 2
		I potential_min = first;
		++first;
		// handle odd case - group size of 1
		I potential_max = first == last ? potential_min : first;

		// first is only guaranteed to have moved up to position 1 next

		if (cmp(*potential_max, *potential_min))
			std::swap(potential_min, potential_max);

		// update the current values
		if (cmp(*potential_min, *current_min))
			current_min = potential_min;
		if (!cmp(*potential_max, *current_max))
			current_max = potential_max;

		// sanity check
		if (first != last)
			++first;
	}

	return std::make_pair(current_min, current_max);
}

template <class I>
std::pair<I, I> minmax_element(I first, I last)
{
	return stepanov::minmax_element(first, last, std::less<typename I::value_type>());
}

}
#endif // MINMAX_H_


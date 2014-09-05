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

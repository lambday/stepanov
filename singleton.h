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

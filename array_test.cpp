#include <array.h>
#include <algorithm>

void array_test()
{
	const size_t n = 5;
	stepanov::array<int> a(n);
	std::iota(a.begin(), a.end(), 1);
	std::cout << a;
}

int main(int argc, char **argv)
{
	array_test();
	return 0;
}

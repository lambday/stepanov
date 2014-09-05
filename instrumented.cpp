#include <iostream>
#include <instrumented.h>

using namespace std;

int instrumented_base::counts[instrumented_base::num_of_operations];
const char* instrumented_base::operations_names[] =
{
	"construction",
	"cast",
	"default_constructor",
	"copy",
	"assignment",
	"destructor",
	"equal",
	"comparison"
};

void instrumented_base::print_counters()
{
	for (const char* operation : operations_names)
		cout << operation << " ";
	cout << "\ttotal" << endl;
}

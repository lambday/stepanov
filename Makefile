all: compare_sort.o instrumented.o
	g++ -O3 -std=c++0x compare_sort.o instrumented.o -I.
compare_sort.o: compare_sort.cpp instrumented.h
	g++ -O3 -std=c++0x -c compare_sort.cpp -I.
instrumented.o: instrumented.cpp instrumented.h
	g++ -O3 -std=c++0x -c instrumented.cpp -I.
clean:
	rm *.o a.out

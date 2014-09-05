all: test.o instrumented.o
	g++ -O3 -std=c++0x test.o instrumented.o -I.
test.o: test.cpp ./compare_sort/instrumented.h
	g++ -O3 -std=c++0x -c test.cpp -I.
instrumented.o: ./compare_sort/instrumented.cpp ./compare_sort/instrumented.h
	g++ -O3 -std=c++0x -c ./compare_sort/instrumented.cpp -I./compare_sort
clean:
	rm *.o a.out

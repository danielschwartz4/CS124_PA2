CC=c++
CFLAGS=-c -Wall

all: strassen


strassen: matrix_mul.o strassen.o matrix.o
		  $(CC) strassen.o matrix_mul.o matrix.o -o strassen

triangle: triangle.o matrix.o matrix_mul.o
		$(CC) triangle.o matrix.o matrix_mul.o -o triangle
tests: tests.o matrix.o matrix_mul.o
	  $(CC) tests.o matrix.o matrix_mul.o -o tests

explore_crossover2: explore_crossover2.o matrix_mul.o matrix.o
			$(CC) explore_crossover2.o matrix_mul.o matrix.o -o explore_crossover2

explore_crossover: explore_crossover.o matrix_mul.o matrix.o
			$(CC) explore_crossover.o matrix_mul.o matrix.o -o explore_crossover

strassen.o: strassen.cpp
		$(CC) $(CFLAGS) strassen.cpp

explore_crossover2.o: explore_crossover2.cc
					$(CC) $(CFLAGS) -std=c++17 explore_crossover2.cc

explore_crossover.o: explore_crossover.cc
					$(CC) $(CFLAGS) explore_crossover.cc

tests.o: tests.cc
		 $(CC) $(CFLAGS) tests.cc

matrix_mul.o: matrix_mul.cc
			$(CC) $(CFLAGS) matrix_mul.cc

matrix.o: matrix.cc
		$(CC) $(CFLAGS) matrix.cc

triangle.o: triangle.cc
		$(CC) $(CFLAGS) triangle.cc

clean: 
	rm *.o strassen tests







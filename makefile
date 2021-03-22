CC=c++
CFLAGS=-c -Wall

all: strassen


# strassen: matrix_mul.o strassen.o
# 		  $(CC) strassen.o matrix_mul.o -o strassen

# explore_cutoff: explore_cutoff.o matrix_mul.o
# 				$(CC) explore_cutoff.o matrix_mul.o -o explore_cutoff


tests: tests.o matrix.o matrix_mul.o
	  $(CC) tests.o matrix.o matrix_mul.o -o tests

explore_crossover: explore_crossover.o matrix_mul.o matrix.o
			$(CC) explore_crossover.o matrix_mul.o matrix.o -o explore_crossover

explore_crossover.o: explore_crossover.cc
					$(CC) $(CFLAGS) explore_crossover.cc

tests.o: tests.cc
		 $(CC) $(CFLAGS) tests.cc

matrix_mul.o: matrix_mul.cc
			$(CC) $(CFLAGS) matrix_mul.cc

matrix.o: matrix.cc
		$(CC) $(CFLAGS) matrix.cc

# triangle: triangle.cc
# 		$(CC) $(CFLAGS) triangle.cc

clean: 
	rm *.o strassen tests







CC=c++
CFLAGS=-c -Wall

all: strassen


# strassen: matrix_mul.o strassen.o
# 		  $(CC) strassen.o matrix_mul.o -o strassen

# explore_cutoff: explore_cutoff.o matrix_mul.o
# 				$(CC) explore_cutoff.o matrix_mul.o -o explore_cutoff


tests: tests.o matrix_mul.o
	  $(CC) tests.o matrix_mul.o -o tests	

matrix_mul: matrix_mul.o 
			$(CC) matrix_mul.o -o matrix_mul

tests.o: tests.cc
		 $(CC) $(CFLAGS) tests.cc

matrix_mul.o: matrix_mul.cc
			$(CC) $(CFLAGS) matrix_mul.cc

clean: 
	rm *.o strassen tests





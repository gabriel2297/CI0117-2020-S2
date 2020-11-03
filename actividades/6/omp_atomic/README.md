compile: omp_atomic.cpp
	g++ -g -Wall -fopenmp omp_atomic.cpp -o omp_atomic
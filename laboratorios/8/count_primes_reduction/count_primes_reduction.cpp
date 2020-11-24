#include <iostream>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

bool isPrime(int number) {
    if ( number < 2 ) return false;
	if ( number == 2 ) return true;
	if ( number % 2 == 0 ) return false;

	for ( size_t i = 3, last = (size_t)(double)sqrt(number); i <= last; i += 2 )
		if ( number % i == 0 )
			return false;

	return true;
}

int main(int argc, char *argv[])
{
  int my_id, numProcesses, lower_limit, upper_limit, primes = 0, counter = 0, segments, temp;
  size_t max_num;
  double start_time = 0.0, end_time = 0.0;
  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  MPI_Status status;

  if (my_id == 0){
    std::cout << "Enter the max number: ";
    std::cin >> max_num;
    segments = max_num / numProcesses;
  }
  MPI_Bcast(&max_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&segments, 1, MPI_INT, 0, MPI_COMM_WORLD);
  if (!my_id){
    lower_limit = 0;
    upper_limit = (int)(my_id + 1) * segments;
    start_time = MPI_Wtime();
  }
  else {
    lower_limit = (int)(my_id * segments) + 1;
    upper_limit = (my_id == numProcesses - 1) ? max_num : (int)(my_id + 1) * segments;
  }

  for (int i = lower_limit; i <= upper_limit; ++i){
    if(isPrime(i)){
      ++counter;
    }
  }
  MPI_Reduce(&counter, &primes, 1,MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (my_id == 0){
    end_time = MPI_Wtime();
    std::cout << "There are " << primes <<  " prime numbers between [2 , " << max_num << " ] " << std::endl;
    std::cout << "The total time was " << end_time - start_time << "s" << std::endl;
  }

  MPI_Finalize();

  return 0;
}
